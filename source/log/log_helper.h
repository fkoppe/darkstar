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

#if !defined(___DARK___LOG_HELPER_H)
#define ___DARK___LOG_HELPER_H

#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>
#include <dark/log/log_data.h>

static const size_t LOG_BUFFER_SIZE = 64;

void dark_log_general(const Dark_Library* library, const char* module, const char* unit, const char* name, Dark_Log_Format lformat, Dark_Log_Level level, void* ostream, void* ostream_mutex, size_t count, const char* cbuffer, const char* color, const char* stamp, void* string);

const char* dark_level_name(Dark_Log_Level level);
const char* dark_level_color(Dark_Log_Level level);

#endif // !defined(___DARK___LOG_HELPER_H)
