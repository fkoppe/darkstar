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

#if !defined(___DARK___CBUFFER_H)
#define ___DARK___CBUFFER_H

#include <dark/char/cbuffer_view.h>
#include <dark/char/cstring.h>
#include <dark/core/std.h>
#include <dark/tool/array.h>
#include <dark/tool/array_view.h>
#include <dark/tool/buffer.h>
#include <dark/tool/buffer_view.h>

typedef struct Dark_Cbuffer Dark_Cbuffer;
struct Dark_Cbuffer
{
    size_t size;
    char* data;
};

Dark_Cbuffer_View dark_cbuffer_to_view(Dark_Cbuffer cbuffer);

Dark_Array dark_cbuffer_to_array(Dark_Cbuffer cbuffer);
Dark_Array_View dark_cbuffer_to_array_view(Dark_Cbuffer cbuffer);

Dark_Buffer dark_cbuffer_to_buffer(Dark_Cbuffer cbuffer);
Dark_Buffer_View dark_cbuffer_to_buffer_view(Dark_Cbuffer cbuffer);

bool dark_cbuffer_terminated_is(Dark_Cbuffer cbuffer, size_t* cstring_lenght);

int8_t dark_cbuffer_compare(const Dark_Cbuffer* a, const Dark_Cbuffer* b);

#endif // !defined(___DARK___CBUFFER_H)
