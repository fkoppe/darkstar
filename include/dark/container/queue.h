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

#if !defined(___DARK___QUEUE_H)
#define ___DARK___QUEUE_H

#include <dark/container/vector.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>
#include <dark/tool/array.h>
#include <dark/tool/array_view.h>
#include <dark/tool/foreach.h>
#include <dark/tool/growth.h>
#include <dark/tool/iterator.h>

#define DARK_QUEUE_AT(queue, index, type) \
(*(type*)dark_queue_at((queue), (index)))

#define DARK_QUEUE_FRONT(queue, type) \
(*(type*)dark_queue_front((queue)))

#define DARK_QUEUE_BACK(queue, type) \
(*(type*)dark_queue_back((queue)))

#define DARK_QUEUE_DATA(queue, type) \
((type*)dark_queue_data((queue)))

#define DARK_QUEUE_SIZE_MAX DARK_VECTOR_SIZE_MAX

typedef struct Dark_Queue Dark_Queue;

void dark_queue_construct_capacity(Dark_Allocator* allocator, Dark_Queue* queue, Dark_Growth growth, size_t element_byte, size_t capacity);
void dark_queue_construct(Dark_Allocator* allocator, Dark_Queue* queue, Dark_Growth growth, size_t element_byte);
void dark_queue_destruct(Dark_Queue* queue);

Dark_Queue* dark_queue_new_capacity(Dark_Allocator* allocator, Dark_Growth growth, size_t element_byte, size_t capacity);
Dark_Queue* dark_queue_new(Dark_Allocator* allocator, Dark_Growth growth, size_t element_byte);
void dark_queue_delete(Dark_Queue* queue);

void* dark_queue_at(Dark_Queue* queue, size_t index);
void* dark_queue_front(Dark_Queue* queue);
void* dark_queue_back(Dark_Queue* queue);
void* dark_queue_data(Dark_Queue* queue);
Dark_Array dark_queue_array(Dark_Queue* queue);
Dark_Array_View dark_queue_array_view(Dark_Queue* queue);

void* dark_queue_emplace(Dark_Queue* queue, size_t count);
Dark_Array dark_queue_emplace_array(Dark_Queue* queue, size_t count);
void* dark_queue_inplace(Dark_Queue* queue);
Dark_Array dark_queue_inplace_array(Dark_Queue* queue);

void dark_queue_push(Dark_Queue* queue, Dark_Array_View source);
void dark_queue_insert(Dark_Queue* queue, const void* element);

void dark_queue_pop(Dark_Queue* queue, size_t count);
void dark_queue_erase(Dark_Queue* queue);

size_t dark_queue_capacity(Dark_Queue* queue);
void dark_queue_reserve(Dark_Queue* queue, size_t capacity);
void dark_queue_reserve_additional(Dark_Queue* queue, size_t additional);
void dark_queue_reserve_exact(Dark_Queue* queue, size_t capacity);
void dark_queue_shrink_to_fit(Dark_Queue* queue);

size_t dark_queue_size(Dark_Queue* queue);
void dark_queue_shrink(Dark_Queue* queue, size_t size);
void dark_queue_clear(Dark_Queue* queue);

bool dark_queue_done(Dark_Queue* queue);
void* dark_queue_next(Dark_Queue* queue);
void* dark_queue_peek(Dark_Queue* queue);
void dark_queue_reset(Dark_Queue* queue);
size_t dark_queue_skip(Dark_Queue* queue, size_t count);

Dark_Iterator* dark_queue_iterate(Dark_Queue* queue);

size_t dark_queue_element_byte(Dark_Queue* queue);

void dark_queue_foreach(Dark_Queue* queue, void* context, Dark_Foreach foreach);

size_t dark_queue_struct_byte(void);

#endif // !defined(___DARK___QUEUE_H)
