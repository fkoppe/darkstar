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

#if !defined(___DARK___CAST_H)
#define ___DARK___CAST_H

#include <dark/core/std.h>

uint8_t dark_ucast_u8(uintmax_t u);
uint16_t dark_ucast_u16(uintmax_t u);
uint32_t dark_ucast_u32(uintmax_t u);
uint64_t dark_ucast_u64(uintmax_t u);
size_t dark_ucast_zu(uintmax_t u);

int8_t dark_ucast_i8(uintmax_t u);
int16_t dark_ucast_i16(uintmax_t u);
int32_t dark_ucast_i32(uintmax_t u);
int64_t dark_ucast_i64(uintmax_t u);
intmax_t dark_ucast_imax(uintmax_t u);

uint8_t dark_icast_u8(intmax_t i);
uint16_t dark_icast_u16(intmax_t i);
uint32_t dark_icast_u32(intmax_t i);
uint64_t dark_icast_u64(intmax_t i);
size_t dark_icast_zu(intmax_t i);

int8_t dark_icast_i8(intmax_t i);
int16_t dark_icast_i16(intmax_t i);
int32_t dark_icast_i32(intmax_t i);
int64_t dark_icast_i64(intmax_t i);

#endif // !defined(___DARK___CAST_H)
