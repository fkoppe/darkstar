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

#if !defined(___DARK___ARRAY_H)
#define ___DARK___ARRAY_H

#include <dark/container/foreach.h>
#include <dark/core/std.h>

typedef struct Dark_Array Dark_Array;
struct Dark_Array
{
    void* data;
    size_t size;
    size_t element_byte;
};

typedef struct Dark_Array_View Dark_Array_View;
struct Dark_Array_View
{
    const void* data;
    size_t size;
    size_t element_byte;
};

Dark_Array_View dark_array_view(Dark_Array array);

void dark_array_foreach(Dark_Array array, void* context, Dark_Foreach foreach);

#endif // !defined(___DARK___ARRAY_H)
