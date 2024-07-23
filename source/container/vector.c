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
#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/memory/memory.h>

#undef DARK_UNIT
#define DARK_UNIT "vector"

static const size_t DARK_CONTAINER_SIZE_MAX = SIZE_MAX;

size_t dark_vector_size_max(void)
{
    return DARK_CONTAINER_SIZE_MAX;
}

size_t dark_vector_struct_size(void)
{
    return sizeof(Dark_Vector_Struct);
}

void dark_vector_create_size(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_LOGIC);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(capacity_ > 0)
    {
        vector->array.data = dark_balloc(allocator_, element_size_, capacity_);
    }

    vector->array.size = size_;
    vector->array.element_size = element_size_;
    vector->capacity = capacity_;
    vector->growth = growth_;
}

void dark_vector_create_capacity(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    //capacity_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_create_size(allocator_, (Dark_Vector*)vector, growth_, element_size_, capacity_, 0);
}

void dark_vector_create(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_create_capacity(allocator_, (Dark_Vector*)vector, growth_, element_size_, 0);
}

void dark_vector_destroy(Dark_Allocator* const allocator_, Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(vector->capacity > 0)
    {
        dark_bfree(allocator_, vector->array.data, vector->array.element_size, vector->capacity);
    }
}

Dark_Vector* dark_vector_new_size(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_LOGIC);

    Dark_Vector_Struct* const vector = dark_malloc(allocator_, sizeof(*vector));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_vector_create_size(allocator_, (Dark_Vector*)vector, growth_, element_size_, capacity_, size_);

    return (Dark_Vector*)vector;
}

Dark_Vector* dark_vector_new_capacity(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    //capacity_

    return dark_vector_new_size(allocator_, growth_, element_size_, capacity_, 0);
}

Dark_Vector* dark_vector_new(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);

    return dark_vector_new_capacity(allocator_, growth_, element_size_, 0);
}

void dark_vector_delete(Dark_Allocator* const allocator_, Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_destroy(allocator_, (Dark_Vector*)vector);

    dark_free(allocator_, vector, sizeof(*vector));
}

void* dark_vector_at(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < vector->array.size, DARK_ERROR_CONTAINER_INDEX);

    return vector->array.data + (vector->array.element_size * index_);
}
void* dark_vector_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_at((Dark_Vector*)vector, 0);
}

void* dark_vector_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_at((Dark_Vector*)vector, vector->array.size - 1);
}

void* dark_vector_data(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_vector_at((Dark_Vector*)vector, 0);
}

Dark_Array dark_vector_array(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return vector->array;
}

Dark_Array_View dark_vector_array_view(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_view(vector->array);
}

void* dark_vector_emplace(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(allocator_, (Dark_Vector*)vector, count_);

    vector->array.size += count_;

    if (index_ < vector->array.size - count_)
    {
        dark_memmove(vector->array.data + (vector->array.element_size * (index_ + count_)), vector->array.data + (vector->array.element_size * index_), vector->array.element_size * (vector->array.size - index_ - count_));
    }

    return vector->array.data + (vector->array.element_size * index_);
}

void* dark_vector_emplace_front(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace(allocator_, (Dark_Vector*)vector, 0, count_);
}

void* dark_vector_emplace_back(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace(allocator_, (Dark_Vector*)vector, vector->array.size, count_);
}

void* dark_vector_inplace(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace(allocator_, (Dark_Vector*)vector, index_, 1);
}

void* dark_vector_inplace_front(Dark_Allocator* const allocator_, Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_front(allocator_, (Dark_Vector*)vector, 1);
}

void* dark_vector_inplace_back(Dark_Allocator* const allocator_, Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_back(allocator_, (Dark_Vector*)vector, 1);
}

void dark_vector_push(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t index_, const Dark_Array_View source_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.element_size > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - source_.size, DARK_ERROR_OVERFLOW);

    void* const destination = dark_vector_emplace(allocator_, (Dark_Vector*)vector, index_, source_.size);

    dark_memcpy(destination, source_.data, vector->array.element_size * source_.size);
}

