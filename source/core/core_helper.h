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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#if !defined(___DARK___CORE_HELPER_H)
#define ___DARK___CORE_HELPER_H

#include <dark/core/error.h>
#include <dark/core/essential.h>
#include <dark/core/library.h>

#include <stdio.h>

void dark_core_enviroment_print(FILE* stream, const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* configuration , const char* module, const char* unit);
void dark_core_error_print(FILE* stream, const Dark_Error* error);

#endif // !defined(___DARK___CORE_HELPER_H)
