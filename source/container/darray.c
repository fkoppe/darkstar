/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

#include "container_helper.h"
#include "container_module.h"

#include <dark/container/container.h>
#include <dark/core/core.h>

#include <string.h>

#undef DARK_UNIT
#define DARK_UNIT "darray"

void* dark_darray_new_size(const size_t element_size_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_DArray* const darray = malloc(sizeof(*darray));
    DARK_ASSERT(NULL != darray, DARK_ERROR_ALLOCATION);

    darray->element_size = element_size_;
    darray->capacity = capacity_;
    darray->size = size_;
    darray->data = NULL;

    if (darray->capacity > 0)
    {
        darray->data = malloc(darray->element_size * darray->capacity);
        DARK_ASSERT(NULL != darray->data, DARK_ERROR_ALLOCATION);
    }

    return darray;
}

void* dark_darray_new_capacity(const size_t element_size_, const size_t capacity_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_

    return dark_darray_new_size(element_size_, capacity_, 0);
}

void* dark_darray_new(const size_t element_size_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);

    return dark_darray_new_capacity(element_size_, 0);
}

void dark_darray_delete(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    if (darray->capacity > 0)
    {
        free(darray->data);
    }

    free(darray);
}

void* dark_darray_at(void* const darray_, const size_t index_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //index_!

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(index_ < darray->size, DARK_ERROR_CONTAINER_INDEX);

    return darray->data + (darray->element_size * index_);
}

void* dark_darray_front(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return dark_darray_at(darray, 0);
}

void* dark_darray_back(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return dark_darray_at(darray, darray->size - 1);
}

void* dark_darray_data(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return dark_darray_at(darray, 0);
}

void dark_darray_push(void* const darray_, const size_t index_, const size_t count_, void* const array_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //index_!
    //count_!
    DARK_ASSERT(NULL != array_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(index_ <= darray->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(darray->size <= DARK_DARRAY_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    darray->size += count_;

    if (darray->size > darray->capacity)
    {
        if (darray->capacity > 0)
        {
            darray->data = realloc(darray->data, darray->element_size * (darray->capacity + count_));
        }
        else
        {
            darray->data = malloc(darray->element_size);
        }

        darray->capacity = darray->size;

        DARK_ASSERT(NULL != darray->data, DARK_ERROR_ALLOCATION);
    }

    if (index_ < darray->size)
    {
        memmove(darray->data + (darray->element_size * (index_ + count_)), darray->data + (darray->element_size * index_), darray->element_size * (darray->size - index_ - count_));
    }

    memcpy(darray->data + (darray->element_size * index_), array_, darray->element_size * count_);
}

void dark_darray_insert(void* const darray_, const size_t index_, void* const element_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(index_ <= darray->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(darray->size + 1 <= DARK_DARRAY_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_darray_push(darray, index_, 1, element_);
}

void dark_darray_push_front(void* const darray_, void* const element_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    dark_darray_insert(darray, 0, element_);
}

void dark_darray_push_back(void* const darray_, void* const element_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(darray->size + 1 <= DARK_DARRAY_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_darray_insert(darray, darray->size, element_);
}

void dark_darray_pop(void* const darray_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //index_!
    //count_!

    Dark_DArray* const darray = darray_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(darray->size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= darray->size, DARK_ERROR_VALUE);

    darray->size -= count_;

    if (0 == darray->size)
    {
        return;
    }

    if (index_ + count_ - 1 >= darray->size)
    {
        return;
    }

    memmove(darray->data + (darray->element_size * index_), darray->data + (darray->element_size * (index_ + count_)), darray->element_size * (darray->size - index_ - count_ + 1));
}

void dark_darray_erase(void* const darray_, const size_t index_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //index_!

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(darray->size >= 1, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + 1 <= darray->size, DARK_ERROR_VALUE);

    dark_darray_pop(darray, index_, 1);
}

void dark_darray_pop_front(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(darray->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_darray_erase(darray, 0);
}

void dark_darray_pop_back(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    DARK_ASSERT(darray->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_darray_erase(darray, darray->size - 1);
}

size_t dark_darray_capacity(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return darray->capacity;
}

void dark_darray_reserve_exact(void* const darray_, const size_t capacity_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //capacity

    Dark_DArray* const darray = darray_;

    if (darray->capacity == capacity_)
    {
        return;
    }

    if (0 == capacity_)
    {
        free(darray->data);
    }
    else
    {
        if (darray->capacity > 0)
        {
            darray->data = realloc(darray->data, darray->element_size * capacity_);
        }
        else
        {
            darray->data = malloc(darray->element_size * capacity_);
        }

        DARK_ASSERT(NULL != darray->data, DARK_ERROR_ALLOCATION);

    }

    darray->size = DARK_MIN(darray->size, capacity_);

    darray->capacity = capacity_;
}

void dark_darray_shrink_to_fit(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    if(darray->capacity == darray->size)
    {
        return;
    }

    darray->capacity = darray->size;

    if(darray->capacity > 0)
    {
        darray->data = realloc(darray->data, darray->element_size * darray->capacity);
        DARK_ASSERT(NULL != darray->data, DARK_ERROR_ALLOCATION);
    }
    else
    {
        free(darray->data);
    }
}

size_t dark_darray_size(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return darray->size;
}

void dark_darray_resize(void* const darray_, const size_t size_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);
    //size_

    Dark_DArray* const darray = darray_;

    darray->size = size_;

    if(darray->size > darray->capacity)
    {
        darray->capacity = darray->size;

        darray->data = realloc(darray->data, darray->element_size * darray->capacity);
        DARK_ASSERT(NULL != darray->data, DARK_ERROR_ALLOCATION);
    }
}

void dark_darray_clear(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    darray->size = 0;
}

size_t dark_darray_element_size(void* const darray_)
{
    DARK_ASSERT(NULL != darray_, DARK_ERROR_NULL);

    Dark_DArray* const darray = darray_;

    return darray->element_size;
}