void dark_vector_push_front(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const Dark_Array_View source_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.element_size > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - source_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(allocator_, (Dark_Vector*)vector, 0, source_);
}

void dark_vector_push_back(Dark_Allocator* const allocator_, Dark_Vector* const vector_, Dark_Array_View source_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);
    DARK_ASSERT(source_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(source_.element_size > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - source_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(allocator_, (Dark_Vector*)vector, vector->array.size, source_);
}

void dark_vector_insert(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t index_, const void* element_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    const Dark_Array_View array_view = { element_, 1, vector->array.element_size };

    dark_vector_push(allocator_, (Dark_Vector*)vector, index_, array_view);
}

void dark_vector_insert_front(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const void* element_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    const Dark_Array_View array_view = { element_, 1, vector->array.element_size };

    dark_vector_push_front(allocator_, (Dark_Vector*)vector, array_view);
}

void dark_vector_insert_back(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const void* element_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    const Dark_Array_View array_view = { element_, 1, vector->array.element_size };

    dark_vector_push_back(allocator_, (Dark_Vector*)vector, array_view);
}

void dark_vector_pop(Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= vector->array.size, DARK_ERROR_VALUE);

    vector->array.size -= count_;

    if (0 == vector->array.size)
    {
        return;
    }

    if (index_ + count_ >= vector->array.size + count_)
    {
        return;
    }

    dark_memmove(vector->array.data + (vector->array.element_size * index_), vector->array.data + (vector->array.element_size * (index_ + count_)), vector->array.element_size * (vector->array.size - index_));
}

void dark_vector_pop_front(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= count_, DARK_ERROR_UNDERFLOW);

    dark_vector_pop((Dark_Vector*)vector, 0, count_);
}

void dark_vector_pop_back(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= count_, DARK_ERROR_UNDERFLOW);

    dark_vector_pop((Dark_Vector*)vector, vector->array.size - count_, count_);
}

void dark_vector_erase(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + 1 <= vector->array.size, DARK_ERROR_VALUE);

    dark_vector_pop((Dark_Vector*)vector, index_, 1);
}

void dark_vector_erase_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_front((Dark_Vector*)vector, 1);
}

void dark_vector_erase_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_back((Dark_Vector*)vector, 1);
}

size_t dark_vector_capacity(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return vector->capacity;
}

void dark_vector_reserve_exact(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if (vector->capacity == capacity_)
    {
        return;
    }

    if (0 == capacity_)
    {
        dark_bfree(allocator_, vector->array.data, vector->array.element_size, vector->capacity);
    }
    else
    {
        if (vector->capacity > 0)
        {
            vector->array.data = dark_brealloc(allocator_, vector->array.data, vector->array.element_size, vector->capacity, capacity_);
        }
        else
        {
            vector->array.data = dark_balloc(allocator_, vector->array.element_size, capacity_);
        }

        DARK_ASSERT(NULL != vector->array.data, DARK_ERROR_ALLOCATION);

    }

    vector->array.size = dark_min_zu(vector->array.size, capacity_);
    vector->capacity = capacity_;
}

void dark_vector_reserve(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(capacity_ > vector->capacity)
    {
        dark_vector_reserve_exact(allocator_, vector_, vector->capacity + vector->growth(vector->capacity, capacity_));
    }
}

void dark_vector_reserve_additional(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t additional_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_reserve(allocator_, vector_, vector->array.size + additional_);
}

void dark_vector_shrink_to_fit(Dark_Allocator* const allocator_, Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_reserve_exact(allocator_, vector_, vector->array.size);
}

size_t dark_vector_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return vector->array.size;
}

void dark_vector_resize(Dark_Allocator* const allocator_, Dark_Vector* const vector_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //size_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(size_ > vector->capacity)
    {
        dark_vector_reserve(allocator_, vector_, size_);
    }

    vector->array.size = size_;
}

void dark_vector_clear(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    vector->array.size = 0;
}

size_t dark_vector_element_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return vector->array.element_size;
}
