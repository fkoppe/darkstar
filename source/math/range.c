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
#define DARK_UNIT "range"

bool dark_range_is_u(const uintmax_t u_, const uintmax_t lower_, const uintmax_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return u_ >= lower_ && u_ <= upper_;
}

bool dark_range_is_i(const intmax_t i_, const intmax_t lower_, const intmax_t upper_)
{
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return i_ >= lower_ && i_ <= upper_;
}

uintmax_t dark_range_clamp_u(const uintmax_t u_, const uintmax_t lower_, const uintmax_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if(u_ < lower_)
    {
        return dark_max_umax(lower_, dark_min_umax(upper_, u_));
    }
    else
    {
        return dark_min_umax(upper_, dark_max_umax(lower_, u_));
    }
}

intmax_t dark_range_clamp_i(const intmax_t i_, const intmax_t lower_, const intmax_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if(i_ < lower_)
    {
        return dark_max_imax(lower_, dark_min_imax(upper_, i_));
    }
    else
    {
        return dark_min_imax(upper_, dark_max_imax(lower_, i_));
    }
}
