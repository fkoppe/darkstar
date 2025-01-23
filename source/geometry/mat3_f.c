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

Dark_Mat_3f dark_mat_3f_create(const Dark_Vec_3f col1_, const Dark_Vec_3f col2_, const Dark_Vec_3f col3_)
{
    //col1_
    //col2_
    //col3_

    Dark_Mat_3f mat;
    mat.m[0] = col1_.x;
    mat.m[1] = col1_.y;
    mat.m[2] = col1_.z;

    mat.m[3] = col2_.x;
    mat.m[4] = col2_.y;
    mat.m[5] = col2_.z;

    mat.m[6] = col3_.x;
    mat.m[7] = col3_.y;
    mat.m[8] = col3_.z;

    return mat;
}

Dark_Mat_3f dark_mat_3f_identity(void)
{
    return dark_mat_3f_create((Dark_Vec_3f){1, 0, 0}, (Dark_Vec_3f){0, 1, 0}, (Dark_Vec_3f){0, 0, 1});
}

Dark_Mat_3f dark_mat_3f_zero(void)
{
    return dark_mat_3f_create((Dark_Vec_3f){0, 0, 0}, (Dark_Vec_3f){0, 0, 0}, (Dark_Vec_3f){0, 0, 0});
}

Dark_Vec_3f dark_mat_3f_column(const Dark_Mat_3f mat3_, const uint8_t col_)
{
    //mat3_
    DARK_ASSERT(col_ <= 2, DARK_ERROR_VALUE);

    Dark_Vec_3f column;

    switch(col_)
    {
    case 0:
        column.x = mat3_.m[0];
        column.y = mat3_.m[1];
        column.z = mat3_.m[2];
        break;
    case 1:
        column.x = mat3_.m[3];
        column.y = mat3_.m[4];
        column.z = mat3_.m[5];
        break;
    case 2:
        column.x = mat3_.m[6];
        column.y = mat3_.m[7];
        column.z = mat3_.m[8];
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }

    return column;
}

Dark_Vec_3f dark_mat_3f_row(const Dark_Mat_3f mat3_, const uint8_t row_)
{
    DARK_ASSERT(row_ <= 2, DARK_ERROR_VALUE);

    Dark_Vec_3f row;

    switch(row_)
    {
    case 0:
        row.x = mat3_.m[0];
        row.y = mat3_.m[3];
        row.z = mat3_.m[6];
        break;
    case 1:
        row.x = mat3_.m[1];
        row.y = mat3_.m[4];
        row.z = mat3_.m[7];
        break;
    case 2:
        row.x = mat3_.m[2];
        row.y = mat3_.m[5];
        row.z = mat3_.m[8];
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }

    return row;
}

float dark_mat_3f_get(const Dark_Mat_3f mat3_, const uint8_t col_, const uint8_t row_)
{
    //mat3_
    DARK_ASSERT(col_ <= 2, DARK_ERROR_VALUE);
    DARK_ASSERT(row_ <= 2, DARK_ERROR_VALUE);

    return mat3_.m[col_ * 3 + row_];
}

Dark_Mat_3f dark_mat_3f_set(const Dark_Mat_3f mat3_, const uint8_t col_, const uint8_t row_, const float value_)
{
    //mat3_
    DARK_ASSERT(col_ <= 2, DARK_ERROR_VALUE);
    DARK_ASSERT(row_ <= 2, DARK_ERROR_VALUE);
    //value_

    Dark_Mat_3f mat = mat3_;

    mat.m[col_ * 3 + row_] = value_;

    return mat;
}


Dark_Mat_3f dark_mat_3f_add(const Dark_Mat_3f a_, const Dark_Mat_3f b_)
{
    //a_
    //b_

    Dark_Mat_3f mat;
    mat.m[0] = a_.m[0] + b_.m[0];
    mat.m[1] = a_.m[1] + b_.m[1];
    mat.m[2] = a_.m[2] + b_.m[2];

    mat.m[3] = a_.m[3] + b_.m[3];
    mat.m[4] = a_.m[4] + b_.m[4];
    mat.m[5] = a_.m[5] + b_.m[5];

    mat.m[6] = a_.m[6] + b_.m[6];
    mat.m[7] = a_.m[7] + b_.m[7];
    mat.m[8] = a_.m[8] + b_.m[8];

    return mat;
}

