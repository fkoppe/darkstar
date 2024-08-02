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

#undef DARK_UNIT
#define DARK_UNIT "static_log.h"

void dark_static_log_cstring(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, const Dark_Log_Format lformat_, const Dark_Log_Level level_, void* const ostream_, void* const ostream_mutex_, const char* const cstring_)
{
    //library_
    //module_
    //unit_
    //name_
    //lformat_
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //ostream_mutex_
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    dark_log_general(library_, module_, unit_, name_, lformat_, level_, ostream_, ostream_mutex_, dark_cstring_lenght(cstring_), cstring_, NULL, NULL, NULL);
}

void dark_static_log_cbuffer(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, const Dark_Log_Format lformat_, const Dark_Log_Level level_, void* const ostream_, void* const ostream_mutex_, const size_t count_, const char* const cbuffer_)
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

    dark_log_general(library_, module_, unit_, name_, lformat_, level_, ostream_, ostream_mutex_, count_, cbuffer_, NULL, NULL, NULL);
}

void dark_static_log_f(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, const Dark_Log_Format lformat_, const Dark_Log_Level level_, void* const ostream_, void* const ostream_mutex_, const char* const format_, ...)
{
    //library_
    //module_
    //unit_
    //name_
    //lformat_
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //ostream_mutex_
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);

    void* string = dark_string_new_v(DARK_GROWTH_STANDARD, format_, args);

    dark_log_general(library_, module_, unit_, name_, lformat_, level_, ostream_, ostream_mutex_, dark_string_size(string), dark_string_cbuffer_terminated(string), NULL, NULL, NULL);

    dark_string_delete(string);
}

void dark_static_log_v(const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const name_, const Dark_Log_Format lformat_, const Dark_Log_Level level_, void* const ostream_, void* const ostream_mutex_, const char* const format_, va_list arguments_)
{
    //library_
    //module_
    //unit_
    //name_
    //lformat_
    DARK_ASSERT(level_ < ___DARK_LOG_LEVEL_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //ostream_mutex_
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    void* string = dark_string_new_v(DARK_GROWTH_STANDARD, format_, arguments_);

    dark_log_general(library_, module_, unit_, name_, lformat_, level_, ostream_, ostream_mutex_, dark_string_size(string), dark_string_cbuffer_terminated(string), NULL, NULL, NULL);

    dark_string_delete(string);
}
