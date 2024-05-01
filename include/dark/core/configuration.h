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

#if !defined(___DARK___CONFIGURATION_H)
#define ___DARK___CONFIGURATION_H

#include <dark/core/essential.h>

#if defined(___DARK_DEBUG)
static const bool DARK_DEBUG_IS = true;
#else
static const bool DARK_DEBUG_IS = false;
#endif // defined(___DARK_DEBUG)

#if defined(___DARK_DEBINFO)
static const bool DARK_DEBINFO_IS = true;
#else
static const bool DARK_DEBINFO_IS = false;
#endif // defined(___DARK_DEBINFO)

#if defined(___DARK_RELEASE)
static const bool DARK_RELEASE_IS = true;
#else
static const bool DARK_RELEASE_IS = false;
#endif // defined(___DARK_RELEASE)

#if defined(___DARK_MINSIZE)
static const bool DARK_MINSIZE_IS = true;
#else
static const bool DARK_MINSIZE_IS = false;
#endif // defined(___DARK_MINSIZE)

#endif // !defined(___DARK___CONFIGURATION_H)

