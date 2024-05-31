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

#undef DARK_UNIT
#define DARK_UNIT "vector"

#include <string.h>

size_t dark_vector_struct_size(void)
{
    return sizeof(Dark_Vector_Struct);
}

void dark_vector_construct_size(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    vector->allocator = allocator_;
    vector->size = size_;
    vector->growth = growth_;
    dark_box_construct_size((Dark_Box*)&vector->box, element_size_, capacity_, allocator_);
}

void dark_vector_construct_capacity(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_construct_size((Dark_Vector*)vector, growth_, element_size_, capacity_, 0, allocator_);
}

void dark_vector_construct(Dark_Vector* const vector_, const Dark_Growth growth_, const size_t element_size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_construct_capacity((Dark_Vector*)vector, growth_, element_size_, 0, allocator_);
}

void dark_vector_destruct(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_box_destruct((Dark_Box*)&vector->box);
}

Dark_Vector* dark_vector_new_size(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, const size_t size_, Dark_Allocator* const allocator_, Dark_Allocator* const struct_allocator_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != struct_allocator_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = dark_malloc(struct_allocator_, sizeof(*vector));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_vector_construct_size((Dark_Vector*)vector, growth_, element_size_, capacity_, size_, allocator_);

    return (Dark_Vector*)vector;
}

Dark_Vector* dark_vector_new_capacity(const Dark_Growth growth_, const size_t element_size_, const size_t capacity_, Dark_Allocator* const allocator_, Dark_Allocator* const struct_allocator_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //capacity_
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != struct_allocator_, DARK_ERROR_NULL);

    return dark_vector_new_size(growth_, element_size_, capacity_, 0, allocator_, struct_allocator_);
}

Dark_Vector* dark_vector_new(const Dark_Growth growth_, const size_t element_size_, Dark_Allocator* const allocator_, Dark_Allocator* const  struct_allocator_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != struct_allocator_, DARK_ERROR_NULL);

    return dark_vector_new_capacity(growth_, element_size_, 0, allocator_, struct_allocator_);
}

void dark_vector_delete(Dark_Vector* const vector_, Dark_Allocator* const struct_allocator_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != struct_allocator_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_destruct((Dark_Vector*)vector);

    dark_free(struct_allocator_, vector, sizeof(*vector));
}

void* dark_vector_at(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < dark_vector_size((Dark_Vector*)vector), DARK_ERROR_CONTAINER_INDEX);

    return dark_box_at((Dark_Box*)&vector->box, index_);
}

void* dark_vector_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_front((Dark_Box*)&vector->box);
}

void* dark_vector_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_at((Dark_Box*)&vector->box, vector->size - 1);
}

void* dark_vector_data(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_data((Dark_Box*)&vector->box);
}

