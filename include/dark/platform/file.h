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

//TODO errors

size_t dark_file_struct_size(void);

void dark_file_create(void* file);
void dark_file_destroy(void* file);

void* dark_file_new(void);
void dark_file_delete(void* file);

bool dark_file_open(void* file, const char* path, Dark_File_Mode mode, Dark_File_Flag flag);
bool dark_file_close(void* file);

bool dark_file_open_is(void* file);

bool dark_file_write(void* file, size_t size, size_t count, const void* data);

bool dark_file_read(void* file, size_t max, char* destination);
bool dark_file_binary_read(void* file, size_t size, size_t max, size_t* count, char* destination);

bool dark_file_mmap(void* file, const char** destination);

bool dark_file_size_get(void* file, size_t* destination);

size_t dark_file_count_max(void);

#endif // !defined(___DARK___FILE_H)
