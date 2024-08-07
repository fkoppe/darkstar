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

#if !defined(___DARK___OSTREAM_H)
#define ___DARK___OSTREAM_H

#include <dark/container/vector.h>
#include <dark/core/std.h>
#include <dark/platform/mutex.h>
#include <dark/tool/buffer.h>

typedef struct Dark_Ostream Dark_Ostream;

typedef struct Dark_Ostream_Settings Dark_Ostream_Settings;
struct Dark_Ostream_Settings
{
    bool binary_is;
    bool force_size_is;
    size_t buffer_size;
};

typedef struct Dark_Ostream_Struct Dark_Ostream_Struct;
struct Dark_Ostream_Struct
{
    Dark_Allocator* allocator;
    Dark_Ostream_Settings settings;
    Dark_Vector* file_vector;
    Dark_Vector* buffer_vector;
    struct
    {
        bool out_is;
        bool err_is;
        void* out_mutex;
        void* err_mutex;
    } std;
};

size_t dark_ostream_struct_byte(void);

void dark_ostream_construct(Dark_Allocator* allocator, Dark_Ostream* ostream, Dark_Ostream_Settings settings);
void dark_ostream_destruct(Dark_Ostream* ostream);

Dark_Ostream* dark_ostream_new(Dark_Allocator* allocator, Dark_Ostream_Settings settings);
void dark_ostream_delete(Dark_Ostream* ostream);

void dark_ostream_write(Dark_Ostream* ostream, Dark_Buffer_View source);

void dark_ostream_flush(Dark_Ostream* ostream);
void dark_ostream_flush_unbuffered(Dark_Ostream* ostream, Dark_Buffer_View source);

void dark_ostream_add_file(Dark_Ostream* ostream, const char* path, Dark_Mutex* mutex);
void dark_ostream_add_stdout(Dark_Ostream* ostream, Dark_Mutex* mutex);
void dark_ostream_add_stderr(Dark_Ostream* ostream, Dark_Mutex* mutex);

#endif // !defined(___DARK___OSTREAM_H)
