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

#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "com"

uintmax_t dark_gcd_u(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ == b_)
    {
        return a_;
    }

    uintmax_t a = dark_max_umax(a_, b_);
    uintmax_t b = dark_min_umax(a_, b_);

    while(0 != b)
    {
        a %= b;

        if(0 == a)
        {
            return b;
        }

        b %= a;
    }

    return a;
}

uintmax_t dark_gcd_i(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    return dark_gcd_u(dark_abs_imax(a_), dark_abs_imax(b_));
}

uintmax_t dark_lcm_u(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(0 == a_ || 0 == b_)
    {
        return 0;
    }

    return (a_ * b_) / dark_gcd_u(a_, b_);
}

uintmax_t dark_lcm_i(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    return dark_lcm_u(dark_abs_imax(a_), dark_abs_imax(b_));
}
