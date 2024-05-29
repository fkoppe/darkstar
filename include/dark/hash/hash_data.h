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

#if !defined(___DARK___HASH_DATA_H)
#define ___DARK___HASH_DATA_H

typedef uint32_t (*Dark_Hash32)(size_t byte, const void* data);
typedef uint32_t (*Dark_Hash32_Seed)(size_t byte, const void* data, uint32_t seed);

typedef uint64_t (*Dark_Hash64)(size_t byte, const void* data);
typedef uint64_t (*Dark_Hash64_Seed)(size_t byte, const void* data, uint64_t seed);

#endif // !defined(___DARK___HASH_DATA_H)
