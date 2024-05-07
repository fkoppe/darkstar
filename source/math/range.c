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

bool dark_range_is_u(const uint64_t u_, const uint64_t lower_, const uint64_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return u_ >= lower_ && u_ <= upper_;
}

bool dark_range_is_i(const int64_t i_, const int64_t lower_, const int64_t upper_)
{
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return i_ >= lower_ && i_ <= upper_;
}

uint64_t dark_range_clamp_u(const uint64_t u_, const uint64_t lower_, const uint64_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if(u_ < lower_)
    {
        return dark_max_u64(lower_, dark_min_u64(upper_, u_));
    }
    else
    {
        return dark_min_u64(upper_, dark_max_u64(lower_, u_));
    }
}

int64_t dark_range_clamp_i(const int64_t i_, const int64_t lower_, const int64_t upper_)
{
    //u_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if(i_ < lower_)
    {
        return dark_max_i64(lower_, dark_min_i64(upper_, i_));
    }
    else
    {
        return dark_min_i64(upper_, dark_max_i64(lower_, i_));
    }
}
