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

#if !defined(___DARK___SPRINT_H)
#define ___DARK___SPRINT_H

#include <dark/core/std.h>

#include <stdarg.h>

size_t dark_snprintf_notterminated(size_t count, char* destination, const char* format, ...);
size_t dark_snprintf_terminated(size_t count, char* destination, const char* format, ...);

size_t dark_vsnprintf_notterminated(size_t count, char* destination, const char* format, va_list arguments);
size_t dark_vsnprintf_terminated(size_t count, char* destination, const char* format, va_list arguments);

#endif // !defined(___DARK___SPRINT_H)
