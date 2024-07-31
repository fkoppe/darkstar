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

#if !defined(___DARK___STOPWATCH_H)
#define ___DARK___STOPWATCH_H

#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Dark_Stopwatch Dark_Stopwatch;

typedef struct Dark_Stopwatch_Struct Dark_Stopwatch_Struct;
struct Dark_Stopwatch_Struct
{
    uint64_t time;
    uint64_t stamp;
    bool running_is;
};

size_t dark_stopwatch_struct_byte(void);

Dark_Stopwatch* dark_stopwatch_new(Dark_Allocator* allocator);
Dark_Stopwatch* dark_stopwatch_new_start(Dark_Allocator* allocator);

void dark_stopwatch_delete(Dark_Allocator* allocator, Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_delete_ns(Dark_Allocator* allocator, Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_delete_ms(Dark_Allocator* allocator, Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_delete_s(Dark_Allocator* allocator, Dark_Stopwatch* stopwatch);

void dark_stopwatch_start(Dark_Stopwatch* stopwatch);
void dark_stopwatch_stop(Dark_Stopwatch* stopwatch);

void dark_stopwatch_reset(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_reset_ns(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_reset_ms(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_reset_s(Dark_Stopwatch* stopwatch);

void dark_stopwatch_restart(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_restart_ns(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_restart_ms(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_restart_s(Dark_Stopwatch* stopwatch);

bool dark_stopwatch_running_is(Dark_Stopwatch* stopwatch);

uint64_t dark_stopwatch_ns(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_ms(Dark_Stopwatch* stopwatch);
uint64_t dark_stopwatch_s(Dark_Stopwatch* stopwatch);

#endif // !defined(___DARK___STOPWATCH_H)
