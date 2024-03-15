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

#include <dark/core/essential.h>

size_t dark_stopwatch_struct_size(void);

void* dark_stopwatch_new(void);
void* dark_stopwatch_new_start(void);

void dark_stopwatch_delete(void* stopwatch);
uint64_t dark_stopwatch_delete_ns(void* stopwatch);
uint64_t dark_stopwatch_delete_ms(void* stopwatch);
uint64_t dark_stopwatch_delete_s(void* stopwatch);

void dark_stopwatch_start(void* stopwatch);
void dark_stopwatch_stop(void* stopwatch);

void dark_stopwatch_reset(void* stopwatch);
uint64_t dark_stopwatch_reset_ns(void* stopwatch);
uint64_t dark_stopwatch_reset_ms(void* stopwatch);
uint64_t dark_stopwatch_reset_s(void* stopwatch);

void dark_stopwatch_restart(void* stopwatch);
uint64_t dark_stopwatch_restart_ns(void* stopwatch);
uint64_t dark_stopwatch_restart_ms(void* stopwatch);
uint64_t dark_stopwatch_restart_s(void* stopwatch);

bool dark_stopwatch_running_is(void* stopwatch);

uint64_t dark_stopwatch_ns(void* stopwatch);
uint64_t dark_stopwatch_ms(void* stopwatch);
uint64_t dark_stopwatch_s(void* stopwatch);

#endif // !defined(___DARK___STOPWATCH_H)
