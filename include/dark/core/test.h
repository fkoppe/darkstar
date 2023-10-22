/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

#if !defined(___DARK___TEST_H)
#define ___DARK___TEST_H

#include <dark/core/essential.h>

#define DARK_TEST(condition) if(!(condition)) dark_test((#condition), 0, NULL, 0, 0, NULL)
#define DARK_TEST_INT(condition, integer) if(!(condition)) dark_test((#condition), 1, (#integer), (integer), 0, NULL)
#define DARK_TEST_UINT(condition, uinteger) if(!(condition)) dark_test((#condition), 2, (#uinteger), 0, (uinteger), NULL)
#define DARK_TEST_CSTRING(condition, cstring) if(!(condition)) dark_test((#condition), 3, (#cstring), 0, 0, (cstring))

void dark_test(const char* condition, size_t num, const char* name, int64_t integer, uint64_t uinteger, const char* cstring);

#endif // !defined(___DARK___TEST_H)
