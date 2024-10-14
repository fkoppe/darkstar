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

#include <dark/core/enviroment.h>
#include <dark/core/error.h>
#include <dark/core/message.h>
#include <dark/core/std.h>
#include <dark/core/util.h>

#if defined(___DARK_DEBINFO)
#define DARK_EXIT(code) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), DARK_ERROR_UNDEFINED, DARK_MESSAGE_NONE, false)
#define DARK_EXIT_ERROR(code, error) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), (error), DARK_MESSAGE_NONE, false)
#define DARK_EXIT_CSTRING(code, error, cstring) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), (error), (Dark_Message){ NULL, (cstring) }, false)
#define DARK_EXIT_MESSAGE(code, error, message) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, (code), (error), (message), false)
#define DARK_ABORT dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, DARK_ERROR_UNDEFINED, DARK_MESSAGE_NONE, true)
#define DARK_ABORT_ERROR(error) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, (error), DARK_MESSAGE_NONE, true)
#define DARK_ABORT_CSTRING(error, cstring) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, (error), (Dark_Message){ NULL, NULL, (cstring) }, true)
#define DARK_ABORT_MESSAGE(error, message) dark_terminate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, 0, (error), (message), true)
#else
#define DARK_EXIT(code) exit(code)
#define DARK_EXIT_ERROR(code, error) exit(code)
#define DARK_EXIT_CSTRING(code, error, cstring) exit(code)
#define DARK_EXIT_MESSAGE(code, error, message) exit(code)
#define DARK_ABORT abort()
#define DARK_ABORT_ERROR(error) abort()
#define DARK_ABORT_CSTRING(error, cstring) abort()
#define DARK_ABORT_MESSAGE(error, message) abort()
#endif // defined(___DARK_DEBINFO)

static const Dark_Message DARK_MESSAGE_EXIT = { NULL, NULL, "exit has been called" };
static const Dark_Message DARK_MESSAGE_ABORT = { NULL, NULL, "abort has been called" };

DARK_NORETURN void dark_abort(void);
DARK_NORETURN void dark_terminate(Dark_Location location, const Dark_Library* library, const char* module, const char* unit, int code, Dark_Error error, Dark_Message message, bool abort_is);

#endif // !defined(___DARK___TERMINATE_H)
