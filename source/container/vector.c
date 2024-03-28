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

void dark_vector_create_size(void* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Vector_Struct* const vector = vector_;

    dark_array_create_size(&vector->array, element_size_, capacity_, size_);
    vector->growth = growth_;
}

void dark_vector_create_capacity(void* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    Dark_Vector_Struct* const vector = vector_;

    dark_vector_create_size(vector, growth_, element_size_, capacity_, 0);
}

void dark_vector_create(void* const vector_, const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = vector_;

    dark_vector_create_capacity(vector, growth_, element_size_, 0);
}

void dark_vector_destroy(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    dark_array_destroy(&vector->array);
}

void* dark_vector_new_size(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Vector_Struct* const vector = malloc(sizeof(*vector));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_vector_create_size(vector, growth_, element_size_, capacity_, size_);

    return vector;
}

void* dark_vector_new_capacity(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    return dark_vector_new_size(growth_, element_size_, capacity_, 0);
}

void* dark_vector_new(const Dark_Growth growth_, const size_t element_size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    return dark_vector_new_capacity(growth_, element_size_, 0);
}

void dark_vector_delete(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    dark_vector_destroy(vector_);

    free(vector);
}

void* dark_vector_at(void* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(index_ < vector->array.size, DARK_ERROR_CONTAINER_INDEX);

    return dark_array_at(&vector->array, index_);
}

void* dark_vector_front(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_front(&vector->array);
}

void* dark_vector_back(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_back(&vector->array);
}

void* dark_vector_data(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_data(&vector->array);
}

void* dark_vector_emplace(void* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    //count_!

    Dark_Vector_Struct* const vector = vector_;

    if (0 == count_)
    {
        return NULL;
    }

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, vector->array.size + count_);

    return dark_array_emplace(&vector->array, index_, count_);
}

void* dark_vector_emplace_front_c(void* vector, size_t count);
void* dark_vector_emplace_front(void* vector);
void* dark_vector_emplace_back_c(void* vector, size_t count);
void* dark_vector_emplace_back(void* vector);

void dark_vector_push(void* const vector_, const size_t index_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    //count_!
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, vector->array.size + count_);

    dark_array_push(&vector->array, index_, count_, source_);
}

void dark_vector_insert(void* const vector_, const size_t index_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(index_ <= vector->array.size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(vector->array.size + 1 <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, index_, 1, element_);
}

void dark_vector_push_front(void* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    dark_vector_insert(vector, 0, element_);
}

void dark_vector_push_back(void* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(vector->array.size + 1 <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert(vector, vector->array.size, element_);
}

void dark_vector_push_back_c(void* const vector_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //count_!
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(vector->array.size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, vector->array.size, count_, source_);
}

void dark_vector_pop(void* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    //count_!

    Dark_Vector_Struct* const vector = vector_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(vector->array.size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= vector->array.size, DARK_ERROR_VALUE);

    dark_array_pop(&vector->array, index_, count_);
}

void dark_vector_erase(void* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + 1 <= vector->array.size, DARK_ERROR_VALUE);

    dark_vector_pop(vector, index_, 1);
}

void dark_vector_pop_front(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase(vector, 0);
}

void dark_vector_pop_back(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    DARK_ASSERT(vector->array.size >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_erase(vector, vector->array.size - 1);
}

size_t dark_vector_capacity(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_capacity(&vector->array);
}

void dark_vector_reserve(void* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity

    Dark_Vector_Struct* const vector = vector_;

    if (capacity_ <= vector->array.capacity)
    {
        return;
    }

    const size_t req = capacity_ - vector->array.capacity;
    const size_t grow_val = DARK_GROWTH_VALUE(vector->array.capacity, vector->growth);

    const size_t num = req / grow_val + (req % grow_val != 0 ? 1 : 0);

    dark_array_reserve_exact(&vector->array, vector->array.capacity + (num * grow_val));
}

void dark_vector_reserve_exact(void* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity

    Dark_Vector_Struct* const vector = vector_;

    dark_array_reserve_exact(&vector->array, capacity_);
}

void dark_vector_shrink_to_fit(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    dark_array_shrink_to_fit(&vector->array);
}

size_t dark_vector_size(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_size(&vector->array);
}

void dark_vector_resize(void* const vector_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //size_

    Dark_Vector_Struct* const vector = vector_;

    if(size_ > vector->array.capacity)
    {
        dark_vector_reserve(vector, size_);
    }

    dark_array_resize(&vector->array, size_);
}

void dark_vector_clear(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    dark_array_clear(&vector->array);
}

size_t dark_vector_element_size(void* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = vector_;

    return dark_array_element_size(&vector->array);
}
