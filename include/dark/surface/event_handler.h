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

#if !defined(___DARK___EVENT_HANDLER_H)
#define ___DARK___EVENT_HANDLER_H

#include <dark/core/error.h>
#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/memory/allocator.h>
#include <dark/surface/event_data.h>

typedef struct Dark_Event_Handler Dark_Event_Handler;

void dark_event_handler_construct(Dark_Allocator* allocator, Dark_Event_Handler* event_handler, Dark_Logger* logger);
void dark_event_handler_destruct(Dark_Event_Handler* event_handler);

Dark_Event_Handler* dark_event_handler_new(Dark_Allocator* allocator, Dark_Logger* logger);
void dark_event_handler_delete(Dark_Event_Handler* event_handler);

void dark_event_handler_insert(Dark_Event_Handler* event_handler, Dark_Event event);

Dark_Event* dark_event_handler_next(Dark_Event_Handler* event_handler);

void dark_event_handler_clear(Dark_Event_Handler* event_handler);

#endif // !defined(___DARK___EVENT_HANDLER_H)