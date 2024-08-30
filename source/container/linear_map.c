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
//#include "linear_map_helper.h"

#include <dark/container/container.h>
#include <dark/container/linear_map_struct.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "linear_map"

void dark_linear_map_construct_capacity(Dark_Allocator* const allocator_, Dark_Linear_Map* const linear_map_, const Dark_Compare compare_, const size_t key_byte_, const size_t value_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != compare_, DARK_ERROR_NULL);
    DARK_ASSERT(key_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(value_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ <= DARK_LINEAR_MAP_SIZE_MAX, DARK_ERROR_OVERFLOW);

    linear_map_->allocator = allocator_;

    dark_vector_construct_capacity(allocator_, &linear_map_->vector, dark_growth_simple, key_byte_ + value_byte_, capacity_);

    linear_map_->compare = compare_;
    linear_map_->key_byte = key_byte_;
    linear_map_->value_byte = value_byte_;
}

void dark_linear_map_construct(Dark_Allocator* const allocator_, Dark_Linear_Map* const linear_map_, const Dark_Compare compare_, const size_t key_byte_, const size_t value_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != compare_, DARK_ERROR_NULL);
    DARK_ASSERT(key_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(value_byte_ > 0, DARK_ERROR_ZERO);

    dark_linear_map_construct_capacity(allocator_, linear_map_, compare_, key_byte_, value_byte_, 0);
}

void dark_linear_map_destruct(Dark_Linear_Map* linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    dark_vector_destruct(&linear_map_->vector);
}

Dark_Linear_Map* dark_linear_map_new_capacity(Dark_Allocator* const allocator_, const Dark_Compare compare_, const size_t key_byte_, const size_t value_byte_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != compare_, DARK_ERROR_NULL);
    DARK_ASSERT(key_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(value_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ <= DARK_LINEAR_MAP_SIZE_MAX, DARK_ERROR_OVERFLOW);

    Dark_Linear_Map* const linear_map = dark_malloc(allocator_, sizeof(*linear_map));
    DARK_ASSERT(NULL != linear_map, DARK_ERROR_NULL);

    dark_linear_map_construct_capacity(allocator_, linear_map, compare_, key_byte_, value_byte_, capacity_);

    return linear_map;
}

Dark_Linear_Map* dark_linear_map_new(Dark_Allocator* const allocator_, const Dark_Compare compare_, const size_t key_byte_, const size_t value_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != compare_, DARK_ERROR_NULL);
    DARK_ASSERT(key_byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(value_byte_ > 0, DARK_ERROR_ZERO);

    return dark_linear_map_new_capacity(allocator_, compare_, key_byte_, value_byte_, 0);
}

void dark_linear_map_delete(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    dark_linear_map_destruct(linear_map_);

    dark_free(linear_map_->allocator, linear_map_, sizeof(*linear_map_));
}

Dark_Array_View dark_linear_map_array_view(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return dark_vector_array_view(&linear_map_->vector);
}

Dark_Buffer_View dark_linear_map_buffer_view(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return dark_vector_buffer_view(&linear_map_->vector);
}

bool dark_linear_map_contain_is(Dark_Linear_Map* const linear_map_, const void* const key_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    for(size_t i = 0; i < dark_linear_map_size(linear_map_); i++)
    {
        if(0 == linear_map_->compare((uint8_t*)dark_vector_at(&linear_map_->vector, i), key_))
        {
            return true;
        }
    }

    return false;
}

void* dark_linear_map_value(Dark_Linear_Map* const linear_map_, const void* const key_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    for(size_t i = 0; i < dark_linear_map_size(linear_map_); i++)
    {
        if(0 == linear_map_->compare((uint8_t*)dark_vector_at(&linear_map_->vector, i), key_))
        {
            return (uint8_t*)dark_vector_at(&linear_map_->vector, i) + linear_map_->key_byte;
        }
    }

    return NULL;
}

void* dark_linear_map_inplace(Dark_Linear_Map* const linear_map_, const void* const key_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != key_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_map_size(linear_map_) < DARK_LINEAR_MAP_SIZE_MAX, DARK_ERROR_OVERFLOW);

    void* contain = dark_linear_map_value(linear_map_, key_);

    if(NULL == contain)
    {
        void* const destination = dark_vector_inplace_back(&linear_map_->vector);
        dark_memcpy(destination, key_, linear_map_->key_byte);

        contain = (uint8_t*)destination + linear_map_->key_byte;
    }

    return contain;
}

void dark_linear_map_insert(Dark_Linear_Map* const linear_map_, const void* const key_, const void* const value_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != key_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != value_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_linear_map_size(linear_map_) < DARK_LINEAR_MAP_SIZE_MAX, DARK_ERROR_OVERFLOW);

    void* const contain = dark_linear_map_inplace(linear_map_, key_);

    dark_memcpy(contain, value_, linear_map_->value_byte);
}

void dark_linear_map_erase(Dark_Linear_Map* const linear_map_, const void* const key_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != key_, DARK_ERROR_NULL);

    DARK_ASSERT(NULL != dark_linear_map_value(linear_map_, key_), DARK_ERROR_CONTAINER_ELEMENT);

    for(size_t i = 0; i < dark_linear_map_size(linear_map_); i++)
    {
        if(0 == linear_map_->compare((char*)dark_vector_at(&linear_map_->vector, i), key_))
        {
            dark_vector_erase(&linear_map_->vector, i);
        }
    }
}

size_t dark_linear_map_capacity(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return dark_vector_capacity(&linear_map_->vector);
}

void dark_linear_map_reserve_exact(Dark_Linear_Map* const linear_map_, const size_t capacity_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(capacity_ <= DARK_LINEAR_MAP_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_exact(&linear_map_->vector, capacity_);
}

void dark_linear_map_shrink_to_fit(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    dark_vector_shrink_to_fit(&linear_map_->vector);
}

size_t dark_linear_map_size(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return dark_vector_size(&linear_map_->vector);
}

void dark_linear_map_clear(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    dark_vector_clear(&linear_map_->vector);
}

void dark_linear_map_iterator(Dark_Linear_Map* const linear_map_, Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    dark_vector_iterator(&linear_map_->vector, iterator_);
}

size_t dark_linear_map_iterator_context_byte(void)
{
    return dark_vector_iterator_context_byte();
}

size_t dark_linear_map_key_byte(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return linear_map_->key_byte;
}

size_t dark_linear_map_value_byte(Dark_Linear_Map* const linear_map_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);

    return linear_map_->value_byte;
}

void dark_linear_map_foreach(Dark_Linear_Map* const linear_map_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != linear_map_, DARK_ERROR_NULL);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    dark_vector_foreach(&linear_map_->vector, context_, foreach_);
}

size_t dark_linear_map_struct_byte(void)
{
    return sizeof(Dark_Linear_Map);
}
