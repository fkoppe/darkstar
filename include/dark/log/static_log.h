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

#if !defined(___DARK___STATIC_LOG_H)
#define ___DARK___STATIC_LOG_H

#include <dark/char/cbuffer.h>
#include <dark/char/char.h>
#include <dark/core/enviroment.h>
#include <dark/core/std.h>
#include <dark/log/log_data.h>

#include <stdarg.h>

#if !defined(___DARK_LOG_NOLOG)
#define DARK_SLOG_CSTRING(name, lformat, level, cstring) dark_static_log_cstring(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, lformat, level, cstring)
#define DARK_SLOG_CBUFFER(name, lformat, level, cbuffer) dark_static_log_cbuffer(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, lformat, level, cbuffer)
#define DARK_SLOG_F(name, lformat, level, format, ...) dark_static_log_f(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, lformat, level, ostream, ostream_mutex, format, __VA_ARGS__)
#define DARK_SLOG_V(name, lformat, level, format, args) dark_static_log_v(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, lformat, level, ostream, ostream_mutex, format, args)
#else
#define DARK_SLOG_CSTRING(name, lformat, level, cstring)
#define DARK_SLOG_CBUFFER(name, lformat, level, cbuffer)
#define DARK_SLOG_F(name, lformat, level, format, ...)
#define DARK_SLOG_V(name, lformat, level, format, args)
#endif // !defined(___DARK_LOG_NOLOG)

void dark_static_log_cstring(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Log_Format lformat, Dark_Log_Level level, const char* cstring);
void dark_static_log_cbuffer(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Log_Format lformat, Dark_Log_Level level, Dark_Cbuffer cbuffer);
void dark_static_log_f(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Log_Format lformat, Dark_Log_Level level, const char* format, ...);
void dark_static_log_v(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Log_Format lformat, Dark_Log_Level level, const char* format, va_list arguments);

#endif // !defined(___DARK___STATIC_LOG_H)
