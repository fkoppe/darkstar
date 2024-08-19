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

#if !defined(___DARK___DURATION_H)
#define ___DARK___DURATION_H

#include <dark/core/std.h>

#define DARK_DURATION_S_TO_MS(s) (s * DARK_KILO)
#define DARK_DURATION_S_TO_NS(s) (s * DARK_GIGA)
#define DARK_DURATION_MS_TO_S(s) (s / DARK_KILO)
#define DARK_DURATION_MS_TO_NS(s) (s * DARK_MEGA)
#define DARK_DURATION_NS_TO_S(s) (s / DARK_GIGA)
#define DARK_DURATION_NS_TO_MS(s) (s / DARK_MEGA)

size_t dark_duration_s_to_ms(size_t s);
size_t dark_duration_s_to_ns(size_t s);

size_t dark_duration_ms_to_s(size_t ms);
size_t dark_duration_ms_to_ns(size_t ms);

size_t dark_duration_ns_to_s(size_t ns);
size_t dark_duration_ns_to_ms(size_t ns);

#endif // !defined(___DARK___DURATION_H)

