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

#if !defined(___DARK___LINEAR_QUEUE_HELPER_H)
#define ___DARK___LINEAR_QUEUE_HELPER_H

#include <dark/core/std.h>
#include <dark/container/linear_queue.h>

typedef struct Dark_Linear_Queue_Iterator_Context Dark_Linear_Queue_Iterator_Context;
struct Dark_Linear_Queue_Iterator_Context
{
    Dark_Linear_Queue* queue;
    size_t index;
};

bool dark_linear_queue_iterator_done_is(Dark_Linear_Queue_Iterator_Context* context);
void* dark_linear_queue_iterator_next(Dark_Linear_Queue_Iterator_Context* context);
void* dark_linear_queue_iterator_peek(Dark_Linear_Queue_Iterator_Context* context);
void dark_linear_queue_iterator_reset(Dark_Linear_Queue_Iterator_Context* context);
size_t dark_linear_queue_iterator_skip(Dark_Linear_Queue_Iterator_Context* context, size_t count);

#endif // !defined(___DARK___LINEAR_QUEUE_HELPER_H)
