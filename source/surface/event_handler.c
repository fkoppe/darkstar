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

#if !defined(___DARK___WINDOW_H)
#define ___DARK___WINDOW_H

#include "surface_module.h"

#include <dark/core/std.h>
#include <dark/surface/event_handler.h>
#include <dark/surface/event_handler_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "event_handler"

static bool DARK_GLFW_INITIALISED_IS = false;

void dark_event_handler_construct(Dark_Allocator* const allocator_, Dark_Event_Handler* const event_handler_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);
    //logger

    event_handler_->allocator = allocator_;

    dark_linear_queue_construct(allocator_, &event_handler_->queue, dark_growth_exponential, sizeof(Dark_Event));

    event_handler_->logger = logger_;
}

void dark_event_handler_destruct(Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    dark_linear_queue_destruct(&event_handler_->queue);
}

Dark_Event_Handler* dark_event_handler_new(Dark_Allocator* const allocator_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //logger

    Dark_Event_Handler* const event_handler = dark_malloc(allocator_, sizeof(*event_handler));
    DARK_ASSERT(NULL != event_handler, DARK_ERROR_ALLOCATION);

    dark_event_handler_construct(allocator_, event_handler, logger_);

    return event_handler;
}

void dark_event_handler_delete(Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    dark_event_handler_destruct(event_handler_);

    dark_free(event_handler_->allocator, event_handler_, sizeof(*event_handler_));
}

void dark_event_handler_insert(Dark_Event_Handler* const event_handler_, const Dark_Event event_)
{
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);
    //event

    dark_linear_queue_insert(&event_handler_->queue, &event_);
}

Dark_Event* dark_event_handler_next(Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    if(dark_linear_queue_done_is(&event_handler_->queue))
    {
        return NULL;
    }
    else
    {
        return dark_linear_queue_next(&event_handler_->queue);
    }
}

void dark_event_handler_clear(Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    dark_linear_queue_clear(&event_handler_->queue);
}

#endif // !defined(___DARK___WINDOW_H)
