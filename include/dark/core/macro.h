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

#if !defined(___DARK___MACRO_H)
#define ___DARK___MACRO_H

#include <dark/core/essential.h>

#if defined(_MSC_VER)
    #define DARK_NORETURN __declspec(noreturn)
#elif defined(__clang__)
    #define DARK_NORETURN _Noreturn
#elif defined(__GNUC__)
    #define DARK_NORETURN __attribute__((noreturn))
#else
    #define DARK_NORETURN
#endif // !defined(_MSC_VER)

static const int64_t DARK_EXIT_SUCCESS = 0;
static const int64_t DARK_EXIT_FAILURE = -1;

#define DARK_MIN(x, y) \
((x) < (y) ? (x) : (y))

#define DARK_MAX(x, y) \
((x) > (y) ? (x) : (y))

#endif // !defined(___DARK___MACRO_H)
