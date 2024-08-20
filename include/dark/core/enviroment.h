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

#if !defined(___DARK___ENVIROMENT_H)
#define ___DARK___ENVIROMENT_H

#include <dark/core/std.h>
#include <dark/core/so.h>

#if !defined(DARK_LIBRARY)
#define DARK_LIBRARY NULL
#endif // !defined(DARK_LIBRARY)

#if !defined(DARK_MODULE)
#define DARK_MODULE NULL
#endif // !defined(DARK_MODULE)

#if !defined(DARK_UNIT)
#define DARK_UNIT NULL
#endif // !defined(DARK_UNIT)

typedef struct Dark_Location Dark_Location;
struct Dark_Location
{
    const char* file;
    const char* func;
    intmax_t line;
    const char* date;
    const char* time;
};

typedef struct Dark_Library Dark_Library;
struct Dark_Library
{
    const char* name;
    uint32_t version;
    const char* configuration;
    const char* color;
};

void dark_location_print(Dark_So so, Dark_Location location);
void dark_library_print(Dark_So so, const Dark_Library* library, const char* module, const char* unit);

#endif // !defined(___DARK___ENVIROMENT_H)
