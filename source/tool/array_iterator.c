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
#include "array_iterator_helper.h"

#include <dark/core/core.h>
#include <dark/tool/array_iterator_context.h>
#include <dark/tool/iterator_struct.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "array_iterator"

void dark_array_iterator_construct(Dark_Allocator* const allocator_, Dark_Iterator* const iterator_, Dark_Array_Iterator_Context* const context_,  const Dark_Array array_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != context_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    iterator_->allocator = allocator_;
    iterator_->done = dark_array_iterator_done;
    iterator_->next = dark_array_iterator_next;
    iterator_->peek = dark_array_iterator_peek;
    iterator_->reset = dark_array_iterator_reset;
    iterator_->skip = dark_array_iterator_skip;
    iterator_->context = context_;

    context_->array = array_;
    context_->index = 0;
}

void dark_array_iterator_destruct(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    //nothing
}

Dark_Iterator* dark_array_iterator_new(Dark_Allocator* const allocator_, const Dark_Array array_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    Dark_Iterator* const iterator = dark_malloc(allocator_, sizeof(*iterator) + dark_array_iterator_context_byte());
    DARK_ASSERT(NULL != iterator, DARK_ERROR_ALLOCATION);

    Dark_Array_Iterator_Context* const context = (Dark_Array_Iterator_Context*)((uint8_t*)iterator + sizeof(Dark_Iterator));

    dark_array_iterator_construct(allocator_, iterator, context, array_);

    return iterator;
}

void dark_array_iterator_delete(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_ALLOCATION);

    Dark_Array_Iterator_Context* const context = (Dark_Array_Iterator_Context*)iterator_->context;

    dark_free(iterator_->allocator, iterator_, sizeof(*iterator_) + dark_array_iterator_context_byte());
}

size_t dark_array_iterator_context_byte(void)
{
    return sizeof(Dark_Array_Iterator_Context);
}
