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

#include <dark/core/essential.h>

typedef enum Dark_Log_Level
{
    DARK_LOG_LEVEL_COMMENT,
    DARK_LOG_LEVEL_INTERNAL,
    DARK_LOG_LEVEL_DEBUG,
    DARK_LOG_LEVEL_TRACE,
    DARK_LOG_LEVEL_INFO,
    DARK_LOG_LEVEL_NOTICE,
    DARK_LOG_LEVEL_WARN,
    DARK_LOG_LEVEL_ERROR,
    DARK_LOG_LEVEL_CRITICAL,
    DARK_LOG_LEVEL_ALERT,
    DARK_LOG_LEVEL_EMERGENCY,
    ___DARK_LOG_LEVEL_MAX,
} Dark_Log_Level;

typedef struct Dark_Logger_Settings
{
    bool log_is;
    Dark_Log_Level level_min;
    struct
    {
        bool time;
        bool thread;
        bool name;
        bool library;
        bool module;
        bool unit;
    } format;
} Dark_Logger_Settings;

size_t dark_logger_struct_size(void);

void* dark_logger_new(Dark_Logger_Settings settings, const char* name, void* stream, void* mutex);
void dark_logger_delete(void* logger);

void dark_logger_log(void* logger, Dark_Log_Level level, const char* cstring);
void dark_logger_logf(void* logger, Dark_Log_Level level, const char* format, ...);
void dark_logger_logv(void* logger, Dark_Log_Level level, const char* format, ...);

const char* dark_logger_level_name(Dark_Log_Level level);
const char* dark_logger_level_color(Dark_Log_Level level);

#endif // !defined(___DARK___LOGGER_H)
