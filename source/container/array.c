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

#include "container_module.h"

#include <dark/container/container.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "container"

Dark_Array_View dark_array_view(const Dark_Array array_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    Dark_Array_View view;
    view.data = array_.data;
    view.size = array_.size;
    view.element_byte = array_.element_byte;

    return view;
}

void dark_array_foreach(const Dark_Array array_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    for(size_t i = 0; i < array_.size; i++)
    {
        foreach_((uint8_t*)array_.data + (array_.element_byte * i), context_);
    }
}
