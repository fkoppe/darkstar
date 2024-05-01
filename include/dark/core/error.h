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

#if !defined(___DARK___ERROR_H)
#define ___DARK___ERROR_H

#include <dark/core/essential.h>

#if !defined(DARK_ERROR_LAYERS_MAX)
#define DARK_ERROR_LAYERS_MAX 3
#endif // !defined(DARK_ERROR_LAYERS_MAX)

typedef struct Dark_Error
{
    const void* parent_error;
    const char* type;
    const char* info;
} Dark_Error;

static const Dark_Error DARK_ERROR_UNDEFINED = { NULL, "undefined", NULL};

static const Dark_Error DARK_ERROR_UNKNOWN = { NULL, "unknown", NULL };

//unreachable error
static const Dark_Error DARK_ERROR_UNREACHABLE = { NULL, "unreachable", "unreachable part of code reached" };
static const Dark_Error DARK_ERROR_SWITCH = { &DARK_ERROR_UNREACHABLE, "switch", "unhandled switch value" };

//runtime error
static const Dark_Error DARK_ERROR_RUNTIME = { NULL, "runtime", NULL };
static const Dark_Error DARK_ERROR_OVERFLOW = { &DARK_ERROR_RUNTIME, "overflow", "exeeded size limit" };
static const Dark_Error DARK_ERROR_UNDERFLOW = { &DARK_ERROR_RUNTIME, "underflow", "undercut size limit" };
static const Dark_Error DARK_ERROR_ALLOCATION = { &DARK_ERROR_RUNTIME, "allocation", "allocation failed" };
static const Dark_Error DARK_ERROR_INTERNAL = { NULL, "internal", NULL };

static const Dark_Error DARK_ERROR_API = { &DARK_ERROR_RUNTIME, "api", "api failed" };
static const Dark_Error DARK_ERROR_DARK = { &DARK_ERROR_API, "dark", NULL};

//logic error
static const Dark_Error DARK_ERROR_LOGIC = { NULL, "logic", NULL };
static const Dark_Error DARK_ERROR_MATH = { &DARK_ERROR_LOGIC, "math", "undefined operation" };

static const Dark_Error DARK_ERROR_STATE = { &DARK_ERROR_LOGIC, "state", NULL};
static const Dark_Error DARK_ERROR_INSTATE = { &DARK_ERROR_STATE, "instate", "already in requested state" };
static const Dark_Error DARK_ERROR_NOSTATE = { &DARK_ERROR_STATE, "nostate", "not in required state" };

static const Dark_Error DARK_ERROR_VALUE = { &DARK_ERROR_LOGIC, "value", "invalid value" };
static const Dark_Error DARK_ERROR_NULL = { &DARK_ERROR_VALUE, "null", "unexpected null-pointer" };
static const Dark_Error DARK_ERROR_ZERO = { &DARK_ERROR_VALUE, "zero", "unexpected zero" };
static const Dark_Error DARK_ERROR_ENUM = { &DARK_ERROR_VALUE, "enum", NULL };
static const Dark_Error DARK_ERROR_RANGE = { &DARK_ERROR_VALUE, "range", "exceeded defined range"};

//nosupport error
static const Dark_Error DARK_ERROR_NOSUPPORT = { NULL, "no support", NULL };
static const Dark_Error DARK_ERROR_HARDWARE = { &DARK_ERROR_NOSUPPORT, "hardware", NULL };
static const Dark_Error DARK_ERROR_SOFTWARE = { &DARK_ERROR_NOSUPPORT, "software", NULL };

#endif // !defined(___DARK___ERROR_H)
