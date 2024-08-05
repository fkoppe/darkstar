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

#if !defined(___DARK___OSTREAM_STRUCT_H)
#define ___DARK___OSTREAM_STRUCT_H

#include <dark/container/vector_struct.h>
#include <dark/core/std.h>
#include <dark/platform/mutex_struct.h>
#include <dark/stream/ostream.h>

struct Dark_Ostream
{
    Dark_Allocator* allocator;
    Dark_Ostream_Settings settings;
    Dark_Vector file_vector;
    Dark_Vector buffer_vector;
    struct
    {
        bool out_is;
        bool err_is;
        Dark_Mutex* out_mutex;
        Dark_Mutex* err_mutex;
    } std;
};

#endif // !defined(___DARK___OSTREAM_STRUCT_H)
