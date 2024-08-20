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

#include "logger_helper.h"
#include "log_module.h"

#include <dark/char/char.h>
#include <dark/core/core.h>
#include <dark/log/logger.h>
#include <dark/log/logger_struct.h>
#include <dark/memory/memory.h>

#undef DARK_UNIT
#define DARK_UNIT "logger"

void dark_logger_construct(Dark_Allocator* const allocator_, Dark_Logger* const logger_, const Dark_Logger_Settings settings_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != settings_.name, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(settings_.name);

    logger_->allocator = allocator_;
    logger_->settings = settings_;
    logger_->name_view = dark_cstring_to_cbuffer_view(settings_.name);
    logger_->color_lenght = dark_cstring_lenght(settings_.color);

    dark_string_construct_capacity(allocator_, &logger_->log_string, dark_growth_simple, 1024);
    dark_string_construct_capacity(allocator_, &logger_->va_string, dark_growth_simple, 512);

    logger_->stamp.recent_is = false;
    logger_->ostream.count = 0;
}

void dark_logger_destruct(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    dark_string_destruct(&logger_->va_string);
    dark_string_destruct(&logger_->log_string);
}

Dark_Logger* dark_logger_new(Dark_Allocator* const allocator_, const Dark_Logger_Settings settings_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != settings_.name, DARK_ERROR_NULL);

    Dark_Logger* const logger = dark_malloc(allocator_, sizeof(*logger));
    DARK_ASSERT(NULL != logger, DARK_ERROR_ALLOCATION);

    dark_logger_construct(allocator_, logger, settings_);

    return logger;
}

void dark_logger_delete(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    dark_logger_destruct(logger_);

    dark_free(logger_->allocator, logger_, sizeof(*logger_));
}

void dark_logger_ostream_add(Dark_Logger* const logger_, const Dark_Logger_Ostream_Settings settings_, Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < settings_.level_min && settings_.level_min < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(___DARK_LOGGER_THREAD_MIN< settings_.format.thread && settings_.format.thread < ___DARK_LOGGER_THREAD_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    DARK_ASSERT(logger_->ostream.count < DARK_LOGGER_STREAM_COUNT_MAX, DARK_ERROR_OVERFLOW);

    logger_->ostream.settings[logger_->ostream.count] = settings_;
    logger_->ostream.instance[logger_->ostream.count] = ostream_;
    logger_->ostream.mutex[logger_->ostream.count] = mutex_;

    logger_->ostream.count++;
}

void dark_logger_update(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    logger_->stamp.recent_is = false;
}

void dark_logger_log_cstring(const char* const module_, const char* const unit_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const cstring_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    dark_logger_log_cbuffer_view(module_, unit_, logger_, level_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_logger_log_cbuffer_view(const char* const module_, const char* const unit_, Dark_Logger* const logger_, const Dark_Log_Level level_, const Dark_Cbuffer_View cbuffer_view_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    if(!logger_->settings.log_is)
    {
        return;
    }

    for(size_t i = 0; i < logger_->ostream.count; i++)
    {
        if(level_ >= logger_->ostream.settings[i].level_min)
        {
            dark_logger_log_helper(module_, unit_, logger_, level_, cbuffer_view_, i);

            dark_string_insert_back(&logger_->log_string, '\n');

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_lock(logger_->ostream.mutex[i]);
            }

            dark_ostream_write(logger_->ostream.instance[i], dark_cbuffer_view_to_buffer_view(dark_string_cbuffer_view(&logger_->log_string)));

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_unlock(logger_->ostream.mutex[i]);
            }

            dark_string_clear(&logger_->log_string);
        }
    }
}

void dark_logger_log_f(const char* const module_, const char* const unit_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, ...)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;
    va_start(args, format_);
    dark_logger_log_v(module_, unit_, logger_, level_, format_, args);
    va_end(args);
}

