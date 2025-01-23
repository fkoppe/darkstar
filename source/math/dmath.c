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
#define DARK_UNIT "dmath"

double dark_sin_d(double value_)
{
    //value_

    return sin(value_);
}

double dark_cos_d(double value_)
{
    //value_

    return cos(value_);
}

double dark_tan_d(double value_)
{
    //value_

    return tan(value_);
}

double dark_asin_d(double value_)
{
    DARK_ASSERT(value_ >= -1.0f && value_ <= 1.0f, DARK_ERROR_MATH);

    return asin(value_);
}

double dark_acos_d(double value_)
{
    DARK_ASSERT(value_ >= -1.0f && value_ <= 1.0f, DARK_ERROR_MATH);

    return acos(value_);
}

double dark_atan_d(double value_)
{
    //value_

    return atan(value_);
}

double dark_exp_d(double value_)
{
    //value_

    return exp(value_);
}

double dark_exp2_d(double value_)
{
    //value_

    return exp2(value_);
}

double dark_log_d(double value_)
{
    DARK_ASSERT(value_ > 0.0f, DARK_ERROR_MATH);

    return log(value_);
}

double dark_log10_d(double value_)
{
    DARK_ASSERT(value_ > 0.0f, DARK_ERROR_MATH);

    return log10(value_);
}

double dark_pow_d(double base_, double exponent_)
{
    DARK_ASSERT(!(base_ < 0.0f && exponent_ != dark_floor_f(exponent_)), DARK_ERROR_MATH);

    return pow(base_, exponent_);
}

double dark_sqrt_d(double value_)
{
    DARK_ASSERT(value_ >= 0.0f, DARK_ERROR_MATH);

    return sqrt(value_);
}

double dark_abs_d(double value_)
{
    //value_

    return fabs(value_);
}

double dark_mod_d(double value_, double mod_)
{
    //value_
    DARK_ASSERT(0.0f != mod_, DARK_ERROR_MATH);

    return fmod(value_, mod_);
}

double dark_ceil_d(double value_)
{
    //value_

    return ceil(value_);
}

double dark_dloor_d(double value_)
{
    //value_

    return floor(value_);
}

double dark_round_d(double value_)
{
    //value_

    return round(value_);
}

double dark_min_d(const double a_, const double b_)
{
    //a_
    //b_

    return DARK_MIN(a_, b_);
}

double dark_max_d(const double a_, const double b_)
{
    //a_
    //b_

    return DARK_MAX(a_, b_);
}

bool dark_nan_is_d(double value_)
{
    //value_

    return isnan(value_);
}

bool dark_ifinite_is_d(double value_)
{
    //value_

    return isinf(value_);
}

bool dark_range_is_d(const double d_, const double lower_, const double upper_)
{
    //d_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    return d_ >= lower_ && d_ <= upper_;
}

double dark_range_clamp_d(const double d_, const double lower_, const double upper_)
{
    //d_
    DARK_ASSERT(lower_ <= upper_, DARK_ERROR_LOGIC);

    if(d_ < lower_)
    {
        return lower_;
    }
    else if(d_ > upper_)
    {
        return upper_;
    }
    else
    {
        return d_;
    }
}

int8_t dark_compare_d(const double* const element_, const double* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    const double diff = dark_abs_f(*element_ - *other_);

    if(diff < DARK_EPSILON_D)
    {
        return 0;
    }
    else if(*element_ < *other_)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
