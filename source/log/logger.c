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

#include "log_helper.h"
#include "log_module.h"

#include <dark/char/char.h>
#include <dark/core/core.h>
#include <dark/log/log.h>
#include <dark/time/time.h>

#undef DARK_UNIT
#define DARK_UNIT "logger"

typedef struct Dark_Logger
{
    Dark_Logger_Settings settings;
    void* ostream;
    void* ostream_mutex;
    void* string;
    bool stamp_recent_is;
    char stamp[8];
} Dark_Logger;

size_t dark_logger_struct_size(void)
{
    return sizeof(Dark_Logger);
}

void* dark_logger_new(const Dark_Logger_Settings settings_, void* const stream_, void* const mutex_)
{
    DARK_ASSERT(settings_.level_min < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != stream_, DARK_ERROR_NULL);
    //mutex_

    Dark_Logger* const logger = malloc(sizeof(*logger));
    DARK_ASSERT(NULL != logger, DARK_ERROR_ALLOCATION);

    logger->settings = settings_;
    logger->ostream = stream_;
    logger->ostream_mutex = mutex_;
    logger->string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 64);
    logger->stamp_recent_is = logger->settings.update_is;

    return logger;
}

void dark_logger_delete(void* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    dark_string_delete(logger->string);

    free(logger);
}

void dark_logger_update(void* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    logger->stamp_recent_is = false;
}

void dark_logger_log(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, void* const logger_, const Dark_Log_Level level_, const size_t count_, const char* const cbuffer_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    if(logger->settings.level_min > level_)
    {
        return;
    }

    if(!logger->settings.log_is)
    {
        return;
    }

    dark_logger_stamp_recent_make(logger);

    dark_log_general(library_, module_, unit_, name_, logger->settings.format, level_, logger->ostream, logger->ostream_mutex, count_, cbuffer_, logger->settings.color, logger->stamp, logger->string);
}

void dark_logger_log_cstring(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, void* const logger_, const Dark_Log_Level level_, const char* const cstring_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    dark_logger_log(library_, module_, unit_, name_, logger, level_, dark_cstring_lenght(cstring_), cstring_);
}

void dark_logger_log_f(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, void* const logger_, const Dark_Log_Level level_, const char* const format_, ...)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    va_list args;
    va_start(args, format_);

    void* string = dark_string_new_v(DARK_GROWTH_STANDARD, format_, args);

    va_end(args);

    dark_logger_log(library_, module_, unit_, name_, logger, level_, dark_string_size(string), dark_string_cbuffer_terminated(string));

    dark_string_delete(string);
}

void dark_logger_log_v(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, void* const logger_, const Dark_Log_Level level_, const char* const format_, va_list arguments_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    void* string = dark_string_new_v(DARK_GROWTH_STANDARD, format_, arguments_);

    dark_logger_log(library_, module_, unit_, name_, logger, level_, dark_string_size(string), dark_string_cbuffer_terminated(string));

    dark_string_delete(string);
}

void dark_logger_stamp_recent_make(void* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    Dark_Logger* const logger = logger_;

    if(!logger->stamp_recent_is)
    {
        dark_stamp_hms(logger->stamp);
    }

    if(logger->settings.update_is)
    {
        logger->stamp_recent_is = true;
    }
}
