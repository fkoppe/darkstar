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

#if !defined(___DARK___LOGGER_HELPER_H)
#define ___DARK___LOGGER_HELPER_H

#include <dark/core/std.h>
#include <dark/log/logger.h>

void dark_logger_log_helper(const Dark_Library* library, const char* module, const char* unit, Dark_Logger* logger, Dark_Log_Level level, Dark_Cbuffer_View cbuffer_view, size_t i);

void dark_logger_stamp_recent_make(Dark_Logger* logger);

const char* dark_log_level_name(Dark_Log_Level level);
const char* dark_log_level_color(Dark_Log_Level level);

#endif // !defined(___DARK___LOGGER_HELPER_H)
