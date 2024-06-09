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

#if !defined(___DARK___SO_H)
#define ___DARK___SO_H

#include <dark/core/std.h>

#define DARK_PRINTF_MAX 512

#if defined(___DARK_DEBUG)
#define DARK_PRINT_DEBUG(data) dark_print(DARK_SO_OUT, (data))
#define DARK_PRINTF_DEBUG(format, ...) dark_printf(DARK_SO_OUT, (format), __VA_ARGS__)
#endif // defined(___DARK_DEBUG)

typedef enum Dark_So Dark_So;
enum Dark_So
{
    ___DARK_SO_MIN,
    DARK_SO_OUT,
    DARK_SO_ERR,
    ___DARK_SO_MAX,
};

void dark_print(Dark_So so, const char* cstring);
void dark_printf(Dark_So so, const char* format, ...);
void dark_flush(Dark_So so);

#endif // !defined(___DARK___SO_H)
