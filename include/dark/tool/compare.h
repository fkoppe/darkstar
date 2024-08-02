/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2024 Felix Koppe <fkoppe@web.de>                             *
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

#if !defined(___DARK___COMPARE_H)
#define ___DARK___COMPARE_H

#include <dark/core/std.h>

typedef int8_t (*Dark_Compare)(const void* element, const void* other);

int8_t dark_compare_u8(const uint8_t* element, const uint8_t* other);
int8_t dark_compare_u16(const uint16_t* element, const uint16_t* other);
int8_t dark_compare_u32(const uint32_t* element, const uint32_t* other);
int8_t dark_compare_u64(const uint64_t* element, const uint64_t* other);
int8_t dark_compare_umax(const uintmax_t* element, const uintmax_t* other);
int8_t dark_compare_zu(const size_t* element, const size_t* other);

int8_t dark_compare_i8(const int8_t* element, const int8_t* other);
int8_t dark_compare_i16(const int16_t* element, const int16_t* other);
int8_t dark_compare_i32(const int32_t* element, const int32_t* other);
int8_t dark_compare_i64(const int64_t* element, const int64_t* other);
int8_t dark_compare_imax(const intmax_t* element, const intmax_t* other);

int8_t dark_compare_f(const float* element, const float* other);
int8_t dark_compare_d(const double* element, const double* other);

#endif // !defined(___DARK___COMPARE_H)
