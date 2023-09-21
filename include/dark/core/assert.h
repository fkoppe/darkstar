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

#if !defined(___DARK___ASSERT_H)
#define ___DARK___ASSERT_H

#include <dark/core/error.h>
#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>

#if defined(___DARK_DEBUG)
#define DARK_ASSERT(condition, error) if(!(condition)) dark_assert(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (#condition), &(error), NULL)
#define DARK_ASSERT_MSG(condition, error, message) if(!(condition)) dark_assert(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (#condition), &(error), (message))
#else
#define DARK_ASSERT(condition, error)
#define DARK_ASSERT_MSG(condition, error, message)
#endif // defined(___DARK_DEBUG)

void dark_assert(const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit, const char* condition, const Dark_Error* error, const char* message);

#endif // !defined(___DARK___ASSERT_H)
