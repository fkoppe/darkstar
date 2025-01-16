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

#if !defined(___DARK___MULT_H)
#define ___DARK___MULT_H

#include <dark/core/std.h>

uint8_t dark_mult_u8(uintmax_t a, intmax_t b);
uint16_t dark_mult_u16(uintmax_t a, intmax_t b);
uint32_t dark_mult_u32(uintmax_t a, intmax_t b);
uint64_t dark_mult_u64(uintmax_t a, intmax_t b);
uintmax_t dark_mult_umax(uintmax_t a, intmax_t b);
size_t dark_mult_zu(uintmax_t a, intmax_t b);

uint8_t dark_umult_u8(uintmax_t a, uintmax_t b);
uint16_t dark_umult_u16(uintmax_t a, uintmax_t b);
uint32_t dark_umult_u32(uintmax_t a, uintmax_t b);
uint64_t dark_umult_u64(uintmax_t a, uintmax_t b);
uintmax_t dark_umult_umax(uintmax_t a, uintmax_t b);
size_t dark_umult_zu(uintmax_t a, uintmax_t b);

uint8_t dark_imult_u8(intmax_t a, intmax_t b);
uint16_t dark_imult_u16(intmax_t a, intmax_t b);
uint32_t dark_imult_u32(intmax_t a, intmax_t b);
uint64_t dark_imult_u64(intmax_t a, intmax_t b);
uintmax_t dark_imult_umax(intmax_t a, intmax_t b);
size_t dark_imult_zu(intmax_t a, intmax_t b);

int8_t dark_mult_i8(uintmax_t a, intmax_t b);
int16_t dark_mult_i16(uintmax_t a, intmax_t b);
int32_t dark_mult_i32(uintmax_t a, intmax_t b);
int64_t dark_mult_i64(uintmax_t a, intmax_t b);
intmax_t dark_mult_imax(uintmax_t a, intmax_t b);

int8_t dark_umult_i8(uintmax_t a, uintmax_t b);
int16_t dark_umult_i16(uintmax_t a, uintmax_t b);
int32_t dark_umult_i32(uintmax_t a, uintmax_t b);
int64_t dark_umult_i64(uintmax_t a, uintmax_t b);
intmax_t dark_umult_imax(uintmax_t a, uintmax_t b);

int8_t dark_imult_i8(intmax_t a, intmax_t b);
int16_t dark_imult_i16(intmax_t a, intmax_t b);
int32_t dark_imult_i32(intmax_t a, intmax_t b);
int64_t dark_imult_i64(intmax_t a, intmax_t b);
intmax_t dark_imult_imax(intmax_t a, intmax_t b);

#endif // !defined(___DARK___MULT_H)
