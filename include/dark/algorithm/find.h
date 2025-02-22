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

#if !defined(___DARK___FIND_H)
#define ___DARK___FIND_H

#include <dark/core/std.h>
#include <dark/tool/array.h>
#include <dark/tool/array_view.h>
#include <dark/tool/compare.h>

bool dark_find_linear_index(const void* element, Dark_Array_View array_view, Dark_Compare compare, size_t* index);
bool dark_find_linear_reverse_index(const void* element, Dark_Array_View array_view, Dark_Compare compare, size_t* index);
bool dark_find_binary_index(const void* element, Dark_Array_View array_view, Dark_Compare compare, size_t* index);

void* dark_find_linear(const void* element, Dark_Array array, Dark_Compare compare);
void* dark_find_linear_reverse(const void* element, Dark_Array array, Dark_Compare compare);
void* dark_find_binary(const void* element, Dark_Array array, Dark_Compare compare);

const void* dark_find_view_linear(const void* element, Dark_Array_View array_view, Dark_Compare compare);
const void* dark_find_view_linear_reverse(const void* element, Dark_Array_View array_view, Dark_Compare compare);
const void* dark_find_view_binary(const void* element, Dark_Array_View array_view, Dark_Compare compare);

#endif // !defined(___DARK___FIND_H)
