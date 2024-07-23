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
#define DARK_UNIT "array_iterator"

size_t dark_array_iterator_context_size(void)
{
    return sizeof(Dark_Array_Iterator_Context);
}

void dark_array_iterator_construct(Dark_Iterator* const iterator_, void* const context_, const Dark_Array array_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_size > 0, DARK_ERROR_ZERO);

    Dark_Iterator_Struct* const iterator = (Dark_Iterator_Struct*)iterator_;

    iterator->next_is = dark_array_allocator_next_is;
    iterator->next = dark_array_allocator_next;
    iterator->context = context_;

    Dark_Array_Iterator_Context* const context = (Dark_Array_Iterator_Context*)iterator->context;
    context->array = array_;
    context->index = 0;
}

void dark_array_iterator_destruct(Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    Dark_Iterator_Struct* const iterator = (Dark_Iterator_Struct*)iterator_;

    //nothing
}

Dark_Iterator* dark_array_iterator_new(Dark_Allocator* const allocator_, const Dark_Array array_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_size > 0, DARK_ERROR_ZERO);

    Dark_Iterator_Struct* const iterator = dark_malloc(allocator_, sizeof(Dark_Iterator_Struct) + dark_array_iterator_context_size());
    DARK_ASSERT(NULL != iterator, DARK_ERROR_ALLOCATION);

    Dark_Array_Iterator_Context* const context = (Dark_Array_Iterator_Context*)((int8_t*)iterator + sizeof(Dark_Iterator_Struct));

    dark_array_iterator_construct((Dark_Iterator*)iterator, context, array_);

    return (Dark_Iterator*)iterator;
}

void dark_array_iterator_delete(Dark_Allocator* const allocator_, Dark_Iterator* const iterator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_ALLOCATION);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_ALLOCATION);

    Dark_Iterator_Struct* const iterator = (Dark_Iterator_Struct*)iterator_;

    dark_free(allocator_, iterator, sizeof(Dark_Iterator_Struct) + dark_array_iterator_context_size());
}

bool dark_array_allocator_next_is(void* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    Dark_Array_Iterator_Context* const context = context_;

    return context->index < context->array.size;
}

void* dark_array_allocator_next(void* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    Dark_Array_Iterator_Context* const context = context_;

    DARK_ASSERT(dark_array_allocator_next_is(context), DARK_ERROR_ITERATOR);

    context->index++;

    return (int8_t*)context->array.data + (context->index - 1);
}
