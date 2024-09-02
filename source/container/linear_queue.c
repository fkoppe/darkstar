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
#include "linear_queue_helper.h"

#include <dark/container/container.h>
#include <dark/container/linear_queue_struct.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/math/math.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "linear_queue"

void dark_linear_queue_construct_capacity(Dark_Allocator* const allocator_, Dark_Linear_Queue* const linear_queue_, const Dark_Growth growth_, const size_t element_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);
    //capacity_

    linear_queue_->allocator = allocator_;

    dark_vector_construct_capacity(linear_queue_->allocator, &linear_queue_->vector, growth_, element_byte_, capacity_);

    linear_queue_->index = 0;
}

void dark_linear_queue_construct(Dark_Allocator* const allocator_, Dark_Linear_Queue* const linear_queue_, const Dark_Growth growth_, const size_t element_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);

    dark_linear_queue_construct_capacity(allocator_, linear_queue_, growth_, element_byte_, 0);
}

void dark_linear_queue_destruct(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    dark_vector_destruct(&linear_queue_->vector);
}

Dark_Linear_Queue* dark_linear_queue_new_capacity(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);
    //capacity_

    Dark_Linear_Queue* const linear_queue = dark_malloc(allocator_, sizeof(*linear_queue));
    DARK_ASSERT(NULL != linear_queue, DARK_ERROR_ALLOCATION);

    dark_linear_queue_construct_capacity(allocator_, linear_queue, growth_, element_byte_, capacity_);

    return linear_queue;
}

Dark_Linear_Queue* dark_linear_queue_new(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_byte_ > 0, DARK_ERROR_ZERO);

    return dark_linear_queue_new_capacity(allocator_, growth_, element_byte_, 0);
}

void dark_linear_queue_delete(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    dark_linear_queue_destruct(linear_queue_);

    dark_free(linear_queue_->allocator, linear_queue_, sizeof(*linear_queue_));
}

void* dark_linear_queue_at(Dark_Linear_Queue* const linear_queue_, const size_t index_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    //index_!

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < dark_linear_queue_size(linear_queue_), DARK_ERROR_CONTAINER_INDEX);

    return dark_vector_at(&linear_queue_->vector, index_ + linear_queue_->index);
}

void* dark_linear_queue_front(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_linear_queue_at(linear_queue_, 0);
}

void* dark_linear_queue_back(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_at(&linear_queue_->vector, dark_linear_queue_size(linear_queue_) - 1);
}

void* dark_linear_queue_data(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_linear_queue_front(linear_queue_);
}

Dark_Array dark_linear_queue_array(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    const Dark_Array array = { dark_linear_queue_element_byte(linear_queue_), dark_linear_queue_size(linear_queue_), dark_linear_queue_data(linear_queue_) };

    return array;
}

Dark_Array_View dark_linear_queue_array_view(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_array_view(&linear_queue_->vector);
}

void* dark_linear_queue_emplace(Dark_Linear_Queue* const linear_queue_, const size_t count_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) <= DARK_LINEAR_QUEUE_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_back(&linear_queue_->vector, count_);
}

Dark_Array dark_linear_queue_emplace_array(Dark_Linear_Queue* const linear_queue_, const size_t count_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) <= DARK_LINEAR_QUEUE_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_array_back(&linear_queue_->vector, count_);
}

void* dark_linear_queue_inplace(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) < DARK_LINEAR_QUEUE_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_inplace_back(&linear_queue_->vector);
}

Dark_Array dark_linear_queue_inplace_array(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) < DARK_LINEAR_QUEUE_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_inplace_array_back(&linear_queue_->vector);
}

void dark_linear_queue_push(Dark_Linear_Queue* const linear_queue_, const Dark_Array_View source_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.element_byte > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) <= DARK_LINEAR_QUEUE_SIZE_MAX - source_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(&linear_queue_->vector, dark_linear_queue_size(linear_queue_), source_);
}

void dark_linear_queue_insert(Dark_Linear_Queue* const linear_queue_, const void* const element_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) < DARK_VECTOR_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert_back(&linear_queue_->vector, element_);
}

void dark_linear_queue_pop(Dark_Linear_Queue* const linear_queue_, const size_t count_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) >= count_, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_back(&linear_queue_->vector, count_);
}

void dark_linear_queue_erase(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_queue_size(linear_queue_) >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase_back(&linear_queue_->vector);
}

