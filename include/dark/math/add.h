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

#if !defined(___DARK___ADD_H)
#define ___DARK___ADD_H

#include <dark/core/essential.h>

uint8_t dark_add_u8(uintmax_t u, intmax_t i);
uint16_t dark_add_u16(uintmax_t u, intmax_t i);
uint32_t dark_add_u32(uintmax_t u, intmax_t i);
uint64_t dark_add_u64(uintmax_t u, intmax_t i);
uintmax_t dark_add_umax(uintmax_t u, intmax_t i);

uint8_t dark_uadd_u8(uintmax_t a, uintmax_t b);
uint16_t dark_uadd_u16(uintmax_t a, uintmax_t b);
uint32_t dark_uadd_u32(uintmax_t a, uintmax_t b);
uint64_t dark_uadd_u64(uintmax_t a, uintmax_t b);
uintmax_t dark_uadd_umax(uintmax_t a, uintmax_t b);

uint8_t dark_iadd_u8(intmax_t a, intmax_t b);
uint16_t dark_iadd_u16(intmax_t a, intmax_t b);
uint32_t dark_iadd_u32(intmax_t a, intmax_t b);
uint64_t dark_iadd_u64(intmax_t a, intmax_t b);
uintmax_t dark_iadd_umax(intmax_t a, intmax_t b);

int8_t dark_add_i8(uintmax_t u, intmax_t i);
int16_t dark_add_i16(uintmax_t u, intmax_t i);
int32_t dark_add_i32(uintmax_t u, intmax_t i);
int64_t dark_add_i64(uintmax_t u, intmax_t i);
intmax_t dark_add_imax(uintmax_t u, intmax_t i);

int8_t dark_uadd_i8(uintmax_t a, uintmax_t b);
int16_t dark_uadd_i16(uintmax_t a, uintmax_t b);
int32_t dark_uadd_i32(uintmax_t a, uintmax_t b);
int64_t dark_uadd_i64(uintmax_t a, uintmax_t b);
intmax_t dark_uadd_imax(uintmax_t a, uintmax_t b);

int8_t dark_iadd_i8(intmax_t a, intmax_t b);
int16_t dark_iadd_i16(intmax_t a, intmax_t b);
int32_t dark_iadd_i32(intmax_t a, intmax_t b);
int64_t dark_iadd_i64(intmax_t a, intmax_t b);
intmax_t dark_iadd_imax(intmax_t a, intmax_t b);

#endif // !defined(___DARK___ADD_H)
