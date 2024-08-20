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

#include <dark/char/cbuffer_view.h>
#include <dark/core/std.h>
#include <dark/log/log_data.h>
#include <dark/memory/allocator.h>
#include <dark/platform/mutex.h>
#include <dark/stream/ostream.h>

#include <stdarg.h>

#define DARK_LOGGER_STREAM_COUNT_MAX 3

#define DARK_LOG_CSTRING(logger, level, cstring) dark_logger_log_cstring(DARK_MODULE, DARK_UNIT, (logger), (level), (cstring))
#define DARK_LOG_CBUFFER_VIEW(logger, level, cbuffer_view) dark_logger_log_cbuffer_view(DARK_MODULE, DARK_UNIT, (logger), (level), (cbuffer_view))
#define DARK_LOG_F(logger, level, format, ...)
#define DARK_LOG_V(logger, level, format, args)

#define DARK_PLOG_CSTRING(logger, level, cstring)  dark_logger_plog_cstring(DARK_MODULE, DARK_UNIT, __FILE__, __LINE__, (logger), (level), (cstring))
#define DARK_PLOG_CBUFFER_VIEW(logger, level, cbuffer_view) dark_logger_plog_cbuffer_view(DARK_MODULE, DARK_UNIT, __FILE__, __LINE__, (logger), (level), (cbuffer_view))
#define DARK_PLOG_F(logger, level, format, ...)
#define DARK_PLOG_V(logger, level, format, args)

#define DARK_DLOG_CSTRING(logger, level, cstring)  dark_logger_dlog_cstring((logger), (level), (cstring))
#define DARK_DLOG_CBUFFER_VIEW(logger, level, cbuffer_view) dark_logger_dlog_cbuffer_view((logger), (level), (cbuffer_view))
#define DARK_DLOG_F(logger, level, format, ...)
#define DARK_DLOG_V(logger, level, format, args)

typedef struct Dark_Logger Dark_Logger;

typedef enum Dark_Logger_Thread Dark_Logger_Thread;
enum Dark_Logger_Thread
{
    ___DARK_LOGGER_THREAD_MIN,
    DARK_LOGGER_THREAD_NOT,
    DARK_LOGGER_THREAD_UINT,
    DARK_LOGGER_THREAD_HEX,
    ___DARK_LOGGER_THREAD_MAX,
};

typedef struct Dark_Logger_Ostream_Settings Dark_Logger_Ostream_Settings;
struct Dark_Logger_Ostream_Settings
{
    bool color_is;
    Dark_Log_Level level_min;
    struct
    {
        bool timestamp_is;
        Dark_Logger_Thread thread;
        bool name_is;
        bool module_is;
        bool unit_is;
    } format;
};

typedef struct Dark_Logger_Settings Dark_Logger_Settings;
struct Dark_Logger_Settings
{
    const char* name;
    const char* color;
    bool log_is;
    bool update_is;
};

void dark_logger_construct(Dark_Allocator* allocator, Dark_Logger* logger, Dark_Logger_Settings settings);
void dark_logger_destruct(Dark_Logger* logger);

Dark_Logger* dark_logger_new(Dark_Allocator* allocator, Dark_Logger_Settings settings);
void dark_logger_delete(Dark_Logger* logger);

void dark_logger_ostream_add(Dark_Logger* logger, Dark_Logger_Ostream_Settings settings, Dark_Ostream* ostream, Dark_Mutex* mutex);

void dark_logger_update(Dark_Logger* logger);

void dark_logger_log_cstring(const char* module, const char* unit, Dark_Logger* logger, Dark_Log_Level level, const char* cstring);
void dark_logger_log_cbuffer_view(const char* module, const char* unit, Dark_Logger* logger, Dark_Log_Level level, Dark_Cbuffer_View cbuffer_view);
void dark_logger_log_f(const char* module, const char* unit, Dark_Logger* logger, Dark_Log_Level level, const char* format, ...);
void dark_logger_log_v(const char* module, const char* unit, Dark_Logger* logger, Dark_Log_Level level, const char* format, va_list arguments);

void dark_logger_plog_cstring(const char* module, const char* unit, const char* file, intmax_t line, Dark_Logger* logger, Dark_Log_Level level, const char* cstring);
void dark_logger_plog_cbuffer_view(const char* module, const char* unit, const char* file, intmax_t line, Dark_Logger* logger, Dark_Log_Level level, Dark_Cbuffer_View cbuffer_view);
void dark_logger_plog_f(const char* module, const char* unit, const char* file, intmax_t line, Dark_Logger* logger, Dark_Log_Level level, const char* format, ...);
void dark_logger_plog_v(const char* module, const char* unit, const char* file, intmax_t line, Dark_Logger* logger, Dark_Log_Level level, const char* format, va_list arguments);

void dark_logger_dlog_cstring(Dark_Logger* logger, Dark_Log_Level level, const char* cstring);
void dark_logger_dlog_cbuffer_view(Dark_Logger* logger, Dark_Log_Level level, Dark_Cbuffer_View cbuffer_view);
void dark_logger_dlog_f(Dark_Logger* logger, Dark_Log_Level level, const char* format, ...);
void dark_logger_dlog_v(Dark_Logger* logger, Dark_Log_Level level, const char* format, va_list arguments);

void dark_logger_stamp_recent_make(Dark_Logger* logger);

size_t dark_logger_struct_byte(void);

#endif // !defined(___DARK___LOGGER_H)
