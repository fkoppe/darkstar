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

#if !defined(___DARK___MAT_3F_H)
#define ___DARK___MAT_3F_H

#include <dark/core/std.h>
#include <dark/geometry/vec_3f.h>

typedef struct Dark_Mat_3f Dark_Mat_3f;
struct Dark_Mat_3f
{
    float m[9];
};

Dark_Mat_3f dark_mat_3f_create(Dark_Vec_3f col1, Dark_Vec_3f col2, Dark_Vec_3f col3);
Dark_Mat_3f dark_mat_3f_identity(void);
Dark_Mat_3f dark_mat_3f_zero(void);

Dark_Vec_3f dark_mat_3f_column(Dark_Mat_3f mat3, uint8_t col);
Dark_Vec_3f dark_mat_3f_row(Dark_Mat_3f mat3, uint8_t row);
float dark_mat_3f_get(Dark_Mat_3f mat3, uint8_t col, uint8_t row);
Dark_Mat_3f dark_mat_3f_set(Dark_Mat_3f mat3, uint8_t col, uint8_t row, float value);

Dark_Mat_3f dark_mat_3f_add(Dark_Mat_3f a, Dark_Mat_3f b);
Dark_Mat_3f dark_mat_3f_sub(Dark_Mat_3f a, Dark_Mat_3f b);
Dark_Mat_3f dark_mat_3f_mult(Dark_Mat_3f mat3, float scalar);
Dark_Vec_3f dark_mat_3f_mult_vec(Dark_Mat_3f mat3, Dark_Vec_3f vec);
Dark_Mat_3f dark_mat_3f_mult_mat(Dark_Mat_3f a, Dark_Mat_3f b);
Dark_Mat_3f dark_mat_3f_div(Dark_Mat_3f mat3, float scalar);

float dark_mat_3f_determinant(Dark_Mat_3f mat3);
bool dark_mat_3f_invert_is(Dark_Mat_3f mat3);
Dark_Mat_3f dark_mat_3f_invert(Dark_Mat_3f mat3);

Dark_Mat_3f dark_mat_3f_transpose(Dark_Mat_3f mat3);

Dark_Mat_3f dark_mat_3f_orthonormalize(Dark_Mat_3f mat3);
Dark_Mat_3f dark_mat_3f_adjoint(Dark_Mat_3f mat3);

Dark_Mat_3f dark_mat_3f_rotate_x(float angle);
Dark_Mat_3f dark_mat_3f_rotate_y(float angle);
Dark_Mat_3f dark_mat_3f_rotate_z(float angle);

Dark_Mat_3f dark_mat_3f_scale(float scale_x, float scale_y);
Dark_Mat_3f dark_mat_3f_translate(float translation_x, float translation_y);

Dark_Mat_3f dark_mat_3f_from_axis_angle(Dark_Vec_3f axis, float angle);
Dark_Mat_3f dark_mat_3f_rotation_between(Dark_Vec_3f from, Dark_Vec_3f to);

int8_t dark_mat_3f_compare(const Dark_Mat_3f* element, const Dark_Mat_3f* other);

#endif // !defined(___DARK___MAT_3F_H)
