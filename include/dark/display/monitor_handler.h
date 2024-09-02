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

#if !defined(___DARK___MONITOR_H)
#define ___DARK___MONITOR_H

#include <dark/core/std.h>
#include <dark/event/event_handler.h>
#include <dark/memory/allocator.h>
#include <dark/random/entropy.h>
#include <dark/random/uuid4.h>
#include <dark/tool/array.h>

typedef struct Dark_Monitor_Handler Dark_Monitor_Handler;

void dark_monitor_handler_construct(Dark_Allocator* allocator, Dark_Monitor_Handler* monitor_handler, Dark_Entropy* entropy, Dark_Event_Handler* event_handler);
void dark_monitor_handler_destruct(Dark_Monitor_Handler* monitor_handler);

void dark_monitor_handler_new(Dark_Allocator* allocator, Dark_Monitor_Handler* monitor_handler, Dark_Entropy* entropy, Dark_Event_Handler* event_handler);
void dark_monitor_handler_delete(Dark_Monitor_Handler* monitor_handler);

void dark_monitor_handler_update(Dark_Monitor_Handler* monitor_handler);

size_t dark_monitor_handler_count(Dark_Monitor_Handler* monitor_handler);

Dark_Uuid4 dark_monitor_handler_primary_id(Dark_Monitor_Handler* monitor_handler);

void dark_monitor_handler_id_raw(Dark_Monitor_Handler* monitor_handler, Dark_Uuid4 monitor_uuid);

#endif // !defined(___DARK___MONITOR_H)
