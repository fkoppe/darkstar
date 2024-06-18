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

#if !defined(___DARK___ASSERT_H)
#define ___DARK___ASSERT_H

#include <dark/core/enviroment.h>
#include <dark/core/error.h>
#include <dark/core/message.h>
#include <dark/core/std.h>
#include <dark/core/terminate.h>
#include <dark/core/util.h>

#if defined(___DARK_DEBUG)
#define DARK_ASSERT(condition, error) if(!(condition)) dark_assert((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (#condition), (error), DARK_MESSAGE_NONE)
#define DARK_ASSERT_CSTRING(condition, error, cstring) if(!(condition)) dark_assert((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (#condition), (error), (Dark_Message){ NULL, (cstring), false })
#define DARK_ASSERT_MESSAGE(condition, error, message) if(!(condition)) dark_assert((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (#condition), (error), (message))
#else
#define DARK_ASSERT(condition, error)
#define DARK_ASSERT_CSTRING(condition, error, cstring)
#define DARK_ASSERT_MESSAGE(condition, error, message)
#endif // defined(___DARK_DEBUG)

static const Dark_Message DARK_MESSAGE_ASSERT = { &DARK_MESSAGE_ABORT, "assertion failed - ", NULL };

DARK_NORETURN void dark_assert(Dark_Location location, const Dark_Library* library, const char* module, const char* unit, const char* condition, Dark_Error error, Dark_Message message);

#endif // !defined(___DARK___ASSERT_H)
