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

typedef struct Dark_File
{
    Dark_File_Mode mode;
    Dark_File_Flag flag;
    FILE* handle;
} Dark_File;

size_t dark_file_count_max(void)
{
    return FOPEN_MAX;
}

void dark_file_modifier_get(const Dark_File_Mode mode_, const Dark_File_Flag flag_, char* const destination_)
{
    DARK_ASSERT(mode_ < ___DARK_FILE_MODE_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(flag_ < ___DARK_FILE_FLAG_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    switch (mode_)
    {
    case DARK_FILE_MODE_READ:
        *destination_ = 'r';
        break;
    case DARK_FILE_MODE_WRITE:
        *destination_ = 'w';
        break;
    case DARK_FILE_MODE_APPEND:
        *destination_ = 'a';
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }

    size_t i = 1;

    if (flag_ & DARK_FILE_FLAG_BINARY)
    {
        destination_[i] = 'b';
        i++;
    }

    if (flag_ & DARK_FILE_FLAG_UPDATE)
    {
        destination_[i] = '+';
        i++;
    }
}

void* dark_file_new(void)
{
    Dark_File* file = malloc(sizeof(*file));
    DARK_ASSERT(NULL != file, DARK_ERROR_ALLOCATION);

    file->mode = ___DARK_FILE_MODE_MAX;
    file->flag = DARK_FILE_FLAG_NONE;
    file->handle = NULL;

    return file;
}

void dark_file_delete(void* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    free(file);
}

bool dark_file_open(void* const file_, const char* const path_, const Dark_File_Mode mode_, const Dark_File_Flag flag_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    DARK_ASSERT(mode_ < ___DARK_FILE_MODE_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(flag_ < ___DARK_FILE_FLAG_MAX, DARK_ERROR_ENUM);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL == file->handle, DARK_ERROR_STATE, "already opened");

    file->mode = mode_;
    file->flag = flag_;

    char modifier[DARK_FILE_MODIFIER_SIZE] = { '\0' };
    dark_file_modifier_get(mode_, flag_, modifier);

    file->handle = fopen(path_, modifier);

    if (NULL == file->handle)
    {
        file->handle = NULL;

        return false;
    }

    return true;
}

bool dark_file_close(void* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");

    if (0 != fclose(file->handle))
    {
        return false;
    }

    file->handle = NULL;

    return true;
}

bool dark_file_open_is(void* const file_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    return file->handle;
}

bool dark_file_read(void* const file_, const size_t max_, char** const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "binary flag set");

    if (max_ > 0)
    {
        char* const result = fgets(*destination_, max_, file->handle);

        if (NULL == result)
        {
            return false;
        }
    }

    return true;
}

bool dark_file_write_char(void* const file_, const char character_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_WRITE) == file->mode, DARK_ERROR_STATE, "no write mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "binary flag set");

    const int result = fputc(character_, file->handle);

    if (0 == result)
    {
        return false;
    }

    return true;
}

bool dark_file_write_cbuffer(void* const file_, const char* const cbuffer_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cbuffer_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_WRITE) == file->mode, DARK_ERROR_STATE, "no write mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "binary flag set");

    const int result = fputs(cbuffer_, file->handle);

    if (EOF == result)
    {
        return false;
    }

    return true;
}

bool dark_file_binary_read(void* const file_, const size_t size_, const size_t max_, size_t* const count_, char** const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != count_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "no binary flag set");

    if (max_ > 0)
    {
        errno = EINVAL;

        *count_ = fread(*destination_, size_, max_, file->handle);

        if (*count_ != max_)
        {
            if (0 == feof(file->handle))
            {
                return false;
            }
        }

        if (errno != EINVAL)
        {
            return false;
        }
    }

    return true;
}

bool dark_file_binary_write(void* const file_, const size_t size_, const size_t count_, const void* const data_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_WRITE) == file->mode, DARK_ERROR_STATE, "no write mode nor update flag set");
    DARK_ASSERT_MSG(!(file->flag & DARK_FILE_FLAG_BINARY), DARK_ERROR_STATE, "no binary flag set");

    if (count_ > 0)
    {
        const size_t result = fwrite(data_, size_, count_, file->handle);

        if (result != count_)
        {
            return false;
        }
    }

    return true;
}

bool dark_file_mmap(void* const file_, const char** const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");

#ifdef ___DARK_WINDOWS
    const HANDLE handle_mapped = CreateFileMapping((HANDLE)_get_osfhandle(fileno(file->handle)), NULL, PAGE_READONLY, 0, 0, 0);

    if (NULL == handle_mapped)
    {
        return false;
    }

    *destination_ = MapViewOfFile(handle_mapped, FILE_MAP_READ, 0, 0, 0);

    bool b = CloseHandle(handle_mapped);
    DARK_ASSERT(b, DARK_ERROR_PLATFORM, "CloseHandle");

    if (NULL == *destination_)
    {
        return false;
    }
#endif // ___DARK_WINDOWS

#if defined(___DARK_UNIX)
    struct stat sb;
    fstat(fileno(file->handle), &sb);

    *destination_ = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fileno(file->handle), 0);
#endif // defined(___DARK_UNIX)

    return true;
}

bool dark_file_size_get(void* const file_, size_t* const destination_)
{
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    Dark_File* file = file_;

    DARK_ASSERT_MSG(NULL != file->handle, DARK_ERROR_STATE, "not opened");
    DARK_ASSERT_MSG((file->flag & DARK_FILE_FLAG_UPDATE || DARK_FILE_MODE_READ) == file->mode, DARK_ERROR_STATE, "no read mode nor update flag set");

#ifdef ___DARK_WINDOWS
    LARGE_INTEGER l_int;

    if (0 == GetFileSizeEx((HANDLE)_get_osfhandle(fileno(file->handle)), &l_int))
    {
        return false;
    }

    *destination_ = l_int.QuadPart;
#endif // ___DARK_WINDOWS

#if defined(___DARK_UNIX)
    struct stat sb;
    fstat(fileno(file->handle), &sb);

    *destination_ = sb.st_size;
#endif // defined(___DARK_UNIX)

    return true;
}
