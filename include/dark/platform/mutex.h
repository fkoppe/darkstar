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

#if !defined(___DARK___MUTEX_H)
#define ___DARK___MUTEX_H

#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Dark_Mutex Dark_Mutex;

size_t dark_mutex_struct_byte(void);

void dark_mutex_construct(Dark_Allocator* allocator, Dark_Mutex* mutex);
void dark_mutex_destruct(Dark_Allocator* allocator, Dark_Mutex* mutex);

Dark_Mutex* dark_mutex_new(Dark_Allocator* allocator);
void dark_mutex_delete(Dark_Mutex* mutex);

bool dark_mutex_trylock(Dark_Mutex* mutex);
void dark_mutex_lock(Dark_Mutex* mutex);
void dark_mutex_unlock(Dark_Mutex* mutex);

#endif // !defined(___DARK___MUTEX_H)
