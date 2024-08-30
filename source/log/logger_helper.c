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
#include <dark/platform/platform.h>

void dark_logger_log_helper(const Dark_Library* const library_, const char* const module_, const char* const unit_, Dark_Logger* const logger_, const Dark_Log_Level level_, const Dark_Cbuffer_View cbuffer_view_, const size_t i_)
{
    //library_
    //module_
    //unit_
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(___DARK_LOG_LEVEL_MIN < level_ && level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);
    DARK_ASSERT(i_ <= DARK_LOGGER_STREAM_COUNT_MAX, DARK_ERROR_VALUE);

    if(logger_->ostream.settings[i_].format.timestamp_is)
    {
        dark_logger_stamp_recent_make(logger_);

        dark_string_insert_back(&logger_->log_string, '[');

        const Dark_Cbuffer cbuffer = { DARK_STAMP_HMS_SIZE, logger_->stamp.buffer };
        dark_string_append_cbuffer_view(&logger_->log_string, dark_cbuffer_to_view(cbuffer));

        dark_string_insert_back(&logger_->log_string, ']');
    }

    uint64_t id;

    switch(logger_->ostream.settings[i_].format.thread)
    {
    case DARK_LOGGER_THREAD_NOT:
        break;
    case DARK_LOGGER_THREAD_UINT:
        id = dark_thread_current_id();
        dark_string_append_f(&logger_->log_string, "[%llu]", id);
        break;
    case DARK_LOGGER_THREAD_HEX:
        id = dark_thread_current_id();
        dark_string_append_f(&logger_->log_string, "[0x%llx]", id);
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }

    if(logger_->ostream.settings[i_].format.name_is && logger_->name_lenght > 0)
    {
        dark_string_insert_back(&logger_->log_string, '[');
        dark_string_append_cstring(&logger_->log_string, logger_->settings.name);
        dark_string_insert_back(&logger_->log_string, ']');
    }

    if(logger_->ostream.settings[i_].format.library_is && NULL != library_)
    {
        const size_t name_lenght = dark_cstring_lenght(library_->name);

        if(logger_->ostream.settings[i_].format.library_is && name_lenght > 0)
        {
            dark_string_insert_back(&logger_->log_string, '[');

            const size_t color_lenght = dark_cstring_lenght(library_->color);

            if(logger_->ostream.settings[i_].color_is && color_lenght > 0)
            {
                const Dark_Cbuffer_View color_view = { color_lenght, library_->color };
                dark_string_append_cbuffer_view(&logger_->log_string, color_view);
            }

            const Dark_Cbuffer_View name_view = { name_lenght, library_->name };
            dark_string_append_cbuffer_view(&logger_->log_string, name_view);
            if(logger_->ostream.settings[i_].color_is && color_lenght > 0)
            {
                dark_string_append_cstring(&logger_->log_string, DARK_CONSOLE_COLOR_RESET);
            }

            dark_string_insert_back(&logger_->log_string, ']');
        }
    }

    const Dark_Cbuffer_View level_color = dark_log_level_color(level_);
    const Dark_Cbuffer_View level_name = dark_log_level_name(level_);

    dark_string_insert_back(&logger_->log_string, '[');

    if(logger_->ostream.settings[i_].color_is && level_color.size > 0)
    {
        dark_string_append_cbuffer_view(&logger_->log_string, level_color);
    }

    DARK_ASSERT(level_name.size > 0, DARK_ERROR_UNKNOWN);
    dark_string_append_cbuffer_view(&logger_->log_string, level_name);

    if(logger_->ostream.settings[i_].color_is && level_color.size > 0)
    {
        dark_string_append_cstring(&logger_->log_string, DARK_CONSOLE_COLOR_RESET);
    }

    dark_string_insert_back(&logger_->log_string, ']');
    dark_string_insert_back(&logger_->log_string, ' ');

    if(logger_->ostream.settings[i_].format.module_is && NULL != module_)
    {
        const Dark_Cbuffer_View view = dark_cstring_to_cbuffer_view(module_);

        if(view.size > 0)
        {
            dark_string_append_cstring(&logger_->log_string, module_);
            dark_string_insert_back(&logger_->log_string, ':');
            dark_string_insert_back(&logger_->log_string, ' ');
        }
    }

    if(logger_->ostream.settings[i_].format.unit_is && NULL != unit_)
    {
        const Dark_Cbuffer_View view = dark_cstring_to_cbuffer_view(module_);

        if(view.size > 0)
        {
            dark_string_append_cstring(&logger_->log_string, unit_);
            dark_string_insert_back(&logger_->log_string, ':');
            dark_string_insert_back(&logger_->log_string, ' ');
        }
    }

    dark_string_append_cbuffer_view(&logger_->log_string, cbuffer_view_);
}

void dark_logger_stamp_recent_make(Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);

    if(!logger_->stamp.recent_is)
    {
        const Dark_Cbuffer cbuffer = { DARK_STAMP_HMS_SIZE, logger_->stamp.buffer };
        dark_stamp_hms_write(cbuffer);
    }

    if(logger_->settings.update_is)
    {
        logger_->stamp.recent_is = true;
    }
}

Dark_Cbuffer_View dark_log_level_name(const Dark_Log_Level level_)
{
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);

    switch(level_)
    {
    case DARK_LOG_LEVEL_TRACE:
        return dark_cstring_to_cbuffer_view("trace");
    case DARK_LOG_LEVEL_COMMENT:
        return dark_cstring_to_cbuffer_view("comment");
    case DARK_LOG_LEVEL_DEBUG:
        return dark_cstring_to_cbuffer_view("debug");
    case DARK_LOG_LEVEL_NOTE:
        return dark_cstring_to_cbuffer_view("note");
    case DARK_LOG_LEVEL_INFO:
        return dark_cstring_to_cbuffer_view("info");
    case DARK_LOG_LEVEL_NOTICE:
        return dark_cstring_to_cbuffer_view("notice");
    case DARK_LOG_LEVEL_WARN:
        return dark_cstring_to_cbuffer_view("warn");
    case DARK_LOG_LEVEL_ERROR:
        return dark_cstring_to_cbuffer_view("error");
    case DARK_LOG_LEVEL_CRITICAL:
        return dark_cstring_to_cbuffer_view("critical");
    case DARK_LOG_LEVEL_ALERT:
        return dark_cstring_to_cbuffer_view("alert");
    case DARK_LOG_LEVEL_EMERGENCY:
        return dark_cstring_to_cbuffer_view("emergency");
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
}

Dark_Cbuffer_View dark_log_level_color(const Dark_Log_Level level_)
{
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);

    switch(level_)
    {
    case DARK_LOG_LEVEL_TRACE:
        return dark_cstring_to_cbuffer_view("");
    case DARK_LOG_LEVEL_COMMENT:
        return dark_cstring_to_cbuffer_view("");
    case DARK_LOG_LEVEL_DEBUG:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_GREEN);
    case DARK_LOG_LEVEL_NOTE:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_CYAN);
    case DARK_LOG_LEVEL_INFO:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_BLUE);
    case DARK_LOG_LEVEL_NOTICE:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_MAGENTA);
    case DARK_LOG_LEVEL_WARN:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_YELLOW);
    case DARK_LOG_LEVEL_ERROR:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_FG_RED);
    case DARK_LOG_LEVEL_CRITICAL:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_BG_MAGENTA);
    case DARK_LOG_LEVEL_ALERT:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_BG_YELLOW);
    case DARK_LOG_LEVEL_EMERGENCY:
        return dark_cstring_to_cbuffer_view(DARK_CONSOLE_COLOR_BG_RED);
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
}
