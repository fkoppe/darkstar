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

#include "time_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/platform/platform.h>
#include <dark/time/time.h>

#undef DARK_UNIT
#define DARK_UNIT "stopwatch"

size_t dark_stopwatch_struct_size(void)
{
    return sizeof(Dark_Stopwatch_Struct);
}

void dark_stopwatch_construct(Dark_Allocator* const allocator_, Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    stopwatch->allocator = allocator_;
    stopwatch->time = 0;
    stopwatch->stamp = 0;
    stopwatch->running_is = false;
}

void dark_stopwatch_construct_start(Dark_Allocator* const allocator_, Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    stopwatch->allocator = allocator_;
    stopwatch->time = 0;
    stopwatch->stamp = dark_clock_ns();
    stopwatch->running_is = true;
}

void dark_stopwatch_destruct(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    //nothing
}

uint64_t dark_stopwatch_destruct_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    const uint64_t ns = dark_stopwatch_ns((Dark_Stopwatch*)stopwatch);

    dark_stopwatch_destruct((Dark_Stopwatch*)stopwatch);

    return ns;
}

uint64_t dark_stopwatch_destruct_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_destruct_ns((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

uint64_t dark_stopwatch_destruct_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_destruct_ms((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

Dark_Stopwatch* dark_stopwatch_new(Dark_Allocator* const allocator_)
{
    Dark_Stopwatch_Struct* const stopwatch = dark_malloc(allocator_, sizeof(*stopwatch));
    DARK_ASSERT(NULL != stopwatch, DARK_ERROR_ALLOCATION);

    dark_stopwatch_construct(allocator_, (Dark_Stopwatch*)stopwatch);

    return (Dark_Stopwatch*)stopwatch;
}

Dark_Stopwatch* dark_stopwatch_new_start(Dark_Allocator* const allocator_)
{
    Dark_Stopwatch_Struct* const stopwatch = dark_malloc(allocator_, sizeof(*stopwatch));
    DARK_ASSERT(NULL != stopwatch, DARK_ERROR_ALLOCATION);

    dark_stopwatch_construct_start(allocator_, (Dark_Stopwatch*)stopwatch);

    return (Dark_Stopwatch*)stopwatch;
}

void dark_stopwatch_delete(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    dark_free(stopwatch->allocator, stopwatch, sizeof(*stopwatch));
}

uint64_t dark_stopwatch_delete_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    const uint64_t ns = dark_stopwatch_ns((Dark_Stopwatch*)stopwatch);

    dark_stopwatch_delete((Dark_Stopwatch*)stopwatch);

    return ns;
}

uint64_t dark_stopwatch_delete_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_delete_ns((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

uint64_t dark_stopwatch_delete_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_delete_ms((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

void dark_stopwatch_start(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    if (!stopwatch->running_is)
    {
        stopwatch->stamp = dark_clock_ns();
        stopwatch->running_is = true;
    }
}

void dark_stopwatch_stop(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    if (stopwatch->running_is)
    {
        stopwatch->time += (dark_clock_ns() - stopwatch->stamp);
        stopwatch->running_is = false;
    }
}

void dark_stopwatch_reset(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    stopwatch->time = 0;
    stopwatch->stamp = 0;
    stopwatch->running_is = false;
}

uint64_t dark_stopwatch_reset_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    const uint64_t ns = dark_stopwatch_ns((Dark_Stopwatch*)stopwatch);

    dark_stopwatch_reset((Dark_Stopwatch*)stopwatch);

    return ns;
}

uint64_t dark_stopwatch_reset_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_reset_ns((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

uint64_t dark_stopwatch_reset_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_reset_ns((Dark_Stopwatch*)stopwatch) / DARK_GIGA;
}

void dark_stopwatch_restart(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    stopwatch->time = 0;
    stopwatch->stamp = dark_clock_ns();
    stopwatch->running_is = true;
}

uint64_t dark_stopwatch_restart_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    const uint64_t ns = dark_stopwatch_ns((Dark_Stopwatch*)stopwatch);

    dark_stopwatch_restart((Dark_Stopwatch*)stopwatch);

    return ns;
}

uint64_t dark_stopwatch_restart_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_restart_ns((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

uint64_t dark_stopwatch_restart_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_restart_ns((Dark_Stopwatch*)stopwatch) / DARK_GIGA;
}

bool dark_stopwatch_running_is(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return stopwatch->running_is;
}

uint64_t dark_stopwatch_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    if (stopwatch->running_is)
    {
        return stopwatch->time + (dark_clock_ns() - stopwatch->stamp);
    }
    else
    {
        return stopwatch->time;
    }
}

uint64_t dark_stopwatch_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_ns((Dark_Stopwatch*)stopwatch) / DARK_MEGA;
}

uint64_t dark_stopwatch_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    Dark_Stopwatch_Struct* const stopwatch = (Dark_Stopwatch_Struct* )stopwatch_;

    return dark_stopwatch_ns((Dark_Stopwatch*)stopwatch) / DARK_GIGA;
}
