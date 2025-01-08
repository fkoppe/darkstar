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

#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "growth"

size_t dark_growth_simple(const size_t current_, const size_t requested_)
{
    //current_
    //requested_

    if(requested_ <= current_)
    {
        return 0;
    }

    return requested_ - current_;
}

size_t dark_growth_standard(const size_t current_, const size_t requested_)
{
    //current_
    //requested_

    if(requested_ <= current_)
    {
        return 0;
    }

    return dark_max_zu(requested_, dark_max_zu(1, current_ * 1.5f));
}

size_t dark_growth_exponential(const size_t current_, const size_t requested_)
{
    //current_
    //requested_

    if(requested_ <= current_)
    {
        return 0;
    }

    return dark_max_zu(requested_, dark_max_zu(1, current_ * 2.0f));
}
