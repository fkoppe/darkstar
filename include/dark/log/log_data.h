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

#if !defined(___DARK___LOG_DATA_H)
#define ___DARK___LOG_DATA_H

#include <dark/core/std.h>

typedef enum Dark_Log_Level Dark_Log_Level;
enum Dark_Log_Level
{
    ___DARK_LOG_LEVEL_MIN,
    DARK_LOG_LEVEL_TRACE,
    DARK_LOG_LEVEL_COMMENT,
    DARK_LOG_LEVEL_DEBUG,
    DARK_LOG_LEVEL_NOTE,
    DARK_LOG_LEVEL_INFO,
    DARK_LOG_LEVEL_NOTICE,
    DARK_LOG_LEVEL_WARN,
    DARK_LOG_LEVEL_ERROR,
    DARK_LOG_LEVEL_CRITICAL,
    DARK_LOG_LEVEL_ALERT,
    DARK_LOG_LEVEL_EMERGENCY,
    ___DARK_LOG_LEVEL_MAX,
};

#endif // !defined(___DARK___LOG_DATA_H)
