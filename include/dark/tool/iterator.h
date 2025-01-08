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

#if !defined(___DARK___ITERATOR_H)
#define ___DARK___ITERATOR_H

#include <dark/core/error.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Dark_Iterator Dark_Iterator;

static const Dark_Error DARK_ERROR_ITERATOR = { &DARK_ERROR_LOGIC, "iterator", "no more element available" };

void dark_iterator_construct_context(Dark_Allocator* allocator, Dark_Iterator* iterator, size_t context_byte);
void dark_iterator_construct(Dark_Allocator* allocator, Dark_Iterator* iterator);
void dark_iterator_destruct(Dark_Iterator* iterator);

Dark_Iterator* dark_iterator_new_context(Dark_Allocator* allocator, size_t context_byte);
Dark_Iterator* dark_iterator_new(Dark_Allocator* allocator);
void dark_iterator_delete(Dark_Iterator* iterator);

bool dark_iterator_done_is(Dark_Iterator* iterator);
void* dark_iterator_next(Dark_Iterator* iterator);
void* dark_iterator_peek(Dark_Iterator* iterator);
void dark_iterator_reset(Dark_Iterator* iterator);
size_t dark_iterator_skip(Dark_Iterator* iterator, size_t count);

#endif // !defined(___DARK___ITERATOR_H)
