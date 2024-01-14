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

#if !defined(___DARK___TERMINATE_H)
#define ___DARK___TERMINATE_H

#include <dark/core/error.h>
#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>

#if defined(___DARK_DEBINFO)
#define DARK_EXIT(code) dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), &DARK_ERROR_UNDEFINED, false, NULL)
#define DARK_EXIT_ERROR(code, error) dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), &(error), false, NULL)
#define DARK_EXIT_MSG(code, error, message) dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), &(error), false, message)
#define DARK_ABORT dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, &DARK_ERROR_UNDEFINED, true, NULL)
#define DARK_ABORT_ERROR(error) dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, &(error), true, NULL)
#define DARK_ABORT_MSG(error, message) dark_terminate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, &(error), true, message)
#else
#define DARK_EXIT(code) exit(code)
#define DARK_EXIT_ERROR(code, error) exit(code)
#define DARK_EXIT_MSG(code, error, message) exit(code)
#define DARK_ABORT abort()
#define DARK_ABORT_ERROR(error) abort()
#define DARK_ABORT_MSG(error, message) abort()
#endif // defined(___DARK_DEBINFO)

void dark_terminate(const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit, int64_t code, const Dark_Error* error, bool abort_is, const char* message);

#endif // !defined(___DARK___TERMINATE_H)
