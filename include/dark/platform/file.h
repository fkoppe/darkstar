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

#include <dark/container/array.h>
#include <dark/core/message.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>
#include <dark/platform/oserror.h>

#define DARK_FILE_MODIFIER_SIZE 4

typedef enum Dark_File_Mode Dark_File_Mode;
enum Dark_File_Mode
{
    ___DARK_FILE_MODE_MIN,
    DARK_FILE_MODE_READ,
    DARK_FILE_MODE_WRITE,
    DARK_FILE_MODE_APPEND,
    ___DARK_FILE_MODE_MAX,
};

typedef enum Dark_File_Flag Dark_File_Flag;
enum Dark_File_Flag
{
    ___DARK_FILE_FLAG_MIN   = 0,
    DARK_FILE_FLAG_NONE     = 1 << 0,
    DARK_FILE_FLAG_UPDATE   = 1 << 1,
    DARK_FILE_FLAG_BINARY   = 1 << 2,
    ___DARK_FILE_FLAG_MAX   = 1 << 3,
};

typedef struct Dark_File Dark_File;

static const Dark_Message DARK_MESSAGE_FILE_MODE_UPDATE = { NULL, "nor update flag set", NULL };
static const Dark_Message DARK_MESSAGE_FILE_MODE_READ = { &DARK_MESSAGE_FILE_MODE_UPDATE, "file not in read mode ", NULL };
static const Dark_Message DARK_MESSAGE_FILE_MODE_WRITE = { &DARK_MESSAGE_FILE_MODE_UPDATE, "file not in write mode ", NULL };
static const Dark_Message DARK_MESSAGE_FILE_FLAG_BINARY = { NULL, "no binary flag set", NULL };
static const Dark_Message DARK_MESSAGE_FILE_OPENED_NOT = { NULL, "file not opened", NULL };
static const Dark_Message DARK_MESSAGE_FILE_OPENED_ALREADY = { NULL, "file already opened", NULL };

size_t dark_file_struct_byte(void);

void dark_file_construct(Dark_File* file);
void dark_file_destruct(Dark_File* file);

Dark_File* dark_file_new(Dark_Allocator* allocator);
void dark_file_delete(Dark_Allocator* allocator, Dark_File* file);

Dark_Oserror dark_file_open(Dark_File* file, const char* path, Dark_File_Mode mode, Dark_File_Flag flag);
Dark_Oserror dark_file_close(Dark_File* file);

bool dark_file_open_is(Dark_File* file);

Dark_Oserror dark_file_write(Dark_File* file, Dark_Array array);

Dark_Oserror dark_file_read(Dark_File* file, size_t max, char* destination);
Dark_Oserror dark_file_binary_read(Dark_File* file, size_t element_byte, size_t max, size_t* count, void* destination);

Dark_Oserror dark_file_mmap(Dark_File* file, void** destination);

Dark_Oserror dark_file_byte(Dark_File* file, size_t* destination);

size_t dark_file_count_max(void);

void dark_file_modifier_get(Dark_File_Mode mode, Dark_File_Flag flag, char* destionation);

#endif // !defined(___DARK___FILE_H)
