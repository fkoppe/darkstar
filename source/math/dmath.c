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
    return sin(value_);
}

double dark_cos_d(double value_)
{
    return cos(value_);
}

double dark_tan_d(double value_)
{
    return tan(value_);
}

double dark_asin_d(double value_)
{
    return asin(value_);
}

double dark_acos_d(double value_)
{
    return acos(value_);
}

double dark_atan_d(double value_)
{
    return atan(value_);
}

double dark_exp_d(double value_)
{
    return exp(value_);
}

double dark_exp2_d(double value_)
{
    return exp2(value_);
}

double dark_log_d(double value_)
{
    return log(value_);
}

double dark_log10_d(double value_)
{
    return log10(value_);
}

double dark_pow_d(double base_, double exponent_)
{
    return pow(base_, exponent_);
}

double dark_sqrt_d(double value_)
{
    return sqrt(value_);
}

double dark_abs_d(double value_)
{
    return fabs(value_);
}

double dark_mod_d(double value_, double mod_)
{
    return fmod(value_, mod_);
}

double dark_ceil_d(double value_)
{
    return ceil(value_);
}

double dark_dloor_d(double value_)
{
    return floor(value_);
}

double dark_round_d(double value_)
{
    return round(value_);
}

bool dark_nan_is_d(double value_)
{
    return isnan(value_);
}

bool dark_ifinite_is_d(double value_)
{
    return isinf(value_);
}
