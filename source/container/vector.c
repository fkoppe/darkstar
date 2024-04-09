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

#undef DARK_UNIT
#define DARK_UNIT "vector"

size_t dark_vector_struct_size(void)
{
    return sizeof(Dark_Vector_Struct);
}

void dark_vector_create_size(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_array_create_size((Dark_Array*)&vector->array, element_size_, capacity_, size_);
    vector->growth = growth_;
}

void dark_vector_create_capacity(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_create_size((Dark_Vector*)vector, growth_, element_size_, capacity_, 0);
}

void dark_vector_create(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_create_capacity((Dark_Vector*)vector, growth_, element_size_, 0);
}

void dark_vector_destroy(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_array_destroy((Dark_Array*)&vector->array);
}

Dark_Vector* dark_vector_new_size(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Vector_Struct* const vector = malloc(sizeof(*vector));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_vector_create_size((Dark_Vector*)vector, growth_, element_size_, capacity_, size_);

    return (Dark_Vector*)vector;
}

Dark_Vector* dark_vector_new_capacity(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    return dark_vector_new_size(growth_, element_size_, capacity_, 0);
}

Dark_Vector* dark_vector_new(const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    return dark_vector_new_capacity(growth_, element_size_, 0);
}

void dark_vector_delete(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_destroy(vector_);

    free(vector);
}

void* dark_vector_at(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < vector->array.size, DARK_ERROR_CONTAINER_INDEX);

    return dark_array_at((Dark_Array*)&vector->array, index_);
}

void* dark_vector_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_front((Dark_Array*)&vector->array);
}

void* dark_vector_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_back((Dark_Array*)&vector->array);
}

void* dark_vector_data(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_data((Dark_Array*)&vector->array);
}

void* dark_vector_emplace(Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve((Dark_Vector*)vector, vector->array.size + count_);

    return dark_array_emplace((Dark_Array*)&vector->array, index_, count_);
}

void* dark_vector_emplace_front_c(Dark_Vector* vector, size_t count);
void* dark_vector_emplace_front(Dark_Vector* vector);
void* dark_vector_emplace_back_c(Dark_Vector* vector, size_t count);
void* dark_vector_emplace_back(Dark_Vector* vector);

void dark_vector_push(Dark_Vector* const vector_, const size_t index_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve((Dark_Vector*)vector, vector->array.size + count_);

    dark_array_push((Dark_Array*)&vector->array, index_, count_, source_);
}

void dark_vector_insert(Dark_Vector* const vector_, const size_t index_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push((Dark_Vector*)vector, index_, 1, element_);
}

void dark_vector_push_front(Dark_Vector* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_insert((Dark_Vector*)vector, 0, element_);
}

void dark_vector_push_back(Dark_Vector* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert((Dark_Vector*)vector, vector->array.size, element_);
}

void dark_vector_push_back_c(Dark_Vector* const vector_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push((Dark_Vector*)vector, vector->array.size, count_, source_);
}

void dark_vector_pop(Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= vector->array.size, DARK_ERROR_VALUE);

    dark_array_pop((Dark_Array*)&vector->array, index_, count_);
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

void dark_vector_pop_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase((Dark_Vector*)vector, 0);
}

void dark_vector_pop_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase((Dark_Vector*)vector, vector->array.size - 1);
}

size_t dark_vector_capacity(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return dark_array_capacity((Dark_Array*)&vector->array);
}

void dark_vector_reserve(Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if (capacity_ <= vector->array.capacity)
    {
        return;
    }

    const size_t req = capacity_ - vector->array.capacity;
    const size_t grow_val = DARK_GROWTH_VALUE(vector->array.capacity, vector->growth);

    const size_t num = req / grow_val + (req % grow_val != 0 ? 1 : 0);

    dark_array_reserve_exact((Dark_Array*)&vector->array, vector->array.capacity + (num * grow_val));
}

void dark_vector_reserve_exact(Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_array_reserve_exact((Dark_Array*)&vector->array, capacity_);
}

void dark_vector_shrink_to_fit(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_array_shrink_to_fit((Dark_Array*)&vector->array);
}

size_t dark_vector_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return dark_array_size((Dark_Array*)&vector->array);
}

void dark_vector_resize(Dark_Vector* const vector_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //size_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(size_ > vector->array.capacity)
    {
        dark_vector_reserve((Dark_Vector*)vector, size_);
    }

    dark_array_resize((Dark_Array*)&vector->array, size_);
}

void dark_vector_clear(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_array_clear((Dark_Array*)&vector->array);
}

size_t dark_vector_element_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return dark_array_element_size((Dark_Array*)&vector->array);
}