size_t dark_linear_queue_capacity(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    return dark_vector_capacity(&linear_queue_->vector);
}

void dark_linear_queue_reserve(Dark_Linear_Queue* const linear_queue_, const size_t capacity_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    //capacity_

    dark_vector_reserve(&linear_queue_->vector, capacity_);
}

void dark_linear_queue_reserve_additional(Dark_Linear_Queue* const linear_queue_, const size_t additional_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(additional_ > 0, DARK_ERROR_ZERO);

    dark_vector_reserve_additional(&linear_queue_->vector, additional_);
}

void dark_linear_queue_reserve_exact(Dark_Linear_Queue* const linear_queue_, const size_t capacity_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    //capacity_

    dark_vector_reserve_exact(&linear_queue_->vector, capacity_);
}

void dark_linear_queue_shrink_to_fit(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    dark_vector_shrink_to_fit(&linear_queue_->vector);
}

size_t dark_linear_queue_size(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    return dark_vector_size(&linear_queue_->vector) - linear_queue_->index;
}

void dark_linear_queue_shrink(Dark_Linear_Queue* const linear_queue_, const size_t size_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    dark_vector_resize(&linear_queue_->vector, size_);
}

void dark_linear_queue_clear(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    dark_vector_clear(&linear_queue_->vector);
}

bool dark_linear_queue_done_is(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    return 0 == dark_linear_queue_size(linear_queue_);
}

void* dark_linear_queue_next(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_linear_queue_done_is(linear_queue_), DARK_ERROR_CONTAINER_EMPTY);

    void* const element = dark_linear_queue_front(linear_queue_);

    linear_queue_->index++;

    return element;
}

void* dark_linear_queue_peek(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_linear_queue_done_is(linear_queue_), DARK_ERROR_CONTAINER_EMPTY);

    return dark_linear_queue_front(linear_queue_);
}

void dark_linear_queue_reset(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    linear_queue_->index = 0;
}

size_t dark_linear_queue_skip(Dark_Linear_Queue* const linear_queue_, const size_t count_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    const size_t skipped = dark_min_zu(count_, dark_linear_queue_size(linear_queue_));

    linear_queue_->index += skipped;

    return skipped;
}

void dark_linear_queue_iterator(Dark_Linear_Queue* const linear_queue_, Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    DARK_ASSERT(iterator_->context == NULL || iterator_->byte > 0, DARK_ERROR_INTERNAL);

    if(iterator_->byte < sizeof(Dark_Linear_Queue_Iterator_Context*))
    {
        if(iterator_->byte > 0)
        {
            iterator_->context = dark_realloc(iterator_->context, iterator_->context, iterator_->byte, sizeof(Dark_Linear_Queue_Iterator_Context*));
            DARK_ASSERT(NULL != iterator_->context, DARK_ERROR_ALLOCATION);
        }
        else
        {
            iterator_->context = dark_malloc(iterator_->allocator, sizeof(Dark_Linear_Queue_Iterator_Context*));
            DARK_ASSERT(NULL != iterator_->context, DARK_ERROR_ALLOCATION);
        }

        iterator_->byte = sizeof(Dark_Linear_Queue_Iterator_Context*);
    }

    DARK_ASSERT(iterator_->context != NULL && iterator_->byte > 0, DARK_ERROR_INTERNAL);

    Dark_Linear_Queue_Iterator_Context* const context = iterator_->context;
    context->queue = linear_queue_;
    context->index = 0;

    iterator_->done_is = (void*)dark_linear_queue_iterator_done_is;
    iterator_->peek = (void*)dark_linear_queue_iterator_peek;
    iterator_->next = (void*)dark_linear_queue_iterator_next;
    iterator_->reset = (void*)dark_linear_queue_iterator_reset;
    iterator_->skip = (void*)dark_linear_queue_iterator_skip;
}

size_t dark_linear_queue_iterator_context_byte(void)
{
    return sizeof(Dark_Linear_Queue_Iterator_Context);
}

size_t dark_linear_queue_element_byte(Dark_Linear_Queue* const linear_queue_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);

    return dark_vector_element_byte(&linear_queue_->vector);
}

void dark_linear_queue_foreach(Dark_Linear_Queue* const linear_queue_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != linear_queue_, DARK_ERROR_NULL);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    dark_vector_foreach(&linear_queue_->vector, context_, foreach_);
}

size_t dark_linear_queue_struct_byte(void)
{
    return sizeof(Dark_Linear_Queue);
}
