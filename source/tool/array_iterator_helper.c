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

#include "array_iterator_helper.h"
#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/array_iterator_context.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "array_iterator_helper"

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
