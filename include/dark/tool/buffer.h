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

#if !defined(___DARK___BUFFER_H)
#define ___DARK___BUFFER_H

#include <dark/core/std.h>
#include <dark/tool/foreach.h>
#include <dark/tool/buffer_view.h>

typedef struct Dark_Buffer Dark_Buffer;
struct Dark_Buffer
{
    size_t byte;
    void* data;
};

Dark_Buffer_View dark_buffer_to_view(Dark_Buffer buffer);

void dark_buffer_foreach(Dark_Buffer buffer, void* context, Dark_Foreach foreach);

#endif // !defined(___DARK___ARRAY_H)
