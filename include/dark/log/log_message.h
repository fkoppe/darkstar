/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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

#if !defined(___DARK___LOG_MESSAGE_H)
#define ___DARK___LOG_MESSAGE_H

#include <dark/core/std.h>
#include <dark/log/logger.h>

#define DARK_LOG_MESSAGE_INITIALISE(logger) DARK_LOG_CSTRING((logger), DARK_LOG_LEVEL_DEBUG, "initialise")
#define DARK_LOG_MESSAGE_SHUTDOWN(logger) DARK_LOG_CSTRING((logger), DARK_LOG_LEVEL_DEBUG, "shutdown")

#define DARK_IDLOG_MESSAGE_INITIALISE(logger, id) DARK_IDLOG_CSTRING((logger), (id), DARK_LOG_LEVEL_DEBUG, "initialise")
#define DARK_IDLOG_MESSAGE_SHUTDOWN(logger, id) DARK_DILOG_CSTRING((logger), (id), DARK_LOG_LEVEL_DEBUG, "shutdown")

#endif // !defined(___DARK___LOG_MESSAGE_H)
