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

#if !defined(___DARK___CBUFFER_H)
#define ___DARK___CBUFFER_H

#include <dark/core/std.h>

typedef struct Dark_Cbuffer Dark_Cbuffer;
struct Dark_Cbuffer
{
    char* data;
    size_t size;
};

typedef struct Dark_Cbuffer_View Dark_Cbuffer_View;
struct Dark_Cbuffer_View
{
    const char* data;
    size_t size;
};

bool dark_cbuffer_terminated_is(Dark_Cbuffer cbuffer, size_t* cstring_lenght);
bool dark_cbuffer_view_terminated_is(Dark_Cbuffer_View cbuffer_view, size_t* cstring_lenght);

Dark_Cbuffer_View dark_cbuffer_view(Dark_Cbuffer cbuffer);

int8_t dark_cbuffer_compare(const Dark_Cbuffer* a, const Dark_Cbuffer* b);
int8_t dark_cbuffer_view_compare(const Dark_Cbuffer_View* a, const Dark_Cbuffer_View* b);

#endif // !defined(___DARK___CBUFFER_H)
