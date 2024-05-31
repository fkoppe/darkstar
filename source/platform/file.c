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
#include <dark/platform/platform.h>

#include <stdio.h>
#include <errno.h>

#undef DARK_UNIT
#define DARK_UNIT "file"

#if defined(___DARK_LINUX)
#define ___DARK_UNIX
#endif // defined(___DARK_LINUX)

#if defined(___DARK_DARWIN)
#define ___DARK_UNIX
#endif // defined(___DARK_DARWIN)

#if defined(___DARK_WINDOWS)
#include <io.h>
#include <windows.h>
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
#include <sys/mman.h>
#include <sys/stat.h>
#endif // defined(___DARK_UNIX)

typedef struct Dark_File_Struct
{
    Dark_File_Mode mode;
    Dark_File_Flag flag;
    FILE* handle;
} Dark_File_Struct;

size_t dark_file_struct_size(void)
{
    return sizeof(Dark_File_Struct);
}

void dark_file_construct(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    file->mode = ___DARK_FILE_MODE_MAX;
    file->flag = DARK_FILE_FLAG_NONE;
    file->handle = NULL;
}

void dark_file_destruct(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    //nothing
}

Dark_File* dark_file_new(void)
{
    Dark_File_Struct* const file = malloc(sizeof(*file));
    DARK_ASSERT(NULL != file, DARK_ERROR_ALLOCATION);

    dark_file_construct((Dark_File*)file);

    return (Dark_File*)file;
}

void dark_file_delete(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    dark_file_destruct((Dark_File*)file);

    free(file);
}

Dark_Oserror dark_file_open(Dark_File* const file_, const char* const path_, const Dark_File_Mode mode_, const Dark_File_Flag flag_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    DARK_ASSERT(mode_ < ___DARK_FILE_MODE_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(flag_ < ___DARK_FILE_FLAG_MAX, DARK_ERROR_ENUM);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL == file->handle, DARK_ERROR_STATE, "already opened");

    file->mode = mode_;
    file->flag = flag_;

    char modifier[DARK_FILE_MODIFIER_SIZE] = { '\0' };
    dark_file_modifier_get(mode_, flag_, modifier);

    file->handle = fopen(path_, modifier);

    if (NULL == file->handle)
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_close(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");

    if (0 != fclose(file->handle))
    {
        return dark_oserror_occured();
    }

    file->handle = NULL;

    return DARK_OSERROR_NONE;
}

bool dark_file_open_is(Dark_File* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    return file->handle;
}

Dark_Oserror dark_file_write(Dark_File* const file_, const size_t size_, const size_t count_, const void* const data_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_WRITE == file->mode || DARK_FILE_MODE_APPEND == file->mode, DARK_ERROR_STATE, "no write mode nor update flag set");

    if (fwrite(data_, size_, count_, file->handle) != count_)
    {
        return dark_oserror_occured();
    }

    if (ferror(file->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_read(Dark_File* const file_, const size_t max_, char* const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(max_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "binary flag set");

    if (NULL == fgets(destination_, max_, file->handle))
    {
        return dark_oserror_occured();
    }

    if (ferror(file->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_binary_read(Dark_File* const file_, const size_t element_size_, const size_t element_count_, size_t* const count_, char* const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(element_count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != count_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "no binary flag set");

    *count_ = fread(destination_, element_size_, element_count_, file->handle);

    if (ferror(file->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_mmap(Dark_File* const file_, const char** const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");

#if defined(___DARK_WINDOWS)
    const HANDLE handle_mapped = CreateFileMapping((HANDLE)_get_osfhandle(fileno(file->handle)), NULL, PAGE_READONLY, 0, 0, 0);
    if (NULL == handle_mapped)
    {
        return dark_oserror_occured();
    }

    *destination_ = MapViewOfFile(handle_mapped, FILE_MAP_READ, 0, 0, 0);

    bool b = CloseHandle(handle_mapped);
    DARK_ASSERT_MSG(b, DARK_ERROR_PLATFORM, "CloseHandle");

    if (NULL == *destination_)
    {
        return dark_oserror_occured();
    }
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    struct stat sb;
    fstat(fileno(file->handle), &sb);

    *destination_ = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fileno(file->handle), 0);
#endif // defined(___DARK_UNIX)

    if (ferror(file->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

Dark_Oserror dark_file_size_get(Dark_File* const file_, size_t* const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File_Struct* const file = (Dark_File_Struct*)file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE) || DARK_FILE_MODE_READ == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");

#if defined(___DARK_WINDOWS)
    LARGE_INTEGER l_int;

    if (0 == GetFileSizeEx((HANDLE)_get_osfhandle(fileno(file->handle)), &l_int))
    {
        return dark_oserror_occured();
    }

    *destination_ = l_int.QuadPart;
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    struct stat sb;
    fstat(fileno(file->handle), &sb);

    *destination_ = sb.st_size;
#endif // defined(___DARK_UNIX)

    if (ferror(file->handle))
    {
        return dark_oserror_occured();
    }

    return DARK_OSERROR_NONE;
}

size_t dark_file_count_max(void)
{
    return FOPEN_MAX;
}
