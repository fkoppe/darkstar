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

#include <math.h>

#undef DARK_UNIT
#define DARK_UNIT "fmath"

float dark_sin_f(const float value_)
{
    //value_

    return sinf(value_);
}

float dark_cos_f(const float value_)
{
    //value_

    return cosf(value_);
}

float dark_tan_f(const float value_)
{
    //value_

    return tanf(value_);
}

float dark_asin_f(const float value_)
{
    DARK_ASSERT(value_ >= -1.0f && value_ <= 1.0f, DARK_ERROR_MATH);

    return asinf(value_);
}

float dark_acos_f(const float value_)
{
    DARK_ASSERT(value_ >= -1.0f && value_ <= 1.0f, DARK_ERROR_MATH);

    return acosf(value_);
}

float dark_atan_f(const float value_)
{
    //value_

    return atanf(value_);
}

float dark_exp_f(const float value_)
{
    //value_

    return expf(value_);
}

float dark_exp2_f(const float value_)
{
    //value_

    return exp2f(value_);
}

float dark_log_f(const float value_)
{
    DARK_ASSERT(value_ > 0.0f, DARK_ERROR_MATH);

    return logf(value_);
}

float dark_log10_f(const float value_)
{
    DARK_ASSERT(value_ > 0.0f, DARK_ERROR_MATH);

    return log10f(value_);
}

float dark_pow_f(const float base_, const float exponent_)
{
    DARK_ASSERT(!(base_ < 0.0f && exponent_ != dark_floor_f(exponent_)), DARK_ERROR_MATH);

    return powf(base_, exponent_);
}

float dark_sqrt_f(const float value_)
{
    DARK_ASSERT(value_ >= 0.0f, DARK_ERROR_MATH);

    return sqrtf(value_);
}

float dark_abs_f(const float value_)
{
    //value_

    return fabsf(value_);
}

float dark_mod_f(const float value_, const float mod_)
{
    //value_
    DARK_ASSERT(0.0f != mod_, DARK_ERROR_MATH);

    return fmodf(value_, mod_);
}

float dark_ceil_f(const float value_)
{
    //value_

    return ceilf(value_);
}

float dark_floor_f(const float value_)
{
    //value_

    return floorf(value_);
}

float dark_round_f(const float value_)
{
    //value_

    return roundf(value_);
}

bool dark_nan_is_f(const float value_)
{
    //value_

    return isnan(value_);
}

bool dark_infinite_is_f(const float value_)
{
    //value_

    return isinf(value_);
}

bool dark_range_is_f(const float f_, const float lower_, const float upper_)
{
    //f_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return f_ >= lower_ && f_ <= upper_;
}

float dark_range_clamp_f(const float f_, const float lower_, const float upper_)
{
    //f_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if (f_ < lower_)
    {
        return lower_;
    }
    else if (f_ > upper_)
    {
        return upper_;
    }
    else
    {
        return f_;
    }
}

int8_t dark_compare_f(const float* const element_, const float* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    const float diff = dark_abs_f(*element_ - *other_);

    if (diff < DARK_EPSILON_F)
    {
        return 0;
    }
    else if (*element_ < *other_)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
