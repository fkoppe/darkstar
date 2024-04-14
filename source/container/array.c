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

#include <string.h>

#undef DARK_UNIT
#define DARK_UNIT "array"

size_t dark_array_struct_size(void)
{
    return sizeof(Dark_Array_Struct);
}

void dark_array_create_size(Dark_Array* const array_, const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    array->element_size = element_size_;
    array->capacity = capacity_;
    array->size = size_;
    array->data = NULL;

    if (array->capacity > 0)
    {
        array->data = malloc(array->element_size * array->capacity);
        DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);
    }
}

void dark_array_create_capacity(Dark_Array* const array_, const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    dark_array_create_size((Dark_Array*)array, element_size_, capacity_, 0);
}

void dark_array_create(Dark_Array* array_, size_t element_size_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    dark_array_create_capacity((Dark_Array*)array, element_size_, 0);
}

void dark_array_destroy(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    if (array->capacity > 0)
    {
        free(array->data);
    }
}

Dark_Array* dark_array_new_size(const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Array_Struct* const array = malloc(sizeof(*array));
    DARK_ASSERT(NULL != array, DARK_ERROR_ALLOCATION);

    dark_array_create_size((Dark_Array*)array, element_size_, capacity_, size_);

    return (Dark_Array*)array;
}

Dark_Array* dark_array_new_capacity(const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    return dark_array_new_size(element_size_, capacity_, 0);
}

Dark_Array* dark_array_new(const size_t element_size_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    return dark_array_new_capacity(element_size_, 0);
}

void dark_array_delete(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    dark_array_destroy((Dark_Array*)array);

    free(array);
}

void* dark_array_at(Dark_Array* const array_, const size_t index_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < array->size, DARK_ERROR_CONTAINER_INDEX);

    return array->data + (array->element_size * index_);
}

void* dark_array_front(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_at((Dark_Array*)array, 0);
}

void* dark_array_back(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_at((Dark_Array*)array, array->size - 1);
}

void* dark_array_data(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_array_at((Dark_Array*)array, 0);
}

void* dark_array_emplace(Dark_Array* const array_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(index_ <= array->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    array->size += count_;

    if (array->size > array->capacity)
    {
        if (array->capacity > 0)
        {
            array->data = realloc(array->data, array->element_size * (array->capacity + count_));
        }
        else
        {
            array->data = malloc(array->element_size * count_);
        }

        array->capacity = array->size;

        DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);
    }

    if (index_ < array->size - count_)
    {
        memmove(array->data + (array->element_size * (index_ + count_)), array->data + (array->element_size * index_), array->element_size * (array->size - index_ - count_));
    }

    return array->data + (array->element_size * index_);
}

void* dark_array_emplace_front(Dark_Array* array_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_array_emplace((Dark_Array*)array, 0, count_);
}

void* dark_array_emplace_back(Dark_Array* array_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_array_emplace((Dark_Array*)array, array->size, count_);
}

void* dark_array_inplace(Dark_Array* const array_, const size_t index_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(index_ <= array->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_array_emplace((Dark_Array*)array, index_, 1);
}

void* dark_array_inplace_front(Dark_Array* array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_array_emplace_front((Dark_Array*)array, 1);
}

void* dark_array_inplace_back(Dark_Array* array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_array_emplace_back((Dark_Array*)array, 1);
}

void dark_array_push(Dark_Array* const array_, const size_t index_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(index_ <= array->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    void* const destination = dark_array_emplace((Dark_Array*)array, index_, count_);

    memcpy(destination, source_, array->element_size * count_);
}

void dark_array_push_front(Dark_Array* const array_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_array_push((Dark_Array*)array, 0, count_, source_);
}

void dark_array_push_back(Dark_Array* const array_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_array_push((Dark_Array*)array, array->size, count_, source_);
}

void dark_array_insert(Dark_Array* const array_, const size_t index_, const void* const element_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(index_ <= array->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_array_push((Dark_Array*)array, index_, 1, element_);
}

void dark_array_insert_front(Dark_Array* const array_, const void* const element_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_array_push_front((Dark_Array*)array, 1, element_);
}

void dark_array_insert_back(Dark_Array* const array_, const void* const element_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_array_push_back((Dark_Array*)array, 1, element_);
}

void dark_array_pop(Dark_Array* const array_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= array->size, DARK_ERROR_VALUE);

    array->size -= count_;

    if (0 == array->size)
    {
        return;
    }

    if (index_ + count_ - 1 >= array->size + count_)
    {
        return;
    }

    memmove(array->data + (array->element_size * index_), array->data + (array->element_size * (index_ + count_)), array->element_size * (array->size - index_));
}

void dark_array_pop_front(Dark_Array* const array_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= count_, DARK_ERROR_UNDERFLOW);

    dark_array_pop((Dark_Array*)array, 0, count_);
}

void dark_array_pop_back(Dark_Array* const array_, const size_t count_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= count_, DARK_ERROR_UNDERFLOW);

    dark_array_pop((Dark_Array*)array, array->size - count_, count_);
}

void dark_array_erase(Dark_Array* const array_, const size_t index_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //index_!

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= 1, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + 1 <= array->size, DARK_ERROR_VALUE);

    dark_array_pop((Dark_Array*)array, index_, 1);
}

void dark_array_erase_front(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_array_pop_front((Dark_Array*)array, 1);
}

void dark_array_erase_back(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    DARK_ASSERT(array->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_array_pop_back((Dark_Array*)array, 1);
}

size_t dark_array_capacity(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    return array->capacity;
}

void dark_array_reserve_exact(Dark_Array* const array_, const size_t capacity_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //capacity

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    if (array->capacity == capacity_)
    {
        return;
    }

    if (0 == capacity_)
    {
        free(array->data);
    }
    else
    {
        if (array->capacity > 0)
        {
            array->data = realloc(array->data, array->element_size * capacity_);
        }
        else
        {
            array->data = malloc(array->element_size * capacity_);
        }

        DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);

    }

    array->size = DARK_MIN(array->size, capacity_);

    array->capacity = capacity_;
}

void dark_array_shrink_to_fit(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    if(array->capacity == array->size)
    {
        return;
    }

    array->capacity = array->size;

    if(array->capacity > 0)
    {
        array->data = realloc(array->data, array->element_size * array->capacity);
        DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);
    }
    else
    {
        free(array->data);
    }
}

size_t dark_array_size(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    return array->size;
}

void dark_array_resize(Dark_Array* const array_, const size_t size_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);
    //size_

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    array->size = size_;

    if(array->size > array->capacity)
    {
        array->capacity = array->size;

        if(array->capacity > 0)
        {
            array->data = malloc(array->element_size * array->capacity);
            DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);
        }
        else
        {
            array->data = realloc(array->data, array->element_size * array->capacity);
            DARK_ASSERT(NULL != array->data, DARK_ERROR_ALLOCATION);
        }
    }
}

void dark_array_clear(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    array->size = 0;
}

size_t dark_array_element_size(Dark_Array* const array_)
{
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_Array_Struct* const array = (Dark_Array_Struct*)array_;

    return array->element_size;
}
