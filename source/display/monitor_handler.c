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

#include "display_module.h"

#include <dark/core/core.h>
#include <dark/display/display.h>
#include <dark/display/monitor_handler_struct.h>
#include <dark/log/logger.h>
#include <dark/memory/memory.h>

#include <GLFW/glfw3.h>

#undef DARK_UNIT
#define DARK_UNIT "monitor"

void dark_monitor_handler_construct(Dark_Monitor_Handler* const monitor_handler_, const Dark_Entropy entropy_, Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    //entropy_
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);


}

void dark_monitor_handler_destruct(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
}

void dark_monitor_handler_new(Dark_Monitor_Handler* const monitor_handler_, const Dark_Entropy entropy_, Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    //entropy_
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);


}

void dark_monitor_handler_delete(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
}

void dark_monitor_handler_update(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);


}

Dark_Uuid4 dark_monitor_handler_primary_id(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    //no update
}

void dark_monitor_handler_id_raw(Dark_Monitor_Handler* const monitor_handler_, const Dark_Uuid4 monitor_uuid_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != dark_uuid4_compare(&DARK_UUID4_ZERO, &monitor_uuid_), DARK_ERROR_VALUE);

    //no update
}
