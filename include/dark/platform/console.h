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

#include <dark/core/essential.h>

static const char* const DARK_CONSOLE_COLOR_FG_RED = "\033[31m";
static const char* const DARK_CONSOLE_COLOR_FG_GREEN = "\033[32m";
static const char* const DARK_CONSOLE_COLOR_FG_YELLOW = "\033[33m";
static const char* const DARK_CONSOLE_COLOR_FG_BLUE = "\033[34m";
static const char* const DARK_CONSOLE_COLOR_FG_PURPLE = "\033[35m";
static const char* const DARK_CONSOLE_COLOR_FG_CYAN = "\033[36m";

static const char* const DARK_CONSOLE_COLOR_BG_RED = "\033[41m";
static const char* const DARK_CONSOLE_COLOR_BG_GREEN = "\033[42m";
static const char* const DARK_CONSOLE_COLOR_BG_YELLOW = "\033[43m";
static const char* const DARK_CONSOLE_COLOR_BG_BLUE = "\033[44m";
static const char* const DARK_CONSOLE_COLOR_BG_PURPLE = "\033[45m";
static const char* const DARK_CONSOLE_COLOR_BG_CYAN = "\033[46m";

static const char* const DARK_CONSOLE_COLOR_EFG_ORANGE = "\033[38;5;202m";
static const char* const DARK_CONSOLE_COLOR_EFG_LIGHT_GREEN = "\033[38;5;154m";
static const char* const DARK_CONSOLE_COLOR_EFG_LIGHT_BLUE = "\033[38;5;159m";

static const char* const DARK_CONSOLE_COLOR_RESET = "\033[0m";

void dark_console_hide(void);
void dark_console_show(void);

#endif // !defined(___DARK___CONSOLE_H)
