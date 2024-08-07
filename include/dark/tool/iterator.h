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

#if !defined(___DARK___ITERATOR_H)
#define ___DARK___ITERATOR_H

#include <dark/core/error.h>
#include <dark/core/std.h>

typedef struct Dark_Iterator Dark_Iterator;

typedef struct Dark_Iterator_Struct Dark_Iterator_Struct;
struct Dark_Iterator_Struct
{
    bool (*next_is)(void* context);
    void* (*next)(void* context);
    void* context;
};

static const Dark_Error DARK_ERROR_ITERATOR = { &DARK_ERROR_LOGIC, "iterator", "next not available" };

bool dark_iterator_next_is(Dark_Iterator* iterator);
void* dark_iterator_next(Dark_Iterator* iterator);

#endif // !defined(___DARK___ITERATOR_H)
