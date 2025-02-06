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

#if !defined(___DARK___LINEAR_QUEUE_H)
#define ___DARK___LINEAR_QUEUE_H

#include <dark/container/vector.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>
#include <dark/tool/array.h>
#include <dark/tool/array_view.h>
#include <dark/tool/foreach.h>
#include <dark/tool/growth.h>
#include <dark/tool/iterator.h>

#define DARK_LINEAR_QUEUE_AT(linear_queue, index, type) \
(*(type*)dark_linear_queue_at((linear_queue), (index)))

#define DARK_LINEAR_QUEUE_FRONT(linear_queue, type) \
(*(type*)dark_linear_queue_front((linear_queue)))

#define DARK_LINEAR_QUEUE_BACK(linear_queue, type) \
(*(type*)dark_linear_queue_back((linear_queue)))

#define DARK_LINEAR_QUEUE_DATA(linear_queue, type) \
((type*)dark_linear_queue_data((linear_queue)))

#define DARK_LINEAR_QUEUE_SIZE_MAX DARK_VECTOR_SIZE_MAX

typedef struct Dark_Linear_Queue Dark_Linear_Queue;

void dark_linear_queue_construct_capacity(Dark_Allocator* allocator, Dark_Linear_Queue* linear_queue, Dark_Growth growth, size_t element_byte, size_t capacity);
void dark_linear_queue_construct(Dark_Allocator* allocator, Dark_Linear_Queue* linear_queue, Dark_Growth growth, size_t element_byte);
void dark_linear_queue_destruct(Dark_Linear_Queue* linear_queue);

Dark_Linear_Queue* dark_linear_queue_new_capacity(Dark_Allocator* allocator, Dark_Growth growth, size_t element_byte, size_t capacity);
Dark_Linear_Queue* dark_linear_queue_new(Dark_Allocator* allocator, Dark_Growth growth, size_t element_byte);
void dark_linear_queue_delete(Dark_Linear_Queue* linear_queue);

void* dark_linear_queue_at(Dark_Linear_Queue* linear_queue, size_t index);
void* dark_linear_queue_front(Dark_Linear_Queue* linear_queue);
void* dark_linear_queue_back(Dark_Linear_Queue* linear_queue);
void* dark_linear_queue_data(Dark_Linear_Queue* linear_queue);
Dark_Array dark_linear_queue_array(Dark_Linear_Queue* linear_queue);
Dark_Array_View dark_linear_queue_array_view(Dark_Linear_Queue* linear_queue);

void* dark_linear_queue_emplace(Dark_Linear_Queue* linear_queue, size_t count);
Dark_Array dark_linear_queue_emplace_array(Dark_Linear_Queue* linear_queue, size_t count);
void* dark_linear_queue_inplace(Dark_Linear_Queue* linear_queue);
Dark_Array dark_linear_queue_inplace_array(Dark_Linear_Queue* linear_queue);

void dark_linear_queue_push(Dark_Linear_Queue* linear_queue, Dark_Array_View source);
void dark_linear_queue_insert(Dark_Linear_Queue* linear_queue, const void* element);

void dark_linear_queue_pop(Dark_Linear_Queue* linear_queue, size_t count);
void dark_linear_queue_erase(Dark_Linear_Queue* linear_queue);

size_t dark_linear_queue_capacity(Dark_Linear_Queue* linear_queue);
void dark_linear_queue_reserve(Dark_Linear_Queue* linear_queue, size_t capacity);
void dark_linear_queue_reserve_additional(Dark_Linear_Queue* linear_queue, size_t additional);
void dark_linear_queue_reserve_exact(Dark_Linear_Queue* linear_queue, size_t capacity);
void dark_linear_queue_shrink_to_fit(Dark_Linear_Queue* linear_queue);

size_t dark_linear_queue_size(Dark_Linear_Queue* linear_queue);
void dark_linear_queue_shrink(Dark_Linear_Queue* linear_queue, size_t size);
void dark_linear_queue_clear(Dark_Linear_Queue* linear_queue);

bool dark_linear_queue_next_is(Dark_Linear_Queue* linear_queue);
void* dark_linear_queue_next(Dark_Linear_Queue* linear_queue);
void* dark_linear_queue_peek(Dark_Linear_Queue* linear_queue);
void dark_linear_queue_reset(Dark_Linear_Queue* linear_queue);
size_t dark_linear_queue_skip(Dark_Linear_Queue* linear_queue, size_t count);

void dark_linear_queue_iterator(Dark_Linear_Queue* linear_queue, Dark_Iterator* iterator);
size_t dark_linear_queue_iterator_context_byte(void);

size_t dark_linear_queue_element_byte(Dark_Linear_Queue* linear_queue);

void dark_linear_queue_foreach(Dark_Linear_Queue* linear_queue, void* context, Dark_Foreach foreach);

size_t dark_linear_queue_struct_byte(void);

#endif // !defined(___DARK___LINEAR_QUEUE_H)
