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

#if !defined(___DARK___CONTAINER_DATA_H)
#define ___DARK___CONTAINER_DATA_H

#include <dark/core/error.h>
#include <dark/core/essential.h>

#if !defined(DARK_CONTAINER_SIZE_MAX)
#define DARK_CONTAINER_SIZE_MAX (1024*16)
#endif // !defined(DARK_CONTAINER_SIZE_MAX)

static const Dark_Error DARK_ERROR_CONTAINER_INTEGRITY = { &DARK_ERROR_LOGIC, "container_integrity", NULL};
static const Dark_Error DARK_ERROR_CONTAINER_EMPTY = { &DARK_ERROR_LOGIC, "container_empty", "size has to be >0"};

static const Dark_Error DARK_ERROR_CONTAINER_INDEX = { &DARK_ERROR_RANGE, "container_index", "index has to be <size"};

#endif // !defined(___DARK___CONTAINER_DATA_H)
