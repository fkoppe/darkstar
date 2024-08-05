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

#if !defined(___DARK___LOGGER_H)
#define ___DARK___LOGGER_H

#include <dark/char/string.h>
#include <dark/core/enviroment.h>
#include <dark/core/std.h>
#include <dark/log/log_data.h>
#include <dark/platform/mutex.h>
#include <dark/stream/ostream.h>

#include <stdarg.h>

#if !defined(___DARK_LOG_NOLOG)
#define DARK_LOG(logger, level, count, cbuffer) dark_logger_log(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, NULL, logger, level, count, cbuffer)
#define DARK_LOG_CSTRING(logger, level, cstring) dark_logger_log_cstring(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, NULL, logger, level, cstring)
#define DARK_LOG_F(logger, level, format, ...) dark_logger_log_f(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, NULL, logger, level, format, __VA_ARGS__)
#define DARK_LOG_V(logger, level, format, args) dark_logger_log_v(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, NULL, logger, level, format, args)
#define DARK_NLOG(logger, name, level, count, cbuffer) dark_logger_log(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, logger, level, count, cbuffer)
#define DARK_NLOG_CSTRING(logger, name, level, cstring) dark_logger_log_cstring(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, logger, level, cstring)
#define DARK_NLOG_F(logger, name, level, format, ...) dark_logger_log_f(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, logger, level, format, __VA_ARGS__)
#define DARK_NLOG_V(logger, name, level, format, args) dark_logger_log_v(DARK_LIBRARY, DARK_MODULE, DARK_UNIT, name, logger, level, format, args)
#else
#define DARK_LOG(logger, level, count, cbuffer)
#define DARK_LOG_CSTRING(logger, level, cstring)
#define DARK_LOG_F(logger, level, format, ...)
#define DARK_LOG_V(logger, level, format, args)
#define DARK_NLOG(logger, name, level, count, cbuffer)
#define DARK_NLOG_CSTRING(logger, name, level, cstring)
#define DARK_NLOG_F(logger, name, level, format, ...)
#define DARK_NLOG_V(logger, name, level, format, args)
#endif // !defined(___DARK_LOG_NOLOG)

typedef struct Dark_Logger Dark_Logger;

typedef struct Dark_Logger_Settings
{
    Dark_Allocator* allocator;
    const char* color;
    bool log_is;
    bool update_is;
    Dark_Log_Level level_min;
    Dark_Log_Format format;
} Dark_Logger_Settings;

size_t dark_logger_struct_byte(void);

void dark_logger_construct(Dark_Allocator* allocator, Dark_Logger* logger, Dark_Logger_Settings settings, Dark_Ostream* ostream, Dark_Mutex* mutex);
void dark_logger_destruct(Dark_Logger* logger);

Dark_Logger* dark_logger_new(Dark_Allocator* allocator, Dark_Logger_Settings settings, Dark_Ostream* ostream, Dark_Mutex* mutex);
void dark_logger_delete(Dark_Logger* logger);

void dark_logger_update(Dark_Logger* logger);

void dark_logger_log(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Logger* logger, Dark_Log_Level level, size_t count, const char* cbuffer);
void dark_logger_log_cstring(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Logger* logger, Dark_Log_Level level, const char* cstring);
void dark_logger_log_f(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Logger* logger, Dark_Log_Level level, const char* format, ...);
void dark_logger_log_v(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Logger* logger, Dark_Log_Level level, const char* format, va_list arguments);

void dark_logger_stamp_recent_make(Dark_Logger* logger);

#endif // !defined(___DARK___LOGGER_H)
