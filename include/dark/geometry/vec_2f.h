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

#if !defined(___DARK___VEC_2F_H)
#define ___DARK___VEC_2F_H

#include <dark/core/std.h>

typedef struct Dark_Vec_2f Dark_Vec_2f;
struct Dark_Vec_2f
{
    float x;
    float y;
};

Dark_Vec_2f dark_vec_2f_create(float x, float y);
Dark_Vec_2f dark_vec_2f_zero(void);

float dark_vec_2f_x(Dark_Vec_2f vec2);
float dark_vec_2f_y(Dark_Vec_2f vec2);

Dark_Vec_2f dark_vec_2f_add(Dark_Vec_2f a, Dark_Vec_2f b);
Dark_Vec_2f dark_vec_2f_sub(Dark_Vec_2f minuend, Dark_Vec_2f subtrahend);
Dark_Vec_2f dark_vec_2f_mult(Dark_Vec_2f vec2, float scalar);
Dark_Vec_2f dark_vec_2f_div(Dark_Vec_2f vec2, float scalar);

Dark_Vec_2f dark_vec_2f_normalize(Dark_Vec_2f vec2);
Dark_Vec_2f dark_vec_2f_perpendicular(Dark_Vec_2f vec2);

float dark_vec_2f_cross(Dark_Vec_2f a, Dark_Vec_2f b);

float dark_vec_2f_dot_f(Dark_Vec_2f a, Dark_Vec_2f b);
float dark_vec_2f_angle_f(Dark_Vec_2f a, Dark_Vec_2f b);
float dark_vec_2f_lenght_f(Dark_Vec_2f vec2);

double dark_vec_2f_dot_d(Dark_Vec_2f a, Dark_Vec_2f b);
double dark_vec_2f_angle_d(Dark_Vec_2f a, Dark_Vec_2f b);
double dark_vec_2f_lenght_d(Dark_Vec_2f vec2);

#endif // !defined(___DARK___VEC_2F_H)
