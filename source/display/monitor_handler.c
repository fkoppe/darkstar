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

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#undef DARK_UNIT
#define DARK_UNIT "monitor_handler"

void dark_monitor_handler_construct(Dark_Monitor_Handler* const monitor_handler_, Dark_Entropy* const entropy_, Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != entropy_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_monitor_handler_destruct(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_monitor_handler_new(Dark_Monitor_Handler* const monitor_handler_, Dark_Entropy* const entropy_, Dark_Event_Handler* const event_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != entropy_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_monitor_handler_delete(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_monitor_handler_update(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    int count = 0;
    GLFWmonitor** const monitor =  glfwGetMonitors(&count);

    const Dark_Array_View view = dark_linear_map_array_view(&monitor_handler_->map);

    for(size_t i = 0; i < count; i++)
    {
        bool found = false;
        for(size_t j = 0; j < view.size; j++)
        {
            if(0 == dark_memcmp(view.data + j * view.element_byte + sizeof(Dark_Uuid4), monitor[i], sizeof(void*)))
            {
                found = true;
            }
        }

        if(!found)
        {
            const Dark_Uuid4 uuid = dark_uuid4_generate(dark_entropy_get_64(monitor_handler_->entropy));
            dark_linear_map_insert(&monitor_handler_->map, &uuid, &monitor[i]);
        }
    }
}

size_t dark_monitor_handler_count(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    return dark_linear_map_size(&monitor_handler_->map);
}

Dark_Uuid4 dark_monitor_handler_primary_id(Dark_Monitor_Handler* const monitor_handler_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);

    //no update

    DARK_UNIMPLEMENTED;
}

void dark_monitor_handler_id_raw(Dark_Monitor_Handler* const monitor_handler_, const Dark_Uuid4 monitor_uuid_)
{
    DARK_ASSERT(NULL != monitor_handler_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != dark_uuid4_compare(&DARK_UUID4_ZERO, &monitor_uuid_), DARK_ERROR_VALUE);

    //no update

    DARK_UNIMPLEMENTED;
}
