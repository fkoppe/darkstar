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

#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/iterator_struct.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "iterator"

void dark_iterator_construct_context(Dark_Allocator* const allocator_, Dark_Iterator* const iterator_, const size_t context_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);
    //context_byte_

    iterator_->allocator = allocator_;
    iterator_->byte = context_byte_;

    if(context_byte_ > 0)
    {
        iterator_->context = dark_malloc(allocator_, context_byte_);
    }
    else
    {
        iterator_->context = NULL;
    }
}

void dark_iterator_construct(Dark_Allocator* const allocator_, Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    dark_iterator_construct_context(allocator_, iterator_, 0);
}

void dark_iterator_destruct(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    if(iterator_->byte > 0)
    {
        DARK_ASSERT(NULL != iterator_->context, DARK_ERROR_UNKNOWN);

        dark_free(iterator_->allocator, iterator_->context, iterator_->byte);
    }
}

Dark_Iterator* dark_iterator_new_context(Dark_Allocator* const allocator_, const size_t context_byte_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //context_byte_

    Dark_Iterator* const iterator = dark_malloc(allocator_, sizeof(*iterator));
    DARK_ASSERT(NULL != iterator, DARK_ERROR_ALLOCATION);

    dark_iterator_construct_context(allocator_, iterator, context_byte_);

    return iterator;
}

Dark_Iterator* dark_iterator_new(Dark_Allocator* const allocator_)
{
    return dark_iterator_new_context(allocator_, 0);
}

void dark_iterator_delete(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    dark_iterator_destruct(iterator_);

    dark_free(iterator_->allocator, iterator_, sizeof(*iterator_));
}

bool dark_iterator_done_is(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    return iterator_->done_is(iterator_->context);
}

void* dark_iterator_next(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    return iterator_->next(iterator_->context);
}

void* dark_iterator_peek(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    return iterator_->peek(iterator_->context);
}

void dark_iterator_reset(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    iterator_->reset(iterator_->context);
}

size_t dark_iterator_skip(Dark_Iterator* const iterator_, const size_t count_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    return iterator_->skip(iterator_->context, count_);
}
