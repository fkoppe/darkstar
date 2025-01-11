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
    return sinf(value_);
}

float dark_cos_f(const float value_)
{
    return cosf(value_);
}

float dark_tan_f(const float value_)
{
    return tanf(value_);
}

float dark_asin_f(const float value_)
{
    return asinf(value_);
}

float dark_acos_f(const float value_)
{
    return acosf(value_);
}

float dark_atan_f(const float value_)
{
    return atanf(value_);
}

float dark_exp_f(float value_)
{
    return expf(value_);
}

float dark_exp2_f(float value_)
{
    return exp2f(value_);
}

float dark_log_f(float value_)
{
    return logf(value_);
}

float dark_log10_f(float value_)
{
    return log10f(value_);
}

float dark_pow_f(float base_, float exponent_)
{
    return powf(base_, exponent_);
}

float dark_sqrt_f(float value_)
{
    return sqrtf(value_);
}

float dark_abs_f(float value_)
{
    return fabsf(value_);
}

float dark_mod_f(float value_, float mod_)
{
    return fmodf(value_, mod_);
}

float dark_ceil_f(float value_)
{
    return ceilf(value_);
}

float dark_floor_f(float value_)
{
    return floorf(value_);
}

float dark_round_f(float value_)
{
    return roundf(value_);
}

bool dark_nan_is_f(float value_)
{
    return isnan(value_);
}

bool dark_infinite_is_f(float value_)
{
    return isinf(value_);
}
