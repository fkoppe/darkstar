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
#define DARK_UNIT "box"

size_t dark_box_struct_size(void)
{
    return sizeof(Dark_Box_Struct);
}

void dark_box_create_size(Dark_Box* const box_, const size_t element_size_, const size_t size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    //size_
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    box->allocator = allocator_;
    box->element_size = element_size_;
    box->size = size_;
    box->data = NULL;

    if (box->size > 0)
    {
        box->data = dark_balloc(box->allocator, box->element_size, box->size);
        DARK_ASSERT(NULL != box->data, DARK_ERROR_ALLOCATION);
    }
}

void dark_box_create(Dark_Box* box_, size_t element_size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    dark_box_create_size((Dark_Box*)box, element_size_, 0, allocator_);
}

void dark_box_destroy(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    if (box->size > 0)
    {
        dark_bfree(box->allocator, box->data, box->element_size, box->size);
    }
}

Dark_Box* dark_box_new_size(const size_t element_size_, const size_t size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = dark_malloc(allocator_, sizeof(*box));
    DARK_ASSERT(NULL != box, DARK_ERROR_ALLOCATION);

    dark_box_create_size((Dark_Box*)box, element_size_, size_, allocator_);

    return (Dark_Box*)box;
}

Dark_Box* dark_box_new(const size_t element_size_, Dark_Allocator* const allocator_)
{
    DARK_ASSERT(0 != element_size_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    return dark_box_new_size(element_size_, 0, allocator_);
}

void dark_box_delete(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    dark_box_destroy((Dark_Box*)box);

    dark_free(box->allocator, box, sizeof(Dark_Box_Struct));
}

void* dark_box_at(Dark_Box* const box_, const size_t index_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size > 0, DARK_ERROR_CONTAINER_EMPTY);
    DARK_ASSERT(index_ < box->size, DARK_ERROR_CONTAINER_INDEX);

    return box->data + (box->element_size * index_);
}

void* dark_box_front(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_at((Dark_Box*)box, 0);
}

void* dark_box_back(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_at((Dark_Box*)box, box->size - 1);
}

void* dark_box_data(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size > 0, DARK_ERROR_CONTAINER_EMPTY);

    return dark_box_at((Dark_Box*)box, 0);
}

void* dark_box_emplace(Dark_Box* const box_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(index_ <= box->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    if (box->size > 0)
    {
        box->data = dark_brealloc(box->allocator, box->data, box->element_size, box->size, box->size + count_);
    }
    else
    {
        box->data = dark_balloc(box->allocator, box->element_size, count_);
    }

    DARK_ASSERT(NULL != box->data, DARK_ERROR_ALLOCATION);

    box->size += count_;

    if (index_ < box->size - count_)
    {
        memmove(box->data + (box->element_size * (index_ + count_)), box->data + (box->element_size * index_), box->element_size * (box->size - index_ - count_));
    }

    return box->data + (box->element_size * index_);
}

void* dark_box_emplace_front(Dark_Box* const box_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_box_emplace((Dark_Box*)box, 0, count_);
}

void* dark_box_emplace_back(Dark_Box* const box_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_box_emplace((Dark_Box*)box, box->size, count_);
}

void* dark_box_inplace(Dark_Box* const box_, const size_t index_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(index_ <= box->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_box_emplace((Dark_Box*)box, index_, 1);
}

void* dark_box_inplace_front(Dark_Box* box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_box_emplace_front((Dark_Box*)box, 1);
}

void* dark_box_inplace_back(Dark_Box* box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_box_emplace_back((Dark_Box*)box, 1);
}

void dark_box_push(Dark_Box* const box_, const size_t index_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(index_ <= box->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    void* const destination = dark_box_emplace((Dark_Box*)box, index_, count_);

    memcpy(destination, source_, box->element_size * count_);
}

void dark_box_push_front(Dark_Box* const box_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_box_push((Dark_Box*)box, 0, count_, source_);
}

void dark_box_push_back(Dark_Box* const box_, const size_t count_, const void* const source_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_box_push((Dark_Box*)box, box->size, count_, source_);
}

void dark_box_insert(Dark_Box* const box_, const size_t index_, const void* const element_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(index_ <= box->size, DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_box_push((Dark_Box*)box, index_, 1, element_);
}

void dark_box_insert_front(Dark_Box* const box_, const void* const element_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_box_push_front((Dark_Box*)box, 1, element_);
}

void dark_box_insert_back(Dark_Box* const box_, const void* const element_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_box_push_back((Dark_Box*)box, 1, element_);
}

void dark_box_pop(Dark_Box* const box_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= box->size, DARK_ERROR_VALUE);

    box->size -= count_;

    if (0 == box->size)
    {
        return;
    }

    if (index_ + count_ - 1 >= box->size + count_)
    {
        return;
    }

    memmove(box->data + (box->element_size * index_), box->data + (box->element_size * (index_ + count_)), box->element_size * (box->size - index_));

    box->data = dark_brealloc(box->allocator, box->data, box->element_size, box->size + count_, box->size);
}

void dark_box_pop_front(Dark_Box* const box_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= count_, DARK_ERROR_UNDERFLOW);

    dark_box_pop((Dark_Box*)box, 0, count_);
}

void dark_box_pop_back(Dark_Box* const box_, const size_t count_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= count_, DARK_ERROR_UNDERFLOW);

    dark_box_pop((Dark_Box*)box, box->size - count_, count_);
}

void dark_box_erase(Dark_Box* const box_, const size_t index_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //index_!

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= 1, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + 1 <= box->size, DARK_ERROR_VALUE);

    dark_box_pop((Dark_Box*)box, index_, 1);
}

void dark_box_erase_front(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_box_pop_front((Dark_Box*)box, 1);
}

void dark_box_erase_back(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    DARK_ASSERT(box->size >= 1, DARK_ERROR_UNDERFLOW);

    dark_box_pop_back((Dark_Box*)box, 1);
}

size_t dark_box_size(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    return box->size;
}

void dark_box_resize(Dark_Box* const box_, const size_t size_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);
    //size_

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    if (box->size == size_)
    {
        return;
    }

    if (0 == size_)
    {
        dark_bfree(box->allocator, box->data, box->element_size, box->size);
    }
    else
    {
        if (box->size > 0)
        {
            box->data = dark_brealloc(box->allocator, box->data, box->element_size, box->size, size_);
        }
        else
        {
            box->data = dark_balloc(box->allocator, box->element_size, size_);
        }

        DARK_ASSERT(NULL != box->data, DARK_ERROR_ALLOCATION);

    }

    box->size = size_;
}

void dark_box_clear(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    box->size = 0;
}

size_t dark_box_element_size(Dark_Box* const box_)
{
    DARK_ASSERT(NULL != box_, DARK_ERROR_NULL);

    Dark_Box_Struct* const box = (Dark_Box_Struct*)box_;

    return box->element_size;
}
