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

#include "array_view_helper.h"
#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/iterator_struct.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "array_view"

Dark_Buffer_View dark_array_view_to_buffer_view(const Dark_Array_View array_view_)
{
    DARK_ASSERT(array_view_.data == NULL || array_view_.size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(array_view_.element_byte > 0, DARK_ERROR_ZERO);

    const Dark_Buffer_View buffer_view = { array_view_.element_byte * array_view_.size, array_view_.data };

    return buffer_view;
}

void dark_array_view_iterator(const Dark_Array_View array_view_, Dark_Iterator* const iterator_)
{
    DARK_ASSERT(array_view_.data == NULL || array_view_.size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(NULL != iterator_, DARK_ERROR_NULL);

    DARK_ASSERT(iterator_->context == NULL || iterator_->byte > 0, DARK_ERROR_INTERNAL);

    if(iterator_->byte < sizeof(Dark_Array_View_Iterator_Context))
    {
        if(iterator_->byte > 0)
        {
            iterator_->context = dark_realloc(iterator_->allocator, iterator_->context, iterator_->byte, sizeof(Dark_Array_View_Iterator_Context));
            DARK_ASSERT(NULL != iterator_->context, DARK_ERROR_ALLOCATION);
        }
        else
        {
            iterator_->context = dark_malloc(iterator_->allocator, sizeof(Dark_Array_View_Iterator_Context));
            DARK_ASSERT(NULL != iterator_->context, DARK_ERROR_ALLOCATION);
        }

        iterator_->byte = sizeof(Dark_Array_View_Iterator_Context);
    }

    Dark_Array_View_Iterator_Context* const context = iterator_->context;
    context->array_view = array_view_;
    context->index = 0;

    iterator_->done_is = (void*)dark_array_view_iterator_done_is;
    iterator_->peek = (void*)dark_array_view_iterator_peek;
    iterator_->next = (void*)dark_array_view_iterator_next;
    iterator_->reset = (void*)dark_array_view_iterator_reset;
    iterator_->skip = (void*)dark_array_view_iterator_skip;
}

size_t dark_array_view_iterator_context_byte(void)
{
    return sizeof(Dark_Array_View_Iterator_Context);
}

void dark_array_view_foreach(const Dark_Array_View array_view_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(array_view_.data == NULL || array_view_.size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(array_view_.element_byte > 0, DARK_ERROR_ZERO);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    for(size_t i = 0; i < array_view_.size; i++)
    {
        foreach_((uint8_t*)array_view_.data + (array_view_.element_byte * i), context_);
    }
}

int8_t dark_array_view_compare(const Dark_Array_View* const a_, const Dark_Array_View* const b_)
{
    DARK_ASSERT(a_->data == NULL || a_->size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(a_->element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(b_->data == NULL || b_->size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(b_->element_byte > 0, DARK_ERROR_ZERO);

    if(dark_compare_zu(&a_->element_byte, &b_->element_byte))
    {
        return dark_compare_zu(&a_->element_byte, &b_->element_byte);
    }

    if(dark_compare_zu(&a_->size, &b_->size))
    {
        return dark_compare_zu(&a_->size, &b_->size);
    }

    if(dark_memcmp(a_->data, b_->data, a_->element_byte * a_->size))
    {
        return dark_memcmp(a_->data, b_->data, a_->element_byte * a_->size);
    }

    return 0;
}
