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
#define DARK_UNIT "sat_add"

uint8_t dark_sat_add_u8(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > UINT8_MAX)
    {
        return UINT8_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > UINT8_MAX)
        {
            return UINT8_MAX;
        }
    }

    return u_ + i_;
}

uint16_t dark_sat_add_u16(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > UINT16_MAX)
    {
        return UINT16_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > UINT16_MAX)
        {
            return UINT16_MAX;
        }
    }

    return u_ + i_;
}

uint32_t dark_sat_add_u32(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > UINT32_MAX)
    {
        return UINT32_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > UINT32_MAX)
        {
            return UINT32_MAX;
        }
    }

    return u_ + i_;
}

uint64_t dark_sat_add_u64(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > UINT64_MAX)
    {
        return UINT64_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > UINT64_MAX)
        {
            return UINT64_MAX;
        }
    }

    return u_ + i_;
}

uintmax_t dark_sat_add_umax(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > UINTMAX_MAX)
    {
        return UINTMAX_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > UINTMAX_MAX)
        {
            return UINTMAX_MAX;
        }
    }

    return u_ + i_;
}

size_t dark_sat_add_zu(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > SIZE_MAX)
    {
        return SIZE_MAX;
    }

    if(i_ < 0)
    {
        if(-i_ > u_)
        {
            return 0;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > SIZE_MAX)
        {
            return SIZE_MAX;
        }
    }

    return u_ + i_;
}

uint8_t dark_sat_uadd_u8(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > UINT8_MAX || b_ > UINT8_MAX || dark_max_umax(a_, b_) > UINT8_MAX - dark_min_umax(a_, b_))
    {
        return UINT8_MAX;
    }

    return a_ + b_;
}

uint16_t dark_sat_uadd_u16(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > UINT16_MAX || b_ > UINT16_MAX || dark_max_umax(a_, b_) > UINT16_MAX - dark_min_umax(a_, b_))
    {
        return UINT16_MAX;
    }

    return a_ + b_;
}

uint32_t dark_sat_uadd_u32(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > UINT32_MAX || b_ > UINT32_MAX || dark_max_umax(a_, b_) > UINT32_MAX - dark_min_umax(a_, b_))
    {
        return UINT32_MAX;
    }

    return a_ + b_;
}

uint64_t dark_sat_uadd_u64(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > UINT64_MAX || b_ > UINT64_MAX || dark_max_umax(a_, b_) > UINT64_MAX - dark_min_umax(a_, b_))
    {
        return UINT64_MAX;
    }

    return a_ + b_;
}

uintmax_t dark_sat_uadd_umax(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > UINTMAX_MAX || b_ > UINTMAX_MAX || dark_max_umax(a_, b_) > UINTMAX_MAX - dark_min_umax(a_, b_))
    {
        return UINTMAX_MAX;
    }

    return a_ + b_;
}

size_t dark_sat_uadd_zu(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > SIZE_MAX || b_ > SIZE_MAX || dark_max_umax(a_, b_) > SIZE_MAX - dark_min_umax(a_, b_))
    {
        return SIZE_MAX;
    }

    return a_ + b_;
}

