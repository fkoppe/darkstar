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

#if !defined(___DARK___PLATFORM_DATA_H)
#define ___DARK___PLATFORM_DATA_H

#include <dark/core/std.h>

#define DARK_PLATFORM_API "unknown"

#if defined(___DARK_WINDOWS)
#undef DARK_PLATFORM_API
#define DARK_PLATFORM_API "win32"
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX)
#undef DARK_PLATFORM_API
#define DARK_PLATFORM_API "linux"
#endif // defined(___DARK_LINUX)

#if defined(___DARK_DARWIN)
#undef DARK_PLATFORM_API
#define DARK_PLATFORM_API "darwin"
#endif // defined(___DARK_DARWIN)

static const Dark_Error DARK_ERROR_PLATFORM = { &DARK_ERROR_API, "platform", DARK_PLATFORM_API};

#endif // !defined(___DARK___PLATFORM_DATA_H)