void dark_logger_log_v(const char* const module_, const char* const unit_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, va_list arguments_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    dark_string_append_f(&logger_->va_string, format_, arguments_);

    dark_logger_log_cbuffer_view(module_, unit_, logger_, level_, dark_string_cbuffer_view(&logger_->va_string));

    dark_string_clear(&logger_->va_string);
}

void dark_logger_plog_cstring(const char* const module_, const char* const unit_, const char* const file_, const intmax_t line_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const cstring_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(line_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    dark_logger_plog_cbuffer_view(module_, unit_, file_, line_, logger_, level_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_logger_plog_cbuffer_view(const char* const module_, const char* const unit_, const char* const file_, const intmax_t line_, Dark_Logger* const logger_, const Dark_Log_Level level_, const Dark_Cbuffer_View cbuffer_view_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(line_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    if(!logger_->settings.log_is)
    {
        return;
    }

    for(size_t i = 0; i < logger_->ostream.count; i++)
    {
        if(level_ >= logger_->ostream.settings[i].level_min)
        {
            dark_logger_log_helper(module_, unit_, logger_, level_, cbuffer_view_, i);

            dark_string_append_f(&logger_->log_string, " (%s:%ju)\n", file_, line_);

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_lock(logger_->ostream.mutex[i]);
            }

            dark_ostream_write(logger_->ostream.instance[i], dark_cbuffer_view_to_buffer_view(dark_string_cbuffer_view(&logger_->log_string)));

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_unlock(logger_->ostream.mutex[i]);
            }

            dark_string_clear(&logger_->log_string);
        }
    }
}

void dark_logger_plog_f(const char* const module_, const char* const unit_, const char* const file_, const intmax_t line_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, ...)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(line_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;
    va_start(args, format_);
    dark_logger_plog_v(module_, unit_, file_, line_, logger_, level_, format_, args);
    va_end(args);
}

void dark_logger_plog_v(const char* const module_, const char* const unit_, const char* const file_, const intmax_t line_, Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, va_list arguments_)
{
    //module_
    //unit_
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(line_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    dark_string_append_f(&logger_->va_string, format_, arguments_);

    dark_logger_plog_cbuffer_view(module_, unit_, file_, line_, logger_, level_, dark_string_cbuffer_view(&logger_->va_string));

    dark_string_clear(&logger_->va_string);
}

void dark_logger_dlog_cstring(Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const cstring_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    dark_logger_dlog_cbuffer_view(logger_, level_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_logger_dlog_cbuffer_view(Dark_Logger* const logger_, const Dark_Log_Level level_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    if(!logger_->settings.log_is)
    {
        return;
    }

    for(size_t i = 0; i < logger_->ostream.count; i++)
    {
        if(level_ >= logger_->ostream.settings[i].level_min)
        {
            dark_string_append_cbuffer_view(&logger_->log_string, cbuffer_view_);

            dark_string_insert_back(&logger_->log_string, '\n');

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_lock(logger_->ostream.mutex[i]);
            }

            dark_ostream_write(logger_->ostream.instance[i], dark_cbuffer_view_to_buffer_view(dark_string_cbuffer_view(&logger_->log_string)));

            if(NULL != logger_->ostream.mutex[i])
            {
                dark_mutex_unlock(logger_->ostream.mutex[i]);
            }

            dark_string_clear(&logger_->log_string);
        }
    }
}

void dark_logger_dlog_f(Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;
    va_start(args, format_);
    dark_logger_dlog_v(logger_, level_, format_, args);
    va_end(args);
}

void dark_logger_dlog_v(Dark_Logger* const logger_, const Dark_Log_Level level_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    dark_string_append_f(&logger_->va_string, format_, arguments_);

    dark_logger_dlog_cbuffer_view(logger_, level_, dark_string_cbuffer_view(&logger_->va_string));

    dark_string_clear(&logger_->va_string);
}

size_t dark_logger_struct_byte(void)
{
    return sizeof(Dark_Logger);
}
