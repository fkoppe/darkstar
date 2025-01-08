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

#if !defined(___DARK___ARRAY_VIEW_H)
#define ___DARK___ARRAY_VIEW_H

#include <dark/core/std.h>
#include <dark/tool/array_view.h>
#include <dark/tool/buffer.h>
#include <dark/tool/foreach.h>
#include <dark/tool/iterator.h>

typedef struct Dark_Array_View Dark_Array_View;
struct Dark_Array_View
{
    size_t element_byte;
    size_t size;
    const void* data;
};

Dark_Buffer_View dark_array_view_to_buffer_view(Dark_Array_View array_view);

void dark_array_view_iterator(Dark_Array_View array_view, Dark_Iterator* iterator);
size_t dark_array_view_iterator_context_byte(void);

void dark_array_view_foreach(Dark_Array_View array_view, void* context, Dark_Foreach foreach);

int8_t dark_array_view_compare(const Dark_Array_View* a, const Dark_Array_View* b);

#endif // !defined(___DARK___ARRAY_VIEW_H)
