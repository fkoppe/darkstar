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

Dark_Vec_3f dark_vec_3f_create(const float x_, const float y_, const float z_)
{
    //x_
    //y_

    Dark_Vec_3f vec;
    vec.x = x_;
    vec.y = y_;
    vec.z = z_;

    return vec;
}

Dark_Vec_3f dark_vec_3f_zero(void)
{
    return dark_vec_3f_create(0.0f, 0.0f, 0.0f);
}

float dark_vec_3f_x(const Dark_Vec_3f vec3_)
{
    //vec3_

    return vec3_.x;
}

float dark_vec_3f_y(const Dark_Vec_3f vec3_)
{
    //vec3_

    return vec3_.y;
}

float dark_vec_3f_z(const Dark_Vec_3f vec3_)
{
    //vec3_

    return vec3_.z;
}

Dark_Vec_3f dark_vec_3f_add(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    Dark_Vec_3f vec;
    vec.x = a_.x + b_.x;
    vec.y = a_.y + b_.y;
    vec.z = a_.z + b_.z;

    return vec;
}

Dark_Vec_3f dark_vec_3f_sub(const Dark_Vec_3f minuend_, const Dark_Vec_3f subtrahend_)
{
    //minuend_
    //subtrahend_

    Dark_Vec_3f vec;
    vec.x = minuend_.x - subtrahend_.x;
    vec.y = minuend_.y - subtrahend_.y;
    vec.z = minuend_.z - subtrahend_.z;

    return vec;
}

Dark_Vec_3f dark_vec_3f_mult(const Dark_Vec_3f vec3_, const float scalar_)
{
    //vec3_
    //scalar_

    Dark_Vec_3f vec;
    vec.x = vec3_.x * scalar_;
    vec.y = vec3_.y * scalar_;
    vec.z = vec3_.z * scalar_;

    return vec;
}

Dark_Vec_3f dark_vec_3f_div(const Dark_Vec_3f vec3_, const float scalar_)
{
    //vec3_
    //scalar_

    Dark_Vec_3f vec;
    vec.x = vec3_.x / scalar_;
    vec.y = vec3_.y / scalar_;
    vec.z = vec3_.z / scalar_;

    return vec;
}

Dark_Vec_3f dark_vec_3f_normalize(const Dark_Vec_3f vec3_)
{
    //vec3_

    return dark_vec_3f_div(vec3_, dark_vec_3f_lenght_f(vec3_));
}

Dark_Vec_3f dark_vec_3f_perpendicular(const Dark_Vec_3f vec3_)
{
    //vec3_

    const Dark_Vec_3f other_x = { 1.0f, 0.0f, 0.0f };

    Dark_Vec_3f vec;

    if(vec3_.x == 0.0f && vec3_.y == 0.0f)
    {
        vec = other_x;
    }
    else
    {
        vec = dark_vec_3f_cross(vec3_, other_x);

        if(dark_vec_3f_x(vec) == 0.0f && dark_vec_3f_y(vec) == 0.0f && dark_vec_3f_z(vec) == 0.0f)
        {
            const Dark_Vec_3f other_y = { 0.0f, 1.0f, 0.0f };

            vec = dark_vec_3f_cross(vec3_, other_y);
        }
    }

    return vec;
}

Dark_Vec_3f dark_vec_3f_cross(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    Dark_Vec_3f vec;
    vec.x = a_.y * b_.z - a_.z * b_.y;
    vec.y = a_.z * b_.x - a_.x * b_.z;
    vec.z = a_.x * b_.y - a_.y * b_.x;

    return vec;
}

float dark_vec_3f_dot_f(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    return a_.x * b_.x + a_.y * b_.y + a_.z * b_.z;
}

float dark_vec_3f_angle_f(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    const float dot = dark_vec_3f_dot_f(a_, b_);

    const float len_a = dark_vec_3f_lenght_f(a_);
    const float len_b = dark_vec_3f_lenght_f(b_);

    if(len_a == 0.0f || len_b == 0.0f)
    {
        return 0.0f;
    }

    float cos_theta = dot / (len_a * len_b);
    cos_theta = dark_range_clamp_f(cos_theta, -1.0f, 1.0f);

    return dark_acos_f(cos_theta);
}

float dark_vec_3f_lenght_f(const Dark_Vec_3f vec3_)
{
    return dark_sqrt_f(vec3_.x * vec3_.x + vec3_.y * vec3_.y + vec3_.z * vec3_.z);
}

double dark_vec_3f_dot_d(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    return (double)a_.x * (double)b_.x + (double)a_.y * (double)b_.y + (double)a_.z * (double)b_.z;
}

double dark_vec_3f_angle_d(const Dark_Vec_3f a_, const Dark_Vec_3f b_)
{
    //a_
    //b_

    const double dot = dark_vec_3f_dot_d(a_, b_);

    const double len_a = dark_vec_3f_lenght_d(a_);
    const double len_b = dark_vec_3f_lenght_d(b_);

    if(len_a == 0.0f || len_b == 0.0f)
    {
        return 0.0f;
    }

    double cos_theta = dot / (len_a * len_b);
    cos_theta = dark_range_clamp_d(cos_theta, -1.0f, 1.0f);

    return dark_acos_d(cos_theta);
}

double dark_vec_3f_lenght_d(const Dark_Vec_3f vec3_)
{
    return dark_sqrt_d((double)vec3_.x * (double)vec3_.x + (double)vec3_.y * (double)vec3_.y + (double)vec3_.z * (double)vec3_.z);
}
