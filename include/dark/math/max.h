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

#if !defined(___DARK___MAX_H)
#define ___DARK___MAX_H

#include <dark/core/std.h>

uint8_t dark_max_u8(uint8_t a, uint8_t b);
uint16_t dark_max_u16(uint16_t a, uint16_t b);
uint32_t dark_max_u32(uint32_t a, uint32_t b);
uint64_t dark_max_u64(uint64_t a, uint64_t b);
uintmax_t dark_max_umax(uintmax_t a, uintmax_t b);
size_t dark_max_zu(size_t a, size_t b);

int8_t dark_max_i8(int8_t a, int8_t b);
int16_t dark_max_i16(int16_t a, int16_t b);
int32_t dark_max_i32(int32_t a, int32_t b);
int64_t dark_max_i64(int64_t a, int64_t b);
intmax_t dark_max_imax(intmax_t a, intmax_t b);

#endif // !defined(___DARK___MAX_H)
