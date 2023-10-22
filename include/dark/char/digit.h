/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

#include <dark/core/essential.h>

#define DARK_DIGIT_COUNT_INT32_MAX 10
#define DARK_DIGIT_COUNT_INT64_MAX 19
#define DARK_DIGIT_COUNT_UINT32_MAX 10
#define DARK_DIGIT_COUNT_UINT64_MAX 20

uint8_t dark_digit_get(int32_t integer, size_t position);
char dark_digit_to_char(uint8_t digit);

size_t dark_digit_count_int32(int32_t integer);

void dark_digit_int32_to_char_arr(int32_t integer, size_t count, char* destination);
void dark_digit_int32_to_char_arr_terminated(int32_t integer, size_t count, char* destination);

#endif // !defined(___DARK___DIGIT_H)
