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
#include <dark/time/stopwatch_struct.h>
#include <dark/time/time.h>

#undef DARK_UNIT
#define DARK_UNIT "stopwatch"

void dark_stopwatch_construct(Dark_Allocator* const allocator_, Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    stopwatch_->allocator = allocator_;
    stopwatch_->time = 0;
    stopwatch_->stamp = 0;
    stopwatch_->running_is = false;
}

void dark_stopwatch_construct_start(Dark_Allocator* const allocator_, Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    stopwatch_->allocator = allocator_;
    stopwatch_->time = 0;
    stopwatch_->stamp = dark_clock_ns();
    stopwatch_->running_is = true;
}

void dark_stopwatch_destruct(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    //nothing
}

uint64_t dark_stopwatch_destruct_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    const uint64_t ns = dark_stopwatch_ns(stopwatch_);

    dark_stopwatch_destruct(stopwatch_);

    return ns;
}

uint64_t dark_stopwatch_destruct_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ns_to_ms(dark_stopwatch_destruct_ns(stopwatch_));
}

uint64_t dark_stopwatch_destruct_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ms_to_s(dark_stopwatch_destruct_ms(stopwatch_));
}

Dark_Stopwatch* dark_stopwatch_new(Dark_Allocator* const allocator_)
{
    Dark_Stopwatch* const stopwatch = dark_malloc(allocator_, sizeof(*stopwatch));
    DARK_ASSERT(NULL != stopwatch, DARK_ERROR_ALLOCATION);

    dark_stopwatch_construct(allocator_, stopwatch);

    return stopwatch;
}

Dark_Stopwatch* dark_stopwatch_new_start(Dark_Allocator* const allocator_)
{
    Dark_Stopwatch* const stopwatch = dark_malloc(allocator_, sizeof(*stopwatch));
    DARK_ASSERT(NULL != stopwatch, DARK_ERROR_ALLOCATION);

    dark_stopwatch_construct_start(allocator_, stopwatch);

    return stopwatch;
}

void dark_stopwatch_delete(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    dark_free(stopwatch_->allocator, stopwatch_, sizeof(*stopwatch_));
}

uint64_t dark_stopwatch_delete_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    const uint64_t ns = dark_stopwatch_ns(stopwatch_);

    dark_stopwatch_delete(stopwatch_);

    return ns;
}

uint64_t dark_stopwatch_delete_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ns_to_ms(dark_stopwatch_delete_ns(stopwatch_));
}

uint64_t dark_stopwatch_delete_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ms_to_s(dark_stopwatch_delete_ms(stopwatch_));
}

void dark_stopwatch_start(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    if (!stopwatch_->running_is)
    {
        stopwatch_->stamp = dark_clock_ns();
        stopwatch_->running_is = true;
    }
}

void dark_stopwatch_stop(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    if (stopwatch_->running_is)
    {
        stopwatch_->time += (dark_clock_ns() - stopwatch_->stamp);
        stopwatch_->running_is = false;
    }
}

void dark_stopwatch_reset(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    stopwatch_->time = 0;
    stopwatch_->stamp = 0;
    stopwatch_->running_is = false;
}

uint64_t dark_stopwatch_reset_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    const uint64_t ns = dark_stopwatch_ns(stopwatch_);

    dark_stopwatch_reset(stopwatch_);

    return ns;
}

uint64_t dark_stopwatch_reset_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ns_to_ms(dark_stopwatch_reset_ns(stopwatch_));
}

uint64_t dark_stopwatch_reset_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ms_to_s(dark_stopwatch_reset_ms(stopwatch_));
}

void dark_stopwatch_restart(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    stopwatch_->time = 0;
    stopwatch_->stamp = dark_clock_ns();
    stopwatch_->running_is = true;
}

uint64_t dark_stopwatch_restart_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    const uint64_t ns = dark_stopwatch_ns(stopwatch_);

    dark_stopwatch_restart(stopwatch_);

    return ns;
}

uint64_t dark_stopwatch_restart_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ns_to_ms(dark_stopwatch_restart_ns(stopwatch_));
}

uint64_t dark_stopwatch_restart_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ms_to_s(dark_stopwatch_restart_ms(stopwatch_));
}

bool dark_stopwatch_running_is(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return stopwatch_->running_is;
}

uint64_t dark_stopwatch_ns(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    if (stopwatch_->running_is)
    {
        return stopwatch_->time + (dark_clock_ns() - stopwatch_->stamp);
    }
    else
    {
        return stopwatch_->time;
    }
}

uint64_t dark_stopwatch_ms(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ns_to_ms(dark_stopwatch_ns(stopwatch_));
}

uint64_t dark_stopwatch_s(Dark_Stopwatch* const stopwatch_)
{
    DARK_ASSERT(NULL != stopwatch_, DARK_ERROR_NULL);

    return dark_duration_ms_to_s(dark_stopwatch_ms(stopwatch_));
}

size_t dark_stopwatch_struct_byte(void)
{
    return sizeof(Dark_Stopwatch);
}
