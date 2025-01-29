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

#if !defined(___DARK___CBUFFER_VIEW_H)
#define ___DARK___CBUFFER_VIEW_H

#include <dark/core/data.h>
#include <dark/core/std.h>
#include <dark/tool/array_view.h>
#include <dark/tool/buffer.h>

Dark_Array_View dark_cbuffer_view_to_array_view(Dark_Cbuffer_View cbuffer_view);

Dark_Buffer_View dark_cbuffer_view_to_buffer_view(Dark_Cbuffer_View cbuffer_view);

bool dark_cbuffer_view_terminated_is(Dark_Cbuffer_View cbuffer_view, size_t* cstring_lenght);

int8_t dark_cbuffer_view_compare(const Dark_Cbuffer_View* a, const Dark_Cbuffer_View* b);

#endif // !defined(___DARK___CBUFFER_VIEW_H)