void* dark_vector_emplace(Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= dark_vector_size((Dark_Vector*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional((Dark_Vector*)vector, count_);

    vector->size += count_;

    return dark_vector_at((Dark_Vector*)vector, index_);
}

void* dark_vector_emplace_front(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace((Dark_Vector*)vector, 0, count_);
}

void* dark_vector_emplace_back(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace((Dark_Vector*)vector, dark_vector_size((Dark_Vector*)vector), count_);
}

void* dark_vector_inplace(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= dark_vector_size((Dark_Vector*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace((Dark_Vector*)vector, index_, 1);
}

void* dark_vector_inplace_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_front((Dark_Vector*)vector, 1);
}

void* dark_vector_inplace_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace_back((Dark_Vector*)vector, 1);
}

void dark_vector_push(Dark_Vector* const vector_, const size_t index_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= dark_vector_size((Dark_Vector*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional((Dark_Vector*)vector, count_);

    dark_box_push((Dark_Box*)&vector->box, index_, count_, source_);

    vector->size += count_;
}

void dark_vector_push_front(Dark_Vector* const vector_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push((Dark_Vector*)vector, dark_vector_size((Dark_Vector*)vector), count_, source_);
}

void dark_vector_push_back(Dark_Vector* const vector_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push((Dark_Vector*)vector, dark_vector_size((Dark_Vector*)vector), count_, source_);
}

void dark_vector_insert(Dark_Vector* const vector_, const size_t index_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(index_ <= dark_vector_size((Dark_Vector*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push((Dark_Vector*)vector, index_, 1, element_);
}

void dark_vector_insert_front(Dark_Vector* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_insert((Dark_Vector*)vector, 0, element_);
}

void dark_vector_insert_back(Dark_Vector* const vector_, const void* const element_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert((Dark_Vector*)vector, dark_vector_size((Dark_Vector*)vector), element_);
}

void dark_vector_pop(Dark_Vector* const vector_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= dark_vector_size((Dark_Vector*)vector), DARK_ERROR_VALUE);

    vector->size -= count_;

    if (0 == vector->size)
    {
        return;
    }

    if (index_ + count_ - 1 >= vector->size + count_)
    {
        return;
    }

    const size_t element_size = dark_box_element_size((Dark_Box*)&vector->box);
    char* const data = dark_box_data((Dark_Box*)&vector->box);

    memmove(data + (element_size * index_), data + (element_size * (index_ + count_)), element_size * (dark_box_size((Dark_Box*)&vector->box) - index_));
}

void dark_vector_pop_front(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= count_, DARK_ERROR_UNDERFLOW);

    dark_box_pop((Dark_Box*)&vector->box, 0, count_);
}

void dark_vector_pop_back(Dark_Vector* const vector_, const size_t count_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= count_, DARK_ERROR_UNDERFLOW);

    dark_box_pop((Dark_Box*)&vector->box, dark_vector_size((Dark_Vector*)vector) - count_, count_);
}

void dark_vector_erase(Dark_Vector* const vector_, const size_t index_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_pop((Dark_Vector*)vector, index_, 1);
}

void dark_vector_erase_front(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_front((Dark_Vector*)vector, 1);
}

void dark_vector_erase_back(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    DARK_ASSERT(dark_vector_size((Dark_Vector*)vector) >= 1, DARK_ERROR_UNDERFLOW);

    dark_vector_pop_back((Dark_Vector*)vector, 1);
}

size_t dark_vector_capacity(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return dark_box_size((Dark_Box*)&vector->box);
}

void dark_vector_reserve(Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if (capacity_ <= dark_vector_capacity((Dark_Vector*)vector))
    {
        return;
    }

    dark_vector_reserve_exact((Dark_Vector*)vector, dark_vector_capacity((Dark_Vector*)vector) + vector->growth(dark_vector_capacity((Dark_Vector*)vector), capacity_));
}

void dark_vector_reserve_additional(Dark_Vector* const vector_, const size_t additional_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //additional_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_vector_reserve((Dark_Vector*)vector_, dark_vector_size((Dark_Vector*)vector_) + additional_);
}

void dark_vector_reserve_exact(Dark_Vector* const vector_, const size_t capacity_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //capacity_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_box_resize((Dark_Box*)&vector->box, capacity_);

    vector->size = dark_min_zu(vector->size, dark_vector_capacity((Dark_Vector*)vector));
}

void dark_vector_shrink_to_fit(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    //dark_box_shrink_to_fit((Dark_Box*)&vector->box);
}

size_t dark_vector_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return vector->size;
}

void dark_vector_resize(Dark_Vector* const vector_, const size_t size_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);
    //size_

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    if(size_ > dark_box_size((Dark_Box*)&vector->box))
    {
        dark_vector_reserve((Dark_Vector*)vector, size_);
    }

    vector->size = size_;
}

void dark_vector_clear(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    dark_box_clear((Dark_Box*)&vector->box);
}

size_t dark_vector_element_size(Dark_Vector* const vector_)
{
    DARK_ASSERT(NULL != vector_, DARK_ERROR_NULL);

    Dark_Vector_Struct* const vector = (Dark_Vector_Struct*)vector_;

    return dark_box_element_size((Dark_Box*)&vector->box);
}
