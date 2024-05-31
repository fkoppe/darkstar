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

#if !defined(___DARK___FILE_H)
#define ___DARK___FILE_H

#include <dark/core/essential.h>
#include <dark/platform/oserror.h>

typedef struct Dark_File Dark_File;

typedef enum Dark_File_Mode
{
    DARK_FILE_MODE_READ,
    DARK_FILE_MODE_WRITE,
    DARK_FILE_MODE_APPEND,
    ___DARK_FILE_MODE_MAX,
} Dark_File_Mode;

typedef enum Dark_File_Flag
{
    DARK_FILE_FLAG_NONE     = 0,
    DARK_FILE_FLAG_UPDATE   = 1 << 0,
    DARK_FILE_FLAG_BINARY   = 1 << 1,
    ___DARK_FILE_FLAG_MAX,
} Dark_File_Flag;

size_t dark_file_struct_size(void);

void dark_file_construct(Dark_File* file);
void dark_file_destruct(Dark_File* file);

Dark_File* dark_file_new(void);
void dark_file_delete(Dark_File* file);

Dark_Oserror dark_file_open(Dark_File* file, const char* path, Dark_File_Mode mode, Dark_File_Flag flag);
Dark_Oserror dark_file_close(Dark_File* file);

bool dark_file_open_is(Dark_File* file);

Dark_Oserror dark_file_write(Dark_File* file, size_t size, size_t count, const void* data);

Dark_Oserror dark_file_read(Dark_File* file, size_t max, char* destination);
Dark_Oserror dark_file_binary_read(Dark_File* file, size_t element_size, size_t element_count, size_t* count, char* destination);

Dark_Oserror dark_file_mmap(Dark_File* file, const char** destination);

Dark_Oserror dark_file_size_get(Dark_File* file, size_t* destination);

size_t dark_file_count_max(void);

#endif // !defined(___DARK___FILE_H)
