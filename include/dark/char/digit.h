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

#if !defined(___DARK___DIGIT_H)
#define ___DARK___DIGIT_H

#include <dark/char/cbuffer.h>
#include <dark/core/message.h>
#include <dark/core/std.h>

#define DARK_DIGIT_COUNT_MAX_I8 3
#define DARK_DIGIT_COUNT_MAX_I16 5
#define DARK_DIGIT_COUNT_MAX_I32 10
#define DARK_DIGIT_COUNT_MAX_I64 19
#define DARK_DIGIT_COUNT_MAX_U8 3
#define DARK_DIGIT_COUNT_MAX_U16 5
#define DARK_DIGIT_COUNT_MAX_U32 10
#define DARK_DIGIT_COUNT_MAX_U64 20

static const Dark_Message DARK_MESSAGE_DIGIT_LEADING_ZERO = { NULL, "leading zero at position", NULL };

uint8_t dark_digit_get_u(uintmax_t number, size_t position);
uint8_t dark_digit_get_i(intmax_t number, size_t position);

char dark_digit_to_char(uint8_t digit);

size_t dark_digit_count_u8(uint8_t number);
size_t dark_digit_count_u16(uint16_t number);
size_t dark_digit_count_u32(uint32_t number);
size_t dark_digit_count_u64(uint64_t number);
size_t dark_digit_count_umax(uintmax_t number);
size_t dark_digit_count_zu(size_t number);

size_t dark_digit_count_i8(int8_t number);
size_t dark_digit_count_i16(int16_t number);
size_t dark_digit_count_i32(int32_t number);
size_t dark_digit_count_i64(int64_t number);
size_t dark_digit_count_imax(intmax_t number);

void dark_digit_write_u(uintmax_t number, size_t digit_count, Dark_Cbuffer destination);
void dark_digit_write_u_terminated(uintmax_t number, size_t digit_count, Dark_Cbuffer destination);

void dark_digit_write_i(intmax_t number, size_t digit_count, Dark_Cbuffer destination);
void dark_digit_write_i_terminated(intmax_t number, size_t digit_count, Dark_Cbuffer destination);

#endif // !defined(___DARK___DIGIT_H)
