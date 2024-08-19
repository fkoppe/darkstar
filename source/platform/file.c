/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2024 Felix Koppe <fkoppe@web.de>                             *
*                                                                                   *
*   This program is free software: you can redistribute it and/or modify            *
*   it under the terms of the GNU Affero General Public License as published        *
*   by the Free Software Foundation, either version 3 of the License, or            *
*   (at your option) any later version.                                             *
*                                                                                   *
*   This program is distributed in the hope that it will be useful,                 *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of                  *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   *
*   GNU Affero General Public License for more details.                             *
*                                                                                   *
*   You should have received a copy of the GNU Affero General Public License        *
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.          *
*                                                                                   *
************************************************************************************/

#include "file_helper.h"
#include "platform_module.h"

#include <dark/core/core.h>
#include <dark/memory/allocator.h>
#include <dark/platform/file_struct.h>
#include <dark/platform/platform.h>

#undef DARK_UNIT
#define DARK_UNIT "file"

#if defined(___DARK_WINDOWS)
#include <dark/windows.h>
#include <io.h>
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
#include <sys/mman.h>
#include <sys/stat.h>
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

void dark_file_construct(Dark_Allocator* const allocator_, Dark_File* const file_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    file_->allocator = allocator_;
    file_->mode = ___DARK_FILE_MODE_MAX;
    file_->flag = DARK_FILE_FLAG_NONE;
    file_->handle = NULL;
}

void dark_file_destruct(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    //nothing
}

Dark_File* dark_file_new(Dark_Allocator* const allocator_)
{
    Dark_File* const file = dark_malloc(allocator_, sizeof(*file));
    DARK_ASSERT(NULL != file, DARK_ERROR_ALLOCATION);

    dark_file_construct(allocator_, file);

    return file;
}

void dark_file_delete(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    dark_file_destruct(file_);

    dark_free(file_->allocator, file_, sizeof(*file_));
}

Dark_Oserror dark_file_open(Dark_File* const file_, const char* const path_, const Dark_File_Mode mode_, const Dark_File_Flag flag_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_FILE_MODE_MIN < mode_ && mode_ < ___DARK_FILE_MODE_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(___DARK_FILE_FLAG_MIN < flag_ && flag_ < ___DARK_FILE_FLAG_MAX, DARK_ERROR_ENUM);

    DARK_CSTRING_ASSERT_CONTENT(path_);
    DARK_ASSERT_MESSAGE(NULL == file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_ALREADY);

    file_->mode = mode_;
    file_->flag = flag_;

    char modifier[DARK_FILE_MODIFIER_SIZE] = { 0 };
    dark_file_modifier_get(mode_, flag_, modifier);

    file_->handle = fopen(path_, modifier);

    if (NULL == file_->handle)
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_close(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);

    if (0 != fclose(file_->handle))
    {
        return dark_oserror_occured();
    }

    file_->handle = NULL;

    return DARK_OSERROR_NONE;
}

bool dark_file_open_is(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    return file_->handle;
}

Dark_Oserror dark_file_write(Dark_File* const file_, const Dark_Cbuffer_View source_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.data != NULL, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_WRITE == file_->mode || DARK_FILE_MODE_APPEND == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_WRITE);
    DARK_ASSERT_MESSAGE(!(file_->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, DARK_MESSAGE_FILE_FLAG_BINARY);

    if (fwrite(source_.data, sizeof(char), source_.size, file_->handle) != source_.size)
    {
        return dark_oserror_occured();
    }

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}


Dark_Oserror dark_file_write_binary(Dark_File* const file_, const Dark_Array_View source_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(source_.element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.data != NULL, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_WRITE == file_->mode || DARK_FILE_MODE_APPEND == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_WRITE);
    DARK_ASSERT_MESSAGE(file_->flag & DARK_FILE_FLAG_BINARY, DARK_ERROR_STATE, DARK_MESSAGE_FILE_FLAG_BINARY);

    if (fwrite(source_.data, source_.element_byte, source_.size, file_->handle) != source_.size)
    {
        return dark_oserror_occured();
    }

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_read(Dark_File* const file_, const Dark_Cbuffer destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_READ);
    DARK_ASSERT_MESSAGE(!(file_->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, DARK_MESSAGE_FILE_FLAG_BINARY);

    if (NULL == fgets(destination_.data, destination_.size, file_->handle))
    {
        return dark_oserror_occured();
    }

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_read_binary(Dark_File* const file_, const Dark_Array destination_, size_t* const read_count_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(destination_.data != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != read_count_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_READ);
    DARK_ASSERT_MESSAGE(file_->flag & DARK_FILE_FLAG_BINARY, DARK_ERROR_STATE, DARK_MESSAGE_FILE_FLAG_BINARY);

    *read_count_ = fread(destination_.data, destination_.element_byte, destination_.size, file_->handle);

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_mmap(Dark_File* const file_, void** const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_READ);

#if defined(___DARK_WINDOWS)
    const HANDLE handle_mapped = CreateFileMapping((HANDLE)_get_osfhandle(fileno(file_->handle)), NULL, PAGE_READONLY, 0, 0, 0);
    if (NULL == handle_mapped)
    {
        return dark_oserror_occured();
    }

    *destination_ = MapViewOfFile(handle_mapped, FILE_MAP_READ, 0, 0, 0);

    bool b = CloseHandle(handle_mapped);
    DARK_ASSERT_CSTRING(b, DARK_ERROR_PLATFORM, "CloseHandle");

    if (NULL == *destination_)
    {
        return dark_oserror_occured();
    }
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    struct stat sb;
    fstat(fileno(file_->handle), &sb);

    *destination_ = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fileno(file_->handle), 0);
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_byte(Dark_File* const file_, size_t* const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(NULL != file_->handle, DARK_ERROR_STATE, DARK_MESSAGE_FILE_OPENED_NOT);
    DARK_ASSERT_MESSAGE((file_->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file_->mode, DARK_ERROR_STATE, DARK_MESSAGE_FILE_MODE_READ);

#if defined(___DARK_WINDOWS)
    LARGE_INTEGER size;

    if (0 == GetFileSizeEx((HANDLE)_get_osfhandle(fileno(file_->handle)), &size))
    {
        return dark_oserror_occured();
    }

    *destination_ = size.QuadPart;
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    struct stat sb;
    fstat(fileno(file_->handle), &sb);

    *destination_ = sb.st_size;
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

    if (ferror(file_->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

size_t dark_file_struct_byte(void)
{
    return sizeof(Dark_File);
}

size_t dark_file_count_max(void)
{
    return FOPEN_MAX;
}
