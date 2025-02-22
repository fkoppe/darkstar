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

#if !defined(___DARK___THREAD_H)
#define ___DARK___THREAD_H

#include <dark/core/message.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

static const Dark_Message DARK_MESSAGE_THREAD_JOINABLE_NOT = { NULL, "thread already joined or detached", NULL };
static const Dark_Message DARK_MESSAGE_THREAD_JOINABLE = { NULL, "thread was not joined or detached", NULL };

typedef struct Dark_Thread Dark_Thread;

typedef void (*Dark_Thread_Worker)(void* argument);

void dark_thread_construct(Dark_Allocator* allocator, Dark_Thread* thread, Dark_Thread_Worker function, void* argument);
void dark_thread_destruct(Dark_Thread* thread);

void* dark_thread_new(Dark_Allocator* allocator, Dark_Thread_Worker function, void* argument);
void dark_thread_delete(Dark_Thread* thread);

uint64_t dark_thread_id(Dark_Thread* thread);

bool dark_thread_joinable(Dark_Thread* thread);
void dark_thread_join(Dark_Thread* thread);
void dark_thread_detach(Dark_Thread* thread);

size_t dark_thread_struct_byte(void);

uint64_t dark_thread_current_id(void);

#endif // !defined(___DARK___THREAD_H)
