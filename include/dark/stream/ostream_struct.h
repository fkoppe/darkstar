/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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

#if !defined(___DARK___OSTREAM_STRUCT_H)
#define ___DARK___OSTREAM_STRUCT_H

#include <dark/container/vector_struct.h>
#include <dark/core/std.h>
#include <dark/platform/file_struct.h>
#include <dark/platform/mutex_struct.h>
#include <dark/stream/ostream.h>
#include <dark/time/stopwatch_struct.h>

typedef enum Dark_Ostream_Type Dark_Ostream_Type;
enum Dark_Ostream_Type
{
    ___DARK_OSTREAM_TYPE_MIN,
    DARK_OSTREAM_TYPE_FILE,
    DARK_OSTREAM_TYPE_STD,
    ___DARK_OSTREAM_TYPE_MAX,
};

struct Dark_Ostream
{
    Dark_Allocator* allocator;
    Dark_Ostream_Settings settings;
    Dark_Vector buffer_vector;
    Dark_Mutex* mutex;
    Dark_Ostream_Type type;
    union
    {
        struct
        {
            Dark_Cbuffer_View path;
            Dark_File_Flag flag;
            Dark_File* instance;
        } file;
        FILE* std;
    } data;
    Dark_Stopwatch* stopwatch;
};

#endif // !defined(___DARK___OSTREAM_STRUCT_H)
