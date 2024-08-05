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
#include <dark/log/logger_struct.h>
#include <dark/time/time.h>

#undef DARK_UNIT
#define DARK_UNIT "logger"

size_t dark_logger_struct_size(void)
{
    return sizeof(Dark_Logger);
}

void dark_logger_construct(Dark_Allocator* const allocator_, Dark_Logger* const logger_, const Dark_Logger_Settings settings_, Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(settings_.level_min < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    logger_->allocator = allocator_;
    logger_->settings = settings_;
    logger_->ostream.instance = ostream_;
    logger_->ostream.mutex = mutex_;

    dark_string_construct_capacity(allocator_, &logger_->log_string, dark_growth_standard, 64);
    dark_string_construct_capacity(allocator_, &logger_->va_string, dark_growth_standard, 64);

    logger_->stamp.recent_is = logger_->settings.update_is;
}

void dark_logger_destruct(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    dark_string_destruct(&logger_->log_string);
    dark_string_destruct(&logger_->va_string);
}

Dark_Logger* dark_logger_new(Dark_Allocator* const allocator_, const Dark_Logger_Settings settings_, Dark_Ostream* const stream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(settings_.level_min < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != stream_, DARK_ERROR_NULL);
    //mutex_

    Dark_Logger* const logger = dark_malloc(logger->allocator, sizeof(*logger));
    DARK_ASSERT(NULL != logger, DARK_ERROR_ALLOCATION);

    dark_logger_construct(allocator_, logger, settings_, stream_, mutex_);

    return logger;
}

void dark_logger_delete(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    dark_logger_destruct(logger_);

    dark_free(logger_->allocator, logger_, sizeof(*logger_));
}

void dark_logger_update(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    logger_->stamp.recent_is = false;
}

void dark_logger_log(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, Dark_Logger* const logger_, const Dark_Log_Level level_, const Dark_Cbuffer cbuffer_view_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    if(logger_->settings.level_min > level_)
    {
        return;
    }

    if(!logger_->settings.log_is)
    {
        return;
    }

    dark_logger_stamp_recent_make(logger_);

    dark_log_general(library_, module_, unit_, name_, logger_->settings.format, level_, logger_->ostream, logger_->ostream.mutex, cbuffer_view_, logger_->settings.color, logger_->stamp, logger_->log_string);
}

void dark_logger_log_cstring(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const cstring_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    const Dark_Cbuffer_View cbuffer_view = dark_cstring_cbuffer_view(cstring_);

    dark_logger_log(library_, module_, unit_, name_, logger_, level_, cbuffer_view);
}

void dark_logger_log_f(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, ...)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);

    dark_string_append_v(logger_->va_string, format_, args);

    va_end(args);

    dark_logger_log(library_, module_, unit_, name_, logger_, level_, dark_string_cbuffer_view(logger_->va_string));

    dark_string_clear(logger_->va_string);
}

void dark_logger_log_v(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, va_list arguments_)
{
    //library_
    //module_
    //unit_
    //name_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    dark_string_append_v(logger_->va_string, format_, arguments_);

    dark_logger_log(library_, module_, unit_, name_, logger_, level_, dark_string_cbuffer_view(logger_->va_string));

    dark_string_clear(logger_->va_string);
}

void dark_logger_stamp_recent_make(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    if(!logger_->stamp.recent_is)
    {
        dark_stamp_hms_write(logger_->stamp);
    }

    if(logger_->settings.update_is)
    {
        logger_->stamp.recent_is = true;
    }
}
