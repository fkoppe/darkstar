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

#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "buffer"

Dark_Buffer_View dark_buffer_to_view(const Dark_Buffer buffer_)
{
    DARK_ASSERT(NULL != buffer_.data, DARK_ERROR_NULL);
    DARK_ASSERT(buffer_.byte > 0, DARK_ERROR_ZERO);

    Dark_Buffer_View buffer_view;
    buffer_view.data = buffer_.data;
    buffer_view.byte = buffer_.byte;

    return buffer_view;
}

void dark_buffer_foreach(const Dark_Buffer buffer_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != buffer_.data, DARK_ERROR_NULL);
    DARK_ASSERT(buffer_.byte > 0, DARK_ERROR_ZERO);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    for(size_t i = 0; i < buffer_.byte; i++)
    {
        foreach_((uint8_t*)buffer_.data + i, context_);
    }
}
