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
#define DARK_UNIT "cast"

uint8_t dark_ucast_u8(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= UINT8_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

uint16_t dark_ucast_u16(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= UINT16_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

uint32_t dark_ucast_u32(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= UINT32_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

uint64_t dark_ucast_u64(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= UINT64_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

size_t dark_ucast_zu(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= SIZE_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

int8_t dark_ucast_i8(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= INT8_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

int16_t dark_ucast_i16(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= INT16_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

int32_t dark_ucast_i32(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= INT32_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

int64_t dark_ucast_i64(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= INT64_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

intmax_t dark_ucast_imax(const uintmax_t u_)
{
    //u_

    DARK_ASSERT(u_ <= INTMAX_MAX, DARK_ERROR_OVERFLOW);

    return u_;
}

uint8_t dark_icast_u8(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= UINT8_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

uint16_t dark_icast_u16(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= UINT16_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

uint32_t dark_icast_u32(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= UINT32_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

uint64_t dark_icast_u64(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= UINT64_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

size_t dark_icast_zu(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= SIZE_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

int8_t dark_icast_i8(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= INT8_MIN, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= INT8_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

int16_t dark_icast_i16(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= INT16_MIN, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= INT16_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

int32_t dark_icast_i32(const intmax_t i_)
{
    //i_
    DARK_ASSERT(i_ >= INT32_MIN, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= INT32_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}

int64_t dark_icast_i64(const intmax_t i_)
{
    //i_

    DARK_ASSERT(i_ >= INT64_MIN, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(i_ <= INT64_MAX, DARK_ERROR_OVERFLOW);

    return i_;
}