Dark_Mat_3f dark_mat_3f_sub(const Dark_Mat_3f a_, const Dark_Mat_3f b_)
{
    //a_
    //b_

    Dark_Mat_3f mat;
    mat.m[0] = a_.m[0] - b_.m[0];
    mat.m[1] = a_.m[1] - b_.m[1];
    mat.m[2] = a_.m[2] - b_.m[2];

    mat.m[3] = a_.m[3] - b_.m[3];
    mat.m[4] = a_.m[4] - b_.m[4];
    mat.m[5] = a_.m[5] - b_.m[5];

    mat.m[6] = a_.m[6] - b_.m[6];
    mat.m[7] = a_.m[7] - b_.m[7];
    mat.m[8] = a_.m[8] - b_.m[8];

    return mat;
}

Dark_Mat_3f dark_mat_3f_mult(const Dark_Mat_3f mat3_, const float scalar_)
{
    //mat3_
    //scalar_

    Dark_Mat_3f mat;
    mat.m[0] = mat3_.m[0] * scalar_;
    mat.m[1] = mat3_.m[1] * scalar_;
    mat.m[2] = mat3_.m[2] * scalar_;

    mat.m[3] = mat3_.m[3] * scalar_;
    mat.m[4] = mat3_.m[4] * scalar_;
    mat.m[5] = mat3_.m[5] * scalar_;

    mat.m[6] = mat3_.m[6] * scalar_;
    mat.m[7] = mat3_.m[7] * scalar_;
    mat.m[8] = mat3_.m[8] * scalar_;

    return mat;
}

Dark_Vec_3f dark_mat_3f_mult_vec(const Dark_Mat_3f mat3_, const Dark_Vec_3f vec_)
{
    //mat3_
    //vec_

    Dark_Vec_3f mat;
    mat.x = mat3_.m[0] * vec_.x + mat3_.m[1] * vec_.y + mat3_.m[2] * vec_.z;
    mat.y = mat3_.m[3] * vec_.x + mat3_.m[4] * vec_.y + mat3_.m[5] * vec_.z;
    mat.z = mat3_.m[6] * vec_.x + mat3_.m[7] * vec_.y + mat3_.m[8] * vec_.z;

    return mat;
}

Dark_Mat_3f dark_mat_3f_mult_mat(const Dark_Mat_3f a_, const Dark_Mat_3f b_)
{
    //a_
    //b_

    Dark_Mat_3f mat;
    mat.m[0] = a_.m[0] * b_.m[0] + a_.m[1] * b_.m[3] + a_.m[2] * b_.m[6];
    mat.m[1] = a_.m[0] * b_.m[1] + a_.m[1] * b_.m[4] + a_.m[2] * b_.m[7];
    mat.m[2] = a_.m[0] * b_.m[2] + a_.m[1] * b_.m[5] + a_.m[2] * b_.m[8];

    mat.m[3] = a_.m[3] * b_.m[0] + a_.m[4] * b_.m[3] + a_.m[5] * b_.m[6];
    mat.m[4] = a_.m[3] * b_.m[1] + a_.m[4] * b_.m[4] + a_.m[5] * b_.m[7];
    mat.m[5] = a_.m[3] * b_.m[2] + a_.m[4] * b_.m[5] + a_.m[5] * b_.m[8];

    mat.m[6] = a_.m[6] * b_.m[0] + a_.m[7] * b_.m[3] + a_.m[8] * b_.m[6];
    mat.m[7] = a_.m[6] * b_.m[1] + a_.m[7] * b_.m[4] + a_.m[8] * b_.m[7];
    mat.m[8] = a_.m[6] * b_.m[2] + a_.m[7] * b_.m[5] + a_.m[8] * b_.m[8];

    return mat;
}

