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

#include "geometry_module.h"

#include <dark/core/std.h>
#include <dark/geometry/geometry.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "geometry"

Dark_Vec_2f dark_vec_2f_create(const float x_, const float y_)
{
    //x_
    //y_

    Dark_Vec_2f vec;
    vec.x = x_;
    vec.y = y_;

    return vec;
}

Dark_Vec_2f dark_vec_2f_zero(void)
{
    return dark_vec_2f_create(0.0f, 0.0f);
}

float dark_vec_2f_x(const Dark_Vec_2f vec2_)
{
    //vec2_

    return vec2_.x;
}

float dark_vec_2f_y(const Dark_Vec_2f vec2_)
{
    //vec2_

    return vec2_.y;
}

Dark_Vec_2f dark_vec_2f_add(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    Dark_Vec_2f vec;
    vec.x = a_.x + b_.x;
    vec.y = a_.y + b_.y;

    return vec;
}

Dark_Vec_2f dark_vec_2f_sub(const Dark_Vec_2f minuend_, const Dark_Vec_2f subtrahend_)
{
    //minuend_
    //subtrahend_

    Dark_Vec_2f vec;
    vec.x = minuend_.x - subtrahend_.x;
    vec.y = minuend_.y - subtrahend_.y;

    return vec;
}

Dark_Vec_2f dark_vec_2f_mult(const Dark_Vec_2f vec2_, const float scalar_)
{
    //vec2_
    //scalar_

    Dark_Vec_2f vec;
    vec.x = vec2_.x * scalar_;
    vec.y = vec2_.y * scalar_;

    return vec;
}

Dark_Vec_2f dark_vec_2f_div(const Dark_Vec_2f vec2_, const float scalar_)
{
    //vec2_
    //scalar_

    Dark_Vec_2f vec;
    vec.x = vec2_.x / scalar_;
    vec.y = vec2_.y / scalar_;

    return vec;
}

Dark_Vec_2f dark_vec_2f_normalize(const Dark_Vec_2f vec2_)
{
    //vec2_

    return dark_vec_2f_div(vec2_, dark_vec_2f_lenght_f(vec2_));
}

Dark_Vec_2f dark_vec_2f_perpendicular(const Dark_Vec_2f vec2_)
{
    //vec2_

    Dark_Vec_2f vec;
    vec.x = -vec2_.y;
    vec.y = vec2_.x;

    return vec;
}

float dark_vec_2f_cross(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    return a_.x * b_.y - a_.y * b_.x;
}

float dark_vec_2f_dot_f(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    return a_.x * b_.x + a_.y * b_.y;
}

float dark_vec_2f_angle_f(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    const float dot = dark_vec_2f_dot_f(a_, b_);

    float len_a = dark_vec_2f_lenght_f(a_);
    float len_b = dark_vec_2f_lenght_f(b_);

    if(len_a == 0.0f || len_b == 0.0f)
    {
        return 0.0f;
    }

    float cos_theta = dot / (len_a * len_b);
    cos_theta = dark_range_clamp_f(cos_theta, -1.0f, 1.0f);

    return dark_acos_f(cos_theta);
}

float dark_vec_2f_lenght_f(const Dark_Vec_2f vec2_)
{
    return dark_sqrt_f(vec2_.x * vec2_.x + vec2_.y * vec2_.y);
}

double dark_vec_2f_dot_d(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    return (double)a_.x * (double)b_.x + (double)a_.y * (double)b_.y;
}

double dark_vec_2f_angle_d(const Dark_Vec_2f a_, const Dark_Vec_2f b_)
{
    //a_
    //b_

    const float dot = dark_vec_2f_dot_d(a_, b_);

    const float len_a = dark_vec_2f_lenght_d(a_);
    const float len_b = dark_vec_2f_lenght_d(b_);

    if(len_a == 0.0f || len_b == 0.0f)
    {
        return 0.0f;
    }

    float cos_theta = dot / (len_a * len_b);
    cos_theta = dark_range_clamp_d(cos_theta, -1.0f, 1.0f);

    return dark_acos_d(cos_theta);
}

double dark_vec_2f_lenght_d(const Dark_Vec_2f vec2_)
{
    return dark_sqrt_d((double)vec2_.x * (double)vec2_.x + (double)vec2_.y * (double)vec2_.y);
}
