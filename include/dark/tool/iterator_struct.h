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

#if !defined(___DARK___ITERATOR_STRUCT_H)
#define ___DARK___ITERATOR_STRUCT_H

#include <dark/core/error.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>
#include <dark/tool/iterator.h>

struct Dark_Iterator
{
    Dark_Allocator* allocator;
    size_t byte;
    void* context;
    bool (*next_is)(void* context);
    void* (*next)(void* context);
    void* (*peek)(void* context);
    void (*reset)(void* context);
    size_t (*skip)(void* context, size_t count);
};

#endif // !defined(___DARK___ITERATOR_STRUCT_H)
