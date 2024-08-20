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

#if !defined(___DARK___CONSOLE_H)
#define ___DARK___CONSOLE_H

#include <dark/core/std.h>

#if !defined(___DARK_CONSOLE_NOCOLOR)
static const char* const DARK_CONSOLE_COLOR_FG_RED = "\033[31m";
static const char* const DARK_CONSOLE_COLOR_FG_GREEN = "\033[32m";
static const char* const DARK_CONSOLE_COLOR_FG_YELLOW = "\033[33m";
static const char* const DARK_CONSOLE_COLOR_FG_BLUE = "\033[34m";
static const char* const DARK_CONSOLE_COLOR_FG_MAGENTA = "\033[35m";
static const char* const DARK_CONSOLE_COLOR_FG_CYAN = "\033[36m";

static const char* const DARK_CONSOLE_COLOR_BFG_RED = "\033[91m";
static const char* const DARK_CONSOLE_COLOR_BFG_GREEN = "\033[92m";
static const char* const DARK_CONSOLE_COLOR_BFG_YELLOW = "\033[93m";
static const char* const DARK_CONSOLE_COLOR_BFG_BLUE = "\033[94m";
static const char* const DARK_CONSOLE_COLOR_BFG_MAGENTA = "\033[95m";
static const char* const DARK_CONSOLE_COLOR_BFG_CYAN = "\033[96m";

static const char* const DARK_CONSOLE_COLOR_BG_RED = "\033[41m";
static const char* const DARK_CONSOLE_COLOR_BG_GREEN = "\033[42m";
static const char* const DARK_CONSOLE_COLOR_BG_YELLOW = "\033[43m";
static const char* const DARK_CONSOLE_COLOR_BG_BLUE = "\033[44m";
static const char* const DARK_CONSOLE_COLOR_BG_MAGENTA = "\033[45m";
static const char* const DARK_CONSOLE_COLOR_BG_CYAN = "\033[46m";

static const char* const DARK_CONSOLE_COLOR_BBG_RED = "\033[101m";
static const char* const DARK_CONSOLE_COLOR_BBG_GREEN = "\033[102m";
static const char* const DARK_CONSOLE_COLOR_BBG_YELLOW = "\033[103m";
static const char* const DARK_CONSOLE_COLOR_BBG_BLUE = "\033[104m";
static const char* const DARK_CONSOLE_COLOR_BBG_MAGENTA = "\033[105m";
static const char* const DARK_CONSOLE_COLOR_BBG_CYAN = "\033[106m";

static const char* const DARK_CONSOLE_COLOR_EFG_RED = "\033[38;5;160m";
static const char* const DARK_CONSOLE_COLOR_EFG_ORANGE = "\033[38;5;202m";
static const char* const DARK_CONSOLE_COLOR_EFG_GREEN = "\033[38;5;154m";
static const char* const DARK_CONSOLE_COLOR_EFG_BLUE = "\033[38;5;159m";

static const char* const DARK_CONSOLE_COLOR_EBG_RED = "\033[48;5;160m";
static const char* const DARK_CONSOLE_COLOR_EBG_ORANGE = "\033[48;5;202m";
static const char* const DARK_CONSOLE_COLOR_EBG_GREEN = "\033[48;5;154m";
static const char* const DARK_CONSOLE_COLOR_EBG_BLUE = "\033[48;5;159m";

static const char* const DARK_CONSOLE_COLOR_RESET = "\033[0m";
#else
static const char* const DARK_CONSOLE_COLOR_FG_RED = "";
static const char* const DARK_CONSOLE_COLOR_FG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_FG_YELLOW = "";
static const char* const DARK_CONSOLE_COLOR_FG_BLUE = "";
static const char* const DARK_CONSOLE_COLOR_FG_MAGENTA = "";
static const char* const DARK_CONSOLE_COLOR_FG_CYAN = "";

static const char* const DARK_CONSOLE_COLOR_BFG_RED = "";
static const char* const DARK_CONSOLE_COLOR_BFG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_BFG_YELLOW = "";
static const char* const DARK_CONSOLE_COLOR_BFG_BLUE = "";
static const char* const DARK_CONSOLE_COLOR_BFG_MAGENTA = "";
static const char* const DARK_CONSOLE_COLOR_BFG_CYAN = "";

static const char* const DARK_CONSOLE_COLOR_BG_RED = "";
static const char* const DARK_CONSOLE_COLOR_BG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_BG_YELLOW = "";
static const char* const DARK_CONSOLE_COLOR_BG_BLUE = "";
static const char* const DARK_CONSOLE_COLOR_BG_MAGENTA = "";
static const char* const DARK_CONSOLE_COLOR_BG_CYAN = "";

static const char* const DARK_CONSOLE_COLOR_BBG_RED = "";
static const char* const DARK_CONSOLE_COLOR_BBG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_BBG_YELLOW = "";
static const char* const DARK_CONSOLE_COLOR_BBG_BLUE = "";
static const char* const DARK_CONSOLE_COLOR_BBG_MAGENTA = "";
static const char* const DARK_CONSOLE_COLOR_BBG_CYAN = "";

static const char* const DARK_CONSOLE_COLOR_EFG_RED = "";
static const char* const DARK_CONSOLE_COLOR_EFG_ORANGE = "";
static const char* const DARK_CONSOLE_COLOR_EFG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_EFG_BLUE = "";

static const char* const DARK_CONSOLE_COLOR_EBG_RED = "";
static const char* const DARK_CONSOLE_COLOR_EBG_ORANGE = "";
static const char* const DARK_CONSOLE_COLOR_EBG_GREEN = "";
static const char* const DARK_CONSOLE_COLOR_EBG_BLUE = "";

static const char* const DARK_CONSOLE_COLOR_RESET = "";
#endif // !defined(___DARK_CONSOLE_NOCOLOR)

void dark_console_hide(void);
void dark_console_show(void);

void dark_console_clear(void);

#endif // !defined(___DARK___CONSOLE_H)
