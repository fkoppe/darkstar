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

#if !defined(___DARK___DEBUG_PRINT_H)
#define ___DARK___DEBUG_PRINT_H

#include <dark/core/essential.h>

#if defined(___DARK_DEBUG)
#define DARK_DEBUG_PRINT(message) dark_debug_print_stdout(message)
#define DARK_DEBUG_PRINTF(format, ...) dark_debug_printf_stdout((format), __VA_ARGS__);
#endif // defined(___DARK_DEBUG)

void dark_debug_print_stdout(const char* message);
void dark_debug_printf_stdout(const char* format, ...);

#endif // !defined(___DARK___DEBUG_PRINT_H)
