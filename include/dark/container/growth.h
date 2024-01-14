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

#if !defined(___DARK___GROWTH_H)
#define ___DARK___GROWTH_H

#include <dark/core/error.h>
#include <dark/core/essential.h>

#define DARK_GROWTH_VALUE(old, growth) \
DARK_MIN(growth.max != 0 ? growth.max : DARK_MAX(growth.min, DARK_MAX(1, growth.factor) * DARK_MAX(1, old)), DARK_MAX(growth.min, growth.factor * DARK_MAX(1, old)))

#define DARK_GROWTH_APPLIED(old, growth) \
(old + DARK_GROWTH_VALUE(old, growth))

typedef struct Dark_Growth
{
    float factor;
    size_t min;
    size_t max;
} Dark_Growth;

static const Dark_Growth DARK_GROWTH_STANDARD = { 0.5f, 1, 0 };
static const Dark_Growth DARK_GROWTH_QUADRATIC = { 1.0f, 1, 0 };

static const Dark_Error DARK_ERROR_GROWTH = { &DARK_ERROR_LOGIC, "growth", "unable to grow/shrink" };

#endif // !defined(___DARK___GROWTH_H)
