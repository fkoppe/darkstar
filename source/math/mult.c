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
#define DARK_UNIT "mult"

uint8_t dark_mult_u8(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= UINT8_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint16_t dark_mult_u16(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= UINT16_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint32_t dark_mult_u32(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= UINT32_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint64_t dark_mult_u64(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= UINT64_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uintmax_t dark_mult_umax(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= UINTMAX_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

size_t dark_mult_zu(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ >= 0, DARK_ERROR_UNDERFLOW);
        DARK_ASSERT(b_ <= SIZE_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint8_t dark_umult_u8(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= UINT8_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint16_t dark_umult_u16(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= UINT16_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint32_t dark_umult_u32(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= UINT32_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint64_t dark_umult_u64(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= UINT64_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uintmax_t dark_umult_umax(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= UINTMAX_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

size_t dark_umult_zu(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if(a_ > 0)
    {
        DARK_ASSERT(b_ <= SIZE_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

uint8_t dark_imult_u8(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_u8(a_, b_);
    }
    else
    {
        return dark_umult_u8(-a_, -b_);
    }
}

uint16_t dark_imult_u16(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    DARK_ASSERT((a_ >= 0 && b_ >= 0) || (a_ < 0 && b_ < 0), DARK_ERROR_UNDERFLOW);

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_u16(a_, b_);
    }
    else
    {
        return dark_umult_u16(-a_, -b_);
    }
}

uint32_t dark_imult_u32(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    DARK_ASSERT((a_ >= 0 && b_ >= 0) || (a_ < 0 && b_ < 0), DARK_ERROR_UNDERFLOW);

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_u32(a_, b_);
    }
    else
    {
        return dark_umult_u32(-a_, -b_);
    }
}

uint64_t dark_imult_u64(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    DARK_ASSERT((a_ >= 0 && b_ >= 0) || (a_ < 0 && b_ < 0), DARK_ERROR_UNDERFLOW);

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_u64(a_, b_);
    }
    else
    {
        return dark_umult_u64(-a_, -b_);
    }
}

uintmax_t dark_imult_umax(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    DARK_ASSERT((a_ >= 0 && b_ >= 0) || (a_ < 0 && b_ < 0), DARK_ERROR_UNDERFLOW);

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_umax(a_, b_);
    }
    else
    {
        return dark_umult_umax(-a_, -b_);
    }
}

size_t dark_imult_zu(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    DARK_ASSERT((a_ >= 0 && b_ >= 0) || (a_ < 0 && b_ < 0), DARK_ERROR_UNDERFLOW);

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_zu(a_, b_);
    }
    else
    {
        return dark_umult_zu(-a_, -b_);
    }
}

int8_t dark_mult_i8(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(b_ >= 0)
    {
        return dark_umult_i8(a_, b_);
    }
    else
    {
        return -dark_umult_i8(a_, -b_);
    }
}

int16_t dark_mult_i16(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(b_ >= 0)
    {
        return dark_umult_i16(a_, b_);
    }
    else
    {
        return -dark_umult_i16(a_, -b_);
    }
}

int32_t dark_mult_i32(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(b_ >= 0)
    {
        return dark_umult_i32(a_, b_);
    }
    else
    {
        return -dark_umult_i32(a_, -b_);
    }
}

int64_t dark_mult_i64(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(b_ >= 0)
    {
        return dark_umult_i64(a_, b_);
    }
    else
    {
        return -dark_umult_i64(a_, -b_);
    }
}

intmax_t dark_mult_imax(const uintmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(b_ >= 0)
    {
        return dark_umult_imax(a_, b_);
    }
    else
    {
        return -dark_umult_imax(a_, -b_);
    }
}

int8_t dark_umult_i8(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if (a_ > 0)
    {
        DARK_ASSERT(b_ <= INT8_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

int16_t dark_umult_i16(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if (a_ > 0)
    {
        DARK_ASSERT(b_ <= INT16_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

int32_t dark_umult_i32(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if (a_ > 0)
    {
        DARK_ASSERT(b_ <= INT32_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

int64_t dark_umult_i64(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if (a_ > 0)
    {
        DARK_ASSERT(b_ <= INT64_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

intmax_t dark_umult_imax(const uintmax_t a_, const uintmax_t b_)
{
    //a_
    //b_

    if (a_ > 0)
    {
        DARK_ASSERT(b_ <= INTMAX_MAX / a_, DARK_ERROR_OVERFLOW);
    }

    return a_ * b_;
}

int8_t dark_imult_i8(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_i8(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return dark_umult_i8(-a_, -b_);
    }
    else
    {
        const intmax_t min = dark_min_imax(a_, b_);
        const uintmax_t max = dark_max_umax(a_, b_);

        return dark_mult_i8(max, min);
    }
}

int16_t dark_imult_i16(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_i16(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return dark_umult_i16(-a_, -b_);
    }
    else
    {
        const intmax_t min = dark_min_imax(a_, b_);
        const uintmax_t max = dark_max_umax(a_, b_);

        return dark_mult_i16(max, min);
    }
}

int32_t dark_imult_i32(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_i32(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return dark_umult_i32(-a_, -b_);
    }
    else
    {
        const intmax_t min = dark_min_imax(a_, b_);
        const uintmax_t max = dark_max_umax(a_, b_);

        return dark_mult_i32(max, min);
    }
}

int64_t dark_imult_i64(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_i64(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return dark_umult_i64(-a_, -b_);
    }
    else
    {
        const intmax_t min = dark_min_imax(a_, b_);
        const uintmax_t max = dark_max_umax(a_, b_);

        return dark_mult_i64(max, min);
    }
}

intmax_t dark_imult_imax(const intmax_t a_, const intmax_t b_)
{
    //a_
    //b_

    if(a_ >= 0 && b_ >= 0)
    {
        return dark_umult_imax(a_, b_);
    }
    else if(a_ < 0 && b_ < 0)
    {
        return dark_umult_imax(-a_, -b_);
    }
    else
    {
        const intmax_t min = dark_min_imax(a_, b_);
        const uintmax_t max = dark_max_umax(a_, b_);

        return dark_mult_imax(max, min);
    }
}
