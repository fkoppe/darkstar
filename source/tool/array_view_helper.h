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

#if !defined(___DARK___ARRAY_VIEW_HELPER_H)
#define ___DARK___ARRAY_VIEW_HELPER_H

#include <dark/core/std.h>
#include <dark/tool/array_view.h>

typedef struct Dark_Array_View_Iterator_Context Dark_Array_View_Iterator_Context;
struct Dark_Array_View_Iterator_Context
{
    Dark_Array_View array_view;
    size_t index;
};

bool dark_array_view_iterator_done_is(Dark_Array_View_Iterator_Context* context);
void* dark_array_view_iterator_next(Dark_Array_View_Iterator_Context* context);
void* dark_array_view_iterator_peek(Dark_Array_View_Iterator_Context* context);
void dark_array_view_iterator_reset(Dark_Array_View_Iterator_Context* context);
size_t dark_array_view_iterator_skip(Dark_Array_View_Iterator_Context* context, size_t count);

#endif // !defined(___DARK___ARRAY_VIEW_HELPER_H)
