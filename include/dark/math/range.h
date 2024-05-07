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

#if !defined(___DARK___RANGE_H)
#define ___DARK___RANGE_H

#include <dark/core/essential.h>

bool dark_range_is_u(uint64_t u, uint64_t lower, uint64_t upper);
bool dark_range_is_i(int64_t i, int64_t lower, int64_t upper);

uint64_t dark_range_clamp_u(uint64_t u, uint64_t lower, uint64_t upper);
int64_t dark_range_clamp_i(int64_t i, int64_t lower, int64_t upper);

#endif // !defined(___DARK___RANGE_H)