Dark_Mat_3f dark_mat_3f_div(const Dark_Mat_3f mat3_, const float scalar_)
{
    //mat3_
    //scalar_

    Dark_Mat_3f mat;
    mat.m[0] = mat3_.m[0] / scalar_;
    mat.m[1] = mat3_.m[1] / scalar_;
    mat.m[2] = mat3_.m[2] / scalar_;

    mat.m[3] = mat3_.m[3] / scalar_;
    mat.m[4] = mat3_.m[4] / scalar_;
    mat.m[5] = mat3_.m[5] / scalar_;

    mat.m[6] = mat3_.m[6] / scalar_;
    mat.m[7] = mat3_.m[7] / scalar_;
    mat.m[8] = mat3_.m[8] / scalar_;

    return mat;
}

float dark_mat_3f_determinant(const Dark_Mat_3f mat3_)
{
    //mat3_

    const float a = mat3_.m[0];
    const float b = mat3_.m[1];
    const float c = mat3_.m[2];
    const float d = mat3_.m[3];
    const float e = mat3_.m[4];
    const float f = mat3_.m[5];
    const float g = mat3_.m[6];
    const float h = mat3_.m[7];
    const float i = mat3_.m[8];

    const float det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    return det;
}

bool dark_mat_3f_invert_is(const Dark_Mat_3f mat3_)
{
    //mat3_

    const float det = dark_mat_3f_determinant(mat3_);

    if(dark_abs_f(det) > DARK_EPSILON_F)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Dark_Mat_3f dark_mat_3f_invert(const Dark_Mat_3f mat3_)
{
    //mat3_

    const float a = mat3_.m[0];
    const float b = mat3_.m[1];
    const float c = mat3_.m[2];
    const float d = mat3_.m[3];
    const float e = mat3_.m[4];
    const float f = mat3_.m[5];
    const float g = mat3_.m[6];
    const float h = mat3_.m[7];
    const float i = mat3_.m[8];

    DARK_ASSERT(dark_mat_3f_invert_is(mat3_), DARK_ERROR_MATH);

    const float det = dark_mat_3f_determinant(mat3_);
    const float inverse_det = 1.0f / det;

    Dark_Mat_3f inverse;
    inverse.m[0] = (e * i - f * h) * inverse_det;
    inverse.m[1] = (c * h - b * i) * inverse_det;
    inverse.m[2] = (b * f - c * e) * inverse_det;

    inverse.m[3] = (f * g - d * i) * inverse_det;
    inverse.m[4] = (a * i - c * g) * inverse_det;
    inverse.m[5] = (c * d - a * f) * inverse_det;

    inverse.m[6] = (d * h - e * g) * inverse_det;
    inverse.m[7] = (b * g - a * h) * inverse_det;
    inverse.m[8] = (a * e - b * d) * inverse_det;

    return inverse;
}

Dark_Mat_3f dark_mat_3f_transpose(const Dark_Mat_3f mat3_)
{
    //mat3_

    Dark_Mat_3f mat;
    mat.m[0] = mat3_.m[0];
    mat.m[1] = mat3_.m[3];
    mat.m[2] = mat3_.m[6];

    mat.m[3] = mat3_.m[1];
    mat.m[4] = mat3_.m[4];
    mat.m[5] = mat3_.m[7];

    mat.m[6] = mat3_.m[2];
    mat.m[7] = mat3_.m[5];
    mat.m[8] = mat3_.m[8];

    return mat;
}

Dark_Mat_3f dark_mat_3f_orthonormalize(const Dark_Mat_3f mat3_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_adjoint(const Dark_Mat_3f mat3_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_rotate_x(const float angle_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_rotate_y(const float angle_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_rotate_z(const float angle_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_scale(const float scale_x_, const float scale_y_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_translate(const float translation_x_, const float translation_y_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_from_axis_angle(const Dark_Vec_3f axis_, const float angle_)
{
    DARK_UNIMPLEMENTED; //TODO
}

Dark_Mat_3f dark_mat_3f_rotation_between(const Dark_Vec_3f from_, const Dark_Vec_3f to_)
{
    DARK_UNIMPLEMENTED; //TODO
}

int8_t dark_mat_3f_compare(const Dark_Mat_3f* const element_, const Dark_Mat_3f* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    for(size_t i = 0; i < 9; i++)
    {
        const size_t result = dark_compare_f(element_->m + i, other_->m + i);

        if(0 != result)
        {
            return result;
        }
    }

    return 0;
}
