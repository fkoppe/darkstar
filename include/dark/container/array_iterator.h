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

#if !defined(___DARK___ARRAY_ITERATOR_H)
#define ___DARK___ARRAY_ITERATOR_H

#include <dark/container/array.h>
#include <dark/container/iterator.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Dark_Array_Iterator_Context Dark_Array_Iterator_Context;
struct Dark_Array_Iterator_Context
{
    Dark_Array* array;
    size_t index;
};

size_t dark_array_iterator_context_size(void);

Dark_Iterator_Struct dark_array_iterator_construct(void* context, Dark_Array* array);
void dark_array_iterator_destruct(Dark_Iterator* iterator);

Dark_Iterator* dark_array_iterator_new(Dark_Allocator* allocator, Dark_Array* array);
void dark_array_iterator_delete(Dark_Allocator* allocator, Dark_Iterator* iterator);

bool dark_array_allocator_next_is(void* context);
void* dark_array_allocator_next(void* context);

#endif // !defined(___DARK___ARRAY_ITERATOR_H)
