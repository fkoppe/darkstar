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

#if !defined(___DARK___DMATH_H)
#define ___DARK___DMATH_H

#include <dark/core/std.h>

#include <float.h>

#define DARK_INFINITY_D = (1.0 / 0.0)
#define DARK_NEGATVIE_INFINITY_D = (-1.0 / 0.0)
#define DARK_NAN_D (0.0 / 0.0)

double dark_sin_d(double value);
double dark_cos_d(double value);
double dark_tan_d(double value);

double dark_asin_d(double value);
double dark_acos_d(double value);
double dark_atan_d(double value);

double dark_exp_d(double value);
double dark_exp2_d(double value);
double dark_log_d(double value);
double dark_log10_d(double value);

double dark_pow_d(double base, double exponent);
double dark_sqrt_d(double value);

double dark_abs_d(double value);
double dark_mod_d(double value, double mod);
double dark_ceil_d(double value);
double dark_dloor_d(double value);
double dark_round_d(double value);

bool dark_nan_is_d(double value);
bool dark_ifinite_is_d(double value);

#endif // !defined(___DARK___DMATH_H)
