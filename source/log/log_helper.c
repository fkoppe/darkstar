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
#include <dark/platform/platform.h>
#include <dark/stream/stream.h>
#include <dark/time/time.h>

#undef DARK_UNIT
#define DARK_UNIT "log_helper.h"

void dark_log_general(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, const Dark_Log_Format lformat_, const Dark_Log_Level level_, void* const ostream_, void* const ostream_mutex_, const size_t count_, const char* const cbuffer_, const char* const color_, const char* const stamp_, void* const string_)
{
    //library_
    //module_
    //unit_
    //name_
    //lformat_
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //ostream_mutex_
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_, DARK_ERROR_NULL);
    //color_
    //stamp_
    //string_

    const char* module_color = "";
    if(NULL == color_ || dark_cbuffer_compare("", color_, 1))
    {
        if(library_ == DARK_LIBRARY)
        {
            module_color = DARK_CONSOLE_COLOR_FG_BLUE;
        }
        else
        {
            module_color = DARK_CONSOLE_COLOR_FG_GREEN;
        }
    }
    else
    {
        module_color = color_;
    }

    void* string;

    if(NULL == string_)
    {
        string = dark_string_new_capacity(DARK_GROWTH_STANDARD, LOG_BUFFER_SIZE);
    }
    else
    {
        string = string_;
        dark_string_reserve(string, LOG_BUFFER_SIZE);
    }

    if(lformat_.timestamp)
    {
        dark_string_insert_back(string, '[');

        if(NULL == stamp_)
        {
            char buffer[DARK_STAMP_HMS_SIZE];
            dark_stamp_hms(buffer);
            dark_string_append_cbuffer(string, DARK_STAMP_HMS_SIZE, buffer);
        }
        else
        {
            dark_string_append_cbuffer(string, DARK_STAMP_HMS_SIZE, stamp_);
        }

        dark_string_insert_back(string, ']');
    }

    if(lformat_.thread)
    {
        const uint64_t id = dark_thread_id_current();

        switch(lformat_.thread)
        {
        case DARK_LOG_THREAD_NOT:
            break;
        case DARK_LOG_THREAD_UINT:
            dark_string_append_f(string, "[%llu]", id);
            break;
        case DARK_LOG_THREAD_HEX:
            dark_string_append_f(string, "[0x%llx]", id);
            break;
        default:
            DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        }
    }

    if(lformat_.library && NULL != library_)
    {
        dark_string_insert_back(string, '[');

        if(dark_cbuffer_compare("", module_color, 1))
        {
            dark_string_append_cbuffer(string, dark_cstring_lenght(module_color), module_color);
        }

        dark_string_append_cbuffer(string, dark_cstring_lenght(library_->name), library_->name);

        if(dark_cbuffer_compare("", module_color, 1))
        {
            dark_string_append_cbuffer(string, dark_cstring_lenght(DARK_CONSOLE_COLOR_RESET), DARK_CONSOLE_COLOR_RESET);
        }

        dark_string_insert_back(string, ']');
    }

    const char* level_name = dark_level_name(level_);
    const char* level_color = dark_level_color(level_);

    dark_string_insert_back(string, '[');

    if(dark_cbuffer_compare("", level_color, 1))
    {
        dark_string_append_cbuffer(string, dark_cstring_lenght(level_color), level_color);
    }

    dark_string_append_cbuffer(string, dark_cstring_lenght(level_name), level_name);

    if(dark_cbuffer_compare("", level_color, 1))
    {
        dark_string_append_cbuffer(string, dark_cstring_lenght(DARK_CONSOLE_COLOR_RESET), DARK_CONSOLE_COLOR_RESET);
    }

    dark_string_insert_back(string, ']');
    dark_string_insert_back(string, ' ');

    if(lformat_.module && NULL != module_)
    {
        dark_string_append_cbuffer(string, dark_cstring_lenght(module_), module_);
        dark_string_insert_back(string, ':');
        dark_string_insert_back(string, ' ');
    }

    if(lformat_.unit && NULL != unit_)
    {
        dark_string_append_cbuffer(string, dark_cstring_lenght(unit_), unit_);
        dark_string_insert_back(string, ':');
        dark_string_insert_back(string, ' ');
    }

    if(lformat_.name && NULL != name_)
    {
        dark_string_append_cbuffer(string, dark_cstring_lenght(name_), name_);
        dark_string_insert_back(string, ':');
        dark_string_insert_back(string, ' ');
    }

    if(NULL != ostream_mutex_)
    {
        dark_mutex_lock(ostream_mutex_);
    }

    dark_string_append_cbuffer(string, count_, cbuffer_);
    dark_string_insert_back(string, '\n');

    dark_ostream_write(ostream_, dark_string_size(string) + 1, dark_string_cbuffer_terminated(string));

    if(NULL != ostream_mutex_)
    {
        dark_mutex_unlock(ostream_mutex_);
    }

    dark_string_clear(string);

    if(NULL == string_)
    {
        dark_string_delete(string);
    }
}

const char* dark_level_name(const Dark_Log_Level level_)
{
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);

    switch(level_)
    {
    case DARK_LOG_LEVEL_COMMENT:
        return "comment";
    case DARK_LOG_LEVEL_INTERNAL:
        return "internal";
    case DARK_LOG_LEVEL_DEBUG:
        return "debug";
    case DARK_LOG_LEVEL_TRACE:
        return "trace";
    case DARK_LOG_LEVEL_INFO:
        return "info";
    case DARK_LOG_LEVEL_NOTICE:
        return "notice";
    case DARK_LOG_LEVEL_WARN:
        return "warn";
    case DARK_LOG_LEVEL_ERROR:
        return "error";
    case DARK_LOG_LEVEL_CRITICAL:
        return "critical";
    case DARK_LOG_LEVEL_ALERT:
        return "alert";
    case DARK_LOG_LEVEL_EMERGENCY:
        return "emergency";
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
}

const char* dark_level_color(const Dark_Log_Level level_)
{
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);

    switch(level_)
    {
    case DARK_LOG_LEVEL_COMMENT:
        return "";
    case DARK_LOG_LEVEL_INTERNAL:
        return "";
    case DARK_LOG_LEVEL_DEBUG:
        return DARK_CONSOLE_COLOR_FG_BLUE;
    case DARK_LOG_LEVEL_TRACE:
        return DARK_CONSOLE_COLOR_FG_PURPLE;
    case DARK_LOG_LEVEL_INFO:
        return DARK_CONSOLE_COLOR_FG_CYAN;
    case DARK_LOG_LEVEL_NOTICE:
        return DARK_CONSOLE_COLOR_EFG_ORANGE;
    case DARK_LOG_LEVEL_WARN:
        return DARK_CONSOLE_COLOR_FG_YELLOW;
    case DARK_LOG_LEVEL_ERROR:
        return DARK_CONSOLE_COLOR_FG_RED;
    case DARK_LOG_LEVEL_CRITICAL:
        return DARK_CONSOLE_COLOR_BG_RED;
    case DARK_LOG_LEVEL_ALERT:
        return DARK_CONSOLE_COLOR_BG_YELLOW;
    case DARK_LOG_LEVEL_EMERGENCY:
        return DARK_CONSOLE_COLOR_EBG_RED;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
}
