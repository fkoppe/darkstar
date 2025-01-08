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

#if !defined(___DARK___CONSOLE_H)
#define ___DARK___CONSOLE_H

#include <dark/core/std.h>

#if !defined(___DARK_CONSOLE_NOCOLOR)
#define DARK_CONSOLE_COLOR_FG_RED "\033[31m"
#define DARK_CONSOLE_COLOR_FG_GREEN "\033[32m"
#define DARK_CONSOLE_COLOR_FG_YELLOW "\033[33m"
#define DARK_CONSOLE_COLOR_FG_BLUE "\033[34m"
#define DARK_CONSOLE_COLOR_FG_MAGENTA "\033[35m"
#define DARK_CONSOLE_COLOR_FG_CYAN "\033[36m"

#define DARK_CONSOLE_COLOR_BFG_RED "\033[91m"
#define DARK_CONSOLE_COLOR_BFG_GREEN "\033[92m"
#define DARK_CONSOLE_COLOR_BFG_YELLOW "\033[93m"
#define DARK_CONSOLE_COLOR_BFG_BLUE "\033[94m"
#define DARK_CONSOLE_COLOR_BFG_MAGENTA "\033[95m"
#define DARK_CONSOLE_COLOR_BFG_CYAN "\033[96m"

#define DARK_CONSOLE_COLOR_BG_RED "\033[41m"
#define DARK_CONSOLE_COLOR_BG_GREEN "\033[42m"
#define DARK_CONSOLE_COLOR_BG_YELLOW "\033[43m"
#define DARK_CONSOLE_COLOR_BG_BLUE "\033[44m"
#define DARK_CONSOLE_COLOR_BG_MAGENTA "\033[45m"
#define DARK_CONSOLE_COLOR_BG_CYAN "\033[46m"

#define DARK_CONSOLE_COLOR_BBG_RED "\033[101m"
#define DARK_CONSOLE_COLOR_BBG_GREEN "\033[102m"
#define DARK_CONSOLE_COLOR_BBG_YELLOW "\033[103m"
#define DARK_CONSOLE_COLOR_BBG_BLUE "\033[104m"
#define DARK_CONSOLE_COLOR_BBG_MAGENTA "\033[105m"
#define DARK_CONSOLE_COLOR_BBG_CYAN "\033[106m"

#define DARK_CONSOLE_COLOR_EFG_RED "\033[38;5;160m"
#define DARK_CONSOLE_COLOR_EFG_ORANGE "\033[38;5;202m"
#define DARK_CONSOLE_COLOR_EFG_GREEN "\033[38;5;154m"
#define DARK_CONSOLE_COLOR_EFG_BLUE "\033[38;5;159m"

#define DARK_CONSOLE_COLOR_EBG_RED "\033[48;5;160m"
#define DARK_CONSOLE_COLOR_EBG_ORANGE "\033[48;5;202m"
#define DARK_CONSOLE_COLOR_EBG_GREEN "\033[48;5;154m"
#define DARK_CONSOLE_COLOR_EBG_BLUE "\033[48;5;159m"

#define DARK_CONSOLE_COLOR_RESET "\033[0m"
#else
#define DARK_CONSOLE_COLOR_FG_RED ""
#define DARK_CONSOLE_COLOR_FG_GREEN ""
#define DARK_CONSOLE_COLOR_FG_YELLOW ""
#define DARK_CONSOLE_COLOR_FG_BLUE ""
#define DARK_CONSOLE_COLOR_FG_MAGENTA ""
#define DARK_CONSOLE_COLOR_FG_CYAN ""

#define DARK_CONSOLE_COLOR_BFG_RED ""
#define DARK_CONSOLE_COLOR_BFG_GREEN ""
#define DARK_CONSOLE_COLOR_BFG_YELLOW ""
#define DARK_CONSOLE_COLOR_BFG_BLUE ""
#define DARK_CONSOLE_COLOR_BFG_MAGENTA ""
#define DARK_CONSOLE_COLOR_BFG_CYAN ""

#define DARK_CONSOLE_COLOR_BG_RED ""
#define DARK_CONSOLE_COLOR_BG_GREEN ""
#define DARK_CONSOLE_COLOR_BG_YELLOW ""
#define DARK_CONSOLE_COLOR_BG_BLUE ""
#define DARK_CONSOLE_COLOR_BG_MAGENTA ""
#define DARK_CONSOLE_COLOR_BG_CYAN ""

#define DARK_CONSOLE_COLOR_BBG_RED ""
#define DARK_CONSOLE_COLOR_BBG_GREEN ""
#define DARK_CONSOLE_COLOR_BBG_YELLOW ""
#define DARK_CONSOLE_COLOR_BBG_BLUE ""
#define DARK_CONSOLE_COLOR_BBG_MAGENTA ""
#define DARK_CONSOLE_COLOR_BBG_CYAN ""

#define DARK_CONSOLE_COLOR_EFG_RED ""
#define DARK_CONSOLE_COLOR_EFG_ORANGE ""
#define DARK_CONSOLE_COLOR_EFG_GREEN ""
#define DARK_CONSOLE_COLOR_EFG_BLUE ""

#define DARK_CONSOLE_COLOR_EBG_RED ""
#define DARK_CONSOLE_COLOR_EBG_ORANGE ""
#define DARK_CONSOLE_COLOR_EBG_GREEN ""
#define DARK_CONSOLE_COLOR_EBG_BLUE ""

#define DARK_CONSOLE_COLOR_RESET ""
#endif // !defined(___DARK_CONSOLE_NOCOLOR)

void dark_console_hide(void);
void dark_console_show(void);

void dark_console_clear(void);

#endif // !defined(___DARK___CONSOLE_H)
