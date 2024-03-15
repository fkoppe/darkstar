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

#if !defined(___DARK___THREAD_H)
#define ___DARK___THREAD_H

#include <dark/core/essential.h>

size_t dark_thread_struct_size(void);

void* dark_thread_new(void (* function), void* argument);
void dark_thread_delete(void* thread);

uint64_t dark_thread_id(void* thread);
uint64_t dark_thread_id_current(void);

bool dark_thread_joinable(void* thread);
void dark_thread_join(void* thread);
void dark_thread_detach(void* thread);

#endif // !defined(___DARK___THREAD_H)
