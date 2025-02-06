/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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
#include <dark/math/math.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "array_view_helper"

bool dark_array_view_iterator_next_is(Dark_Array_View_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    return context_->index >= context_->array_view.size;
}

void* dark_array_view_iterator_next(Dark_Array_View_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_array_view_iterator_next_is(context_), DARK_ERROR_ITERATOR);

    context_->index++;

    return (int8_t*)context_->array_view.data + context_->array_view.element_byte * (context_->index - 1);
}

void* dark_array_view_iterator_peek(Dark_Array_View_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_array_view_iterator_next_is(context_), DARK_ERROR_ITERATOR);

    return (int8_t*)context_->array_view.data + context_->array_view.element_byte * context_->index;
}

void dark_array_view_iterator_reset(Dark_Array_View_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    context_->index = 0;
}

size_t dark_array_view_iterator_skip(Dark_Array_View_Iterator_Context* const context_, const size_t count_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    const size_t skipped = dark_min_zu(count_, context_->array_view.size - context_->index);

    context_->index += skipped;

    return skipped;
}
