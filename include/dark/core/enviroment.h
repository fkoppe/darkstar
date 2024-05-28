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

#if !defined(___DARK___ENVIROMENT_H)
#define ___DARK___ENVIROMENT_H

#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>

#include <stdio.h>

void dark_core_enviroment_print_stderr(const char* file, const char* func, intmax_t line, const char* date, const char* time, const Dark_Library* library, const char* configuration, const char* module, const char* unit);

#endif // !defined(___DARK___ENVIROMENT_H)
