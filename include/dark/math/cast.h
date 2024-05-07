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

#if !defined(___DARK___CAST_H)
#define ___DARK___CAST_H

#include <dark/core/essential.h>

uint8_t dark_ucast_u8(uint64_t u);
uint16_t dark_ucast_u16(uint64_t u);
uint32_t dark_ucast_u32(uint64_t u);
uint64_t dark_ucast_u64(uint64_t u);

int8_t dark_ucast_i8(uint64_t u);
int16_t dark_ucast_i16(uint64_t u);
int32_t dark_ucast_i32(uint64_t u);
int64_t dark_ucast_i64(uint64_t u);

uint8_t dark_icast_u8(int64_t i);
uint16_t dark_icast_u16(int64_t i);
uint32_t dark_icast_u32(int64_t i);
uint64_t dark_icast_u64(int64_t i);

int8_t dark_icast_i8(int64_t i);
int16_t dark_icast_i16(int64_t i);
int32_t dark_icast_i32(int64_t i);
int64_t dark_icast_i64(int64_t i);

#endif // !defined(___DARK___CAST_H)
