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
#define DARK_UNIT "sat_cast"

uint8_t dark_sat_ucast_u8(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, UINT8_MAX);
}

uint16_t dark_sat_ucast_u16(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, UINT16_MAX);
}

uint32_t dark_sat_ucast_u32(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, UINT32_MAX);
}

uint64_t dark_sat_ucast_u64(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, UINT64_MAX);
}

int8_t dark_sat_ucast_i8(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, INT8_MAX);
}

int16_t dark_sat_ucast_i16(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, INT16_MAX);
}

int32_t dark_sat_ucast_i32(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, INT32_MAX);
}

int64_t dark_sat_ucast_i64(const uintmax_t u_)
{
    //u_

    return DARK_MIN(u_, INT64_MAX);
}

uint8_t dark_sat_icast_u8(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, 0, UINT8_MAX);
}

uint16_t dark_sat_icast_u16(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, 0, UINT16_MAX);
}

uint32_t dark_sat_icast_u32(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, 0, UINT32_MAX);
}

uint64_t dark_sat_icast_u64(const intmax_t i_)
{
    //i_

    return DARK_MAX(0, i_);
}

int8_t dark_sat_icast_i8(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, INT8_MIN, INT8_MAX);
}

int16_t dark_sat_icast_i16(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, INT16_MIN, INT16_MAX);
}

int32_t dark_sat_icast_i32(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, INT32_MIN, INT32_MAX);
}

int64_t dark_sat_icast_i64(const intmax_t i_)
{
    //i_

    return dark_range_clamp_i(i_, INT64_MIN, INT64_MAX);
}
