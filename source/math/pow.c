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

#include "math_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "pow"

uintmax_t dark_upow_u(uintmax_t base_, uintmax_t exponent_)
{
    //base_
    //exponent_

    if(0 == exponent_)
    {
        DARK_ASSERT(0 != base_, DARK_ERROR_MATH);

        return 1;
    }

    if (0 == base_)
    {
        return 0;
    }

    uintmax_t val = base_;
    for(size_t i = 1; i < exponent_; i++)
    {
        DARK_ASSERT(val <= (UINTMAX_MAX - (val * base_)), DARK_ERROR_OVERFLOW);
        val *= base_;
    }

    return val;
}

uintmax_t dark_upow_i(intmax_t base_, uintmax_t exponent_)
{
    //base_
    //exponent_

    if(0 == exponent_)
    {
        DARK_ASSERT(0 != base_, DARK_ERROR_MATH);

        return 1;
    }

    if (0 == base_)
    {
        return 0;
    }

    intmax_t val = base_;
    for(size_t i = 1; i < exponent_; i++)
    {
        if (val > 0)
        {
            DARK_ASSERT(val <= (INTMAX_MAX - (val * dark_abs_imax(base_))), DARK_ERROR_OVERFLOW);
        }
        else
        {
            DARK_ASSERT(val >= (INTMAX_MAX + (val * dark_abs_imax(base_))), DARK_ERROR_UNDERFLOW);
        }

        val *= base_;
    }

    return val;
}
