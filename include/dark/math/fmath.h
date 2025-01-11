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

#if !defined(___DARK___FMATH_H)
#define ___DARK___FMATH_H

#include <dark/core/std.h>

#include <float.h>

#define DARK_INFINITY_F = (1.0f / 0.0f)
#define DARK_NEGATVIE_INFINITY_F = (-1.0f / 0.0f)
#define DARK_NAN_F (0.0f / 0.0f)

float dark_sin_f(float value);
float dark_cos_f(float value);
float dark_tan_f(float value);

float dark_asin_f(float value);
float dark_acos_f(float value);
float dark_atan_f(float value);

float dark_exp_f(float value);
float dark_exp2_f(float value);
float dark_log_f(float value);
float dark_log10_f(float value);

float dark_pow_f(float base, float exponent);
float dark_sqrt_f(float value);

float dark_abs_f(float value);
float dark_mod_f(float value, float mod);
float dark_ceil_f(float value);
float dark_floor_f(float value);
float dark_round_f(float value);

bool dark_nan_is_f(float value);
bool dark_ifinite_is_f(float value);

#endif // !defined(___DARK___FLOAT_H)
