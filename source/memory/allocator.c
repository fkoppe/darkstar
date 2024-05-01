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

#include "memory_module.h"

#include <dark/memory/memory.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "allocator"

void* dark_malloc(Dark_Allocator* const allocator_, const size_t byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->allocate(allocator->context, NULL, 0, byte_);
}

void* dark_balloc(Dark_Allocator* const allocator_, const size_t size_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->allocate(allocator->context, NULL, 0, count_ * size_);
}

void* dark_realloc(Dark_Allocator* const allocator_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != address_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_old_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(byte_new_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->allocate(allocator->context, address_, byte_old_, byte_new_);
}

void* dark_brealloc(Dark_Allocator* const allocator_, void* const address_, const size_t size_, const size_t count_old_, const size_t count_new_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != address_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_old_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_new_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->allocate(allocator->context, address_, count_old_ * size_, count_new_ * size_);
}

void dark_free(Dark_Allocator* const  allocator_, void* const address_, const size_t byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != address_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    DARK_ASSERT(NULL == allocator->allocate(allocator->context, address_, byte_, 0), DARK_ERROR_ALLOCATOR_INTERNAL);
}

void dark_bfree(Dark_Allocator* const allocator_, void* const address_, const size_t size_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    DARK_ASSERT(NULL == allocator->allocate(allocator->context, address_, size_ * count_, 0), DARK_ERROR_ALLOCATOR_INTERNAL);
}

void* dark_calloc(Dark_Allocator* const allocator_, const size_t byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->callocate(allocator->context, NULL, 0, byte_);
}

void* dark_bcalloc(Dark_Allocator* const allocator_, const size_t size_, const size_t count_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->callocate(allocator->context, NULL, 0, count_ * size_);
}

void* dark_recalloc(Dark_Allocator* const allocator_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != address_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_old_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(byte_new_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->callocate(allocator->context, address_, byte_old_, byte_new_);
}

void* dark_brecalloc(Dark_Allocator* const allocator_, void* const address_, const size_t size_, const size_t count_old_, const size_t count_new_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != address_, DARK_ERROR_NULL);
    DARK_ASSERT(size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_old_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_new_ > 0, DARK_ERROR_ZERO);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    return allocator->callocate(allocator->context, address_, count_old_ * size_, count_new_ * size_);
}
