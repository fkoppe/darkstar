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

#include "container_module.h"
#include "linear_queue_helper.h"

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "linear_queue_helper"

bool dark_linear_queue_iterator_next_is(Dark_Linear_Queue_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    return context_->index >= dark_linear_queue_size(context_->queue);
}

void* dark_linear_queue_iterator_next(Dark_Linear_Queue_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_linear_queue_iterator_next_is(context_), DARK_ERROR_ITERATOR);

    context_->index++;

    return dark_linear_queue_at(context_->queue, context_->index - 1);
}

void* dark_linear_queue_iterator_peek(Dark_Linear_Queue_Iterator_Context* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    DARK_ASSERT(!dark_linear_queue_iterator_next_is(context_), DARK_ERROR_ITERATOR);

     return dark_linear_queue_at(context_->queue, context_->index);
}

void dark_linear_queue_iterator_reset(Dark_Linear_Queue_Iterator_Context*  const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    context_->index = 0;
}

size_t dark_linear_queue_iterator_skip(Dark_Linear_Queue_Iterator_Context*  const context_, const size_t count_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    const size_t skipped = dark_min_zu(count_, dark_sat_add_zu(dark_linear_queue_size(context_->queue), -context_->index));

    context_->index += skipped;

    return skipped;
}
