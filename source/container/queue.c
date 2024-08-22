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

#include "container_module.h"

#include <dark/container/container.h>
#include <dark/container/queue_struct.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/math/math.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "queue"

void dark_queue_construct_capacity(Dark_Allocator* const allocator_, Dark_Queue* const queue_, const Dark_Growth growth_, const size_t element_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);
    //capacity_

    queue_->allocator = allocator_;

    dark_vector_construct_capacity(queue_->allocator, &queue_->vector, growth_, element_byte_, capacity_);

    queue_->iterator.allocator = NULL;
    queue_->iterator.done = (void*)dark_queue_done;
    queue_->iterator.next = (void*)dark_queue_next;
    queue_->iterator.peek = (void*)dark_queue_peek;
    queue_->iterator.reset = (void*)dark_queue_reset;;
    queue_->iterator.skip = (void*)dark_queue_skip;
    queue_->iterator.context = queue_;
    queue_->index = 0;
}

void dark_queue_construct(Dark_Allocator* const allocator_, Dark_Queue* const queue_, const Dark_Growth growth_, const size_t element_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);

    dark_queue_construct_capacity(allocator_, queue_, growth_, element_byte_, 0);
}

void dark_queue_destruct(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    dark_vector_destruct(&queue_->vector);
}

Dark_Queue* dark_queue_new_capacity(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);
    //capacity_

    Dark_Queue* const queue = dark_malloc(allocator_, sizeof(*queue));
    DARK_ASSERT(NULL != queue, DARK_ERROR_ALLOCATION);

    dark_queue_construct_capacity(allocator_, queue, growth_, element_byte_, capacity_);

    return queue;
}

Dark_Queue* dark_queue_new(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);

    return dark_queue_new_capacity(allocator_, growth_, element_byte_, 0);
}

void dark_queue_delete(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    dark_queue_destruct(queue_);

    dark_free(queue_->allocator, queue_, sizeof(*queue_));
}

void* dark_queue_at(Dark_Queue* const queue_, const size_t index_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    //index_!

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < dark_queue_size(queue_), DARK_ERROR_CONTAINER_INDEX);

    return dark_vector_at(&queue_->vector, index_);
}

void* dark_queue_front(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_front(&queue_->vector);
}

void* dark_queue_back(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_back(&queue_->vector);
}

void* dark_queue_data(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_data(&queue_->vector);
}

Dark_Array dark_queue_array(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_array(&queue_->vector);
}

Dark_Array_View dark_queue_array_view(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_array_view(&queue_->vector);
}

void* dark_queue_emplace(Dark_Queue* const queue_, const size_t count_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_queue_size(queue_) <= DARK_QUEUE_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_back(&queue_->vector, count_);
}

Dark_Array dark_queue_emplace_array(Dark_Queue* const queue_, const size_t count_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_queue_size(queue_) <= DARK_QUEUE_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_array_back(&queue_->vector, count_);
}

void* dark_queue_inplace(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) < DARK_QUEUE_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_inplace_back(&queue_->vector);
}

Dark_Array dark_queue_inplace_array(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) < DARK_QUEUE_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_inplace_array_back(&queue_->vector);
}

void dark_queue_push(Dark_Queue* const queue_, const Dark_Array_View source_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.element_byte > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_queue_size(queue_) <= DARK_QUEUE_SIZE_MAX - source_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(&queue_->vector, dark_queue_size(queue_), source_);
}

void dark_queue_insert(Dark_Queue* const queue_, const void* const element_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) < DARK_VECTOR_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert_back(&queue_->vector, element_);
}

void dark_queue_pop(Dark_Queue* const queue_, const size_t count_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_queue_size(queue_) >= count_, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_back(&queue_->vector, count_);
}

void dark_queue_erase(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_queue_size(queue_) >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase_back(&queue_->vector);
}

size_t dark_queue_capacity(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    return dark_vector_capacity(&queue_->vector);
}

void dark_queue_reserve(Dark_Queue* const queue_, const size_t capacity_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    //capacity_

    dark_vector_reserve(&queue_->vector, capacity_);
}

void dark_queue_reserve_additional(Dark_Queue* const queue_, const size_t additional_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(additional_ > 0, DARK_ERROR_ZERO);

    dark_vector_reserve_additional(&queue_->vector, additional_);
}

void dark_queue_reserve_exact(Dark_Queue* const queue_, const size_t capacity_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    //capacity_

    dark_vector_reserve_exact(&queue_->vector, capacity_);
}

void dark_queue_shrink_to_fit(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    dark_vector_shrink_to_fit(&queue_->vector);
}

size_t dark_queue_size(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    return dark_vector_size(&queue_->vector);
}

void dark_queue_shrink(Dark_Queue* const queue_, const size_t size_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    dark_vector_resize(&queue_->vector, size_);
}

void dark_queue_clear(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    dark_vector_clear(&queue_->vector);
}

bool dark_queue_done(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    return queue_->index >= dark_queue_size(queue_);
}

void* dark_queue_next(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_queue_done(queue_), DARK_ERROR_ITERATOR);

    queue_->index++;

    return dark_queue_at(queue_, queue_->index - 1);
}

void* dark_queue_peek(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_queue_done(queue_), DARK_ERROR_ITERATOR);

    return dark_queue_at(queue_, queue_->index);
}

void dark_queue_reset(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    queue_->index = 0;
}

size_t dark_queue_skip(Dark_Queue* const queue_, const size_t count_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    const size_t skipped = dark_min_zu(count_, dark_queue_size(queue_) - queue_->index);

    queue_->index += skipped;

    return skipped;
}

Dark_Iterator* dark_queue_iterate(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    return &queue_->iterator;
}

size_t dark_queue_element_byte(Dark_Queue* const queue_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);

    return dark_vector_element_byte(&queue_->vector);
}

void dark_queue_foreach(Dark_Queue* const queue_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != queue_, DARK_ERROR_NULL);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    dark_vector_foreach(&queue_->vector, context_, foreach_);
}

size_t dark_queue_struct_byte(void)
{
    return sizeof(Dark_Queue);
}