uint8_t dark_sat_iadd_u8(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_add_u8(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_u8(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

uint16_t dark_sat_iadd_u16(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_u16(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_u16(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

uint32_t dark_sat_iadd_u32(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_u32(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_u32(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

uint64_t dark_sat_iadd_u64(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_u64(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_u64(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

uintmax_t dark_sat_iadd_umax(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_umax(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_umax(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

size_t dark_sat_iadd_zu(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_zu(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return 0;
    }
    else
    {
        return dark_sat_add_zu(DARK_MAX(a_, b_), DARK_MIN(a_, b_));
    }
}

int8_t dark_sat_add_i8(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > INT8_MAX)
    {
        return INT8_MAX;
    }

    if(i_ < 0)
    {
        if(u_ > INT8_MAX - i_)
        {
            return INT8_MAX;
        }

        if((intmax_t)(u_ + i_) < INT8_MIN)
        {
            return INT8_MIN;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > INT8_MAX)
        {
            return INT8_MAX;
        }
    }

    return u_ + i_;
}

int16_t dark_sat_add_i16(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > INT16_MAX)
    {
        return INT16_MAX;
    }

    if(i_ < 0)
    {
        if(u_ > INT16_MAX - i_)
        {
            return INT16_MAX;
        }

        if((intmax_t)(u_ + i_) < INT16_MIN)
        {
            return INT16_MIN;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > INT16_MAX)
        {
            return INT16_MAX;
        }
    }

    return u_ + i_;
}

int32_t dark_sat_add_i32(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > INT32_MAX)
    {
        return INT32_MAX;
    }

    if(i_ < 0)
    {
        if(u_ > INT32_MAX - i_)
        {
            return INT32_MAX;
        }

        if((intmax_t)(u_ + i_) < INT32_MIN)
        {
            return INT32_MIN;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > INT32_MAX)
        {
            return INT32_MAX;
        }
    }

    return u_ + i_;
}

int64_t dark_sat_add_i64(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > INT64_MAX)
    {
        return INT64_MAX;
    }

    if(i_ < 0)
    {
        if(u_ > INT64_MAX - i_)
        {
            return INT64_MAX;
        }

        if((intmax_t)(u_ + i_) < INT64_MIN)
        {
            return INT64_MIN;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > INT64_MAX)
        {
            return INT64_MAX;
        }
    }

    return u_ + i_;
}

intmax_t dark_sat_add_imax(const uintmax_t u_, const intmax_t i_)
{
    //u_
    //i_

    if(i_ > INTMAX_MAX)
    {
        return INTMAX_MAX;
    }

    if(i_ < 0)
    {
        if(u_ > INTMAX_MAX - i_)
        {
            return INTMAX_MAX;
        }

        if((intmax_t)(u_ + i_) < INTMAX_MIN)
        {
            return INTMAX_MIN;
        }
    }
    else
    {
        if(u_ > UINTMAX_MAX - i_ || u_ + i_ > INTMAX_MAX)
        {
            return INTMAX_MAX;
        }
    }

    return u_ + i_;
}

int8_t dark_sat_uadd_i8(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > INT8_MAX || b_ > INT8_MAX)
    {
        return INT8_MAX;
    }

    if(dark_max_umax(a_, b_) > (uintmax_t)INT8_MAX - dark_min_umax(a_, b_))
    {
        return INT8_MAX;
    }

    return a_ + b_;
}

int16_t dark_sat_uadd_i16(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > INT16_MAX || b_ > INT16_MAX)
    {
        return INT16_MAX;
    }

    if(dark_max_umax(a_, b_) > (uintmax_t)INT16_MAX - dark_min_umax(a_, b_))
    {
        return INT16_MAX;
    }

    return a_ + b_;
}

int32_t dark_sat_uadd_i32(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > INT32_MAX || b_ > INT32_MAX)
    {
        return INT32_MAX;
    }

    if(dark_max_umax(a_, b_) > (uintmax_t)INT32_MAX - dark_min_umax(a_, b_))
    {
        return INT32_MAX;
    }

    return a_ + b_;
}

int64_t dark_sat_uadd_i64(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > INT64_MAX || b_ > INT64_MAX)
    {
        return INT64_MAX;
    }

    if(dark_max_umax(a_, b_) > (uintmax_t)INT64_MAX - dark_min_umax(a_, b_))
    {
        return INT64_MAX;
    }

    return a_ + b_;
}

intmax_t dark_sat_uadd_imax(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > INTMAX_MAX || b_ > INTMAX_MAX)
    {
        return INTMAX_MAX;
    }

    if(dark_max_umax(a_, b_) > (uintmax_t)INTMAX_MAX - dark_min_umax(a_, b_))
    {
        return INTMAX_MAX;
    }

    return a_ + b_;
}

int8_t dark_sat_iadd_i8(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_i8(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return -dark_sat_uadd_i8(-a_, -b_);
    }
    else
    {
        return dark_sat_add_i8(dark_max_imax(a_, b_), dark_min_imax(a_, b_));
    }
}

int16_t dark_sat_iadd_i16(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_i16(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return -dark_sat_uadd_i16(-a_, -b_);
    }
    else
    {
        return dark_sat_add_i16(dark_max_imax(a_, b_), dark_min_imax(a_, b_));
    }
}

int32_t dark_sat_iadd_i32(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_i32(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return -dark_sat_uadd_i32(-a_, -b_);
    }
    else
    {
        return dark_sat_add_i32(dark_max_imax(a_, b_), dark_min_imax(a_, b_));
    }
}

int64_t dark_sat_iadd_i64(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_i64(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return -dark_sat_uadd_i64(-a_, -b_);
    }
    else
    {
        return dark_sat_add_i64(dark_max_imax(a_, b_), dark_min_imax(a_, b_));
    }
}

intmax_t dark_sat_iadd_imax(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_sat_uadd_imax(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return -dark_sat_uadd_imax(-a_, -b_);
    }
    else
    {
        return dark_sat_add_imax(dark_max_imax(a_, b_), dark_min_imax(a_, b_));
    }
}
