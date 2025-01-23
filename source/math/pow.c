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

#include "math_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "pow"

uintmax_t dark_upow_u(const uintmax_t base_, const uintmax_t exponent_)
{
    //base_
    //exponent_

    if(0 == exponent_)
    {
        DARK_ASSERT(0 != base_, DARK_ERROR_MATH);

        return 1;
    }

    if(0 == base_)
    {
        return 0;
    }

    uintmax_t exponent = exponent_;
    uintmax_t base = base_;
    uintmax_t val = 1;

    while (exponent > 0)
    {
        if(exponent % 2 == 1)
        {
            val = dark_umult_umax(base, val);
        }

        base = dark_umult_umax(base, base);
        exponent /= 2;
    }

    return val;
}

intmax_t dark_upow_i(const intmax_t base_, const uintmax_t exponent_)
{
    //base_
    //exponent_

    if(0 == exponent_)
    {
        DARK_ASSERT(0 != base_, DARK_ERROR_MATH);

        return 1;
    }

    if(0 == base_)
    {
        return 0;
    }

    if(base_ > 0)
    {
        return dark_upow_u(base_, exponent_);
    }
    else
    {
        if(-exponent_ % 2 == 0)
        {
            return dark_ucast_imax(dark_upow_u(-base_, exponent_));
        }
        else
        {
            return -dark_ucast_imax(dark_upow_u(-base_, exponent_));
        }
    }
}
