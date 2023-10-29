/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

#include "allocation_override.h"
#include "profile_module.h"

#include <dark/core/core.h>
#include <dark/profile/profile.h>

#undef DARK_UNIT
#define DARK_UNIT "memory_profiler"

#undef malloc
#undef realloc
#undef calloc
#undef free

typedef struct Dark_Allocation_Info
{
    void* adress;
    size_t size;
    struct
    {
        const char* func;
        const char* file;
        size_t line;
        const char* date;
        const char* time;
        const Dark_Library* library;
        const char* module;
        const char* unit;
    } at;
} Dark_Allocation_Info;

typedef struct Dark_Memory_Profiler
{
    bool initialised_is;
    bool full_reached_is;
    Dark_Memory_Profile_Level level;
    bool assert_pointer_is;
    Dark_Allocation_Info* allocation_arr;
    Dark_Memory_Info all;
    Dark_Memory_Info own;
} Dark_Memory_Profiler;

static Dark_Memory_Profiler MEMORY_PROFILER = { .initialised_is = false };

void dark_memory_profiler_initialise(const Dark_Memory_Profile_Level level_, const bool assert_pointer_is_)
{
    DARK_ASSERT(level_ < ___DARK_MEMORY_PROFILE_LEVEL_MAX, DARK_ERROR_ENUM);
    //assert_pointer_is_

    if(MEMORY_PROFILER.initialised_is || level_ < DARK_MEMORY_PROFILE_LEVEL_REDUCED)
    {
        return;
    }

    MEMORY_PROFILER.initialised_is = true;
    MEMORY_PROFILER.full_reached_is = false;
    MEMORY_PROFILER.level = level_;
    MEMORY_PROFILER.assert_pointer_is = assert_pointer_is_;

    size_t usage_own = 0;
    size_t count_own_sum = 0;
    if(MEMORY_PROFILER.level >= DARK_MEMORY_PROFILE_LEVEL_FULL)
    {
        usage_own += sizeof(*MEMORY_PROFILER.allocation_arr);
        count_own_sum++;

        MEMORY_PROFILER.allocation_arr = malloc(usage_own);
        DARK_ASSERT(NULL != MEMORY_PROFILER.allocation_arr, DARK_ERROR_ALLOCATION);

        MEMORY_PROFILER.allocation_arr[0].adress = MEMORY_PROFILER.allocation_arr;
        MEMORY_PROFILER.allocation_arr[0].size = usage_own;
        MEMORY_PROFILER.allocation_arr[0].at.file = __FILE__;
        MEMORY_PROFILER.allocation_arr[0].at.func = __func__;
        MEMORY_PROFILER.allocation_arr[0].at.line = 0;
        MEMORY_PROFILER.allocation_arr[0].at.date = __DATE__;
        MEMORY_PROFILER.allocation_arr[0].at.time = __TIME__;
        MEMORY_PROFILER.allocation_arr[0].at.library = DARK_LIBRARY;
        MEMORY_PROFILER.allocation_arr[0].at.module = DARK_MODULE;
        MEMORY_PROFILER.allocation_arr[0].at.unit = DARK_UNIT;
    }
    else
    {
        MEMORY_PROFILER.allocation_arr = NULL;
    }

    MEMORY_PROFILER.own.current.count = count_own_sum;
    MEMORY_PROFILER.own.current.usage = usage_own;
    MEMORY_PROFILER.own.total.count = MEMORY_PROFILER.own.current.count;
    MEMORY_PROFILER.own.total.usage = MEMORY_PROFILER.own.current.usage;
    MEMORY_PROFILER.own.peak.count = MEMORY_PROFILER.own.current.count;
    MEMORY_PROFILER.own.peak.usage = MEMORY_PROFILER.own.current.usage;

    MEMORY_PROFILER.all.current.count = MEMORY_PROFILER.own.current.count;
    MEMORY_PROFILER.all.current.usage = MEMORY_PROFILER.own.current.usage;
    MEMORY_PROFILER.all.total.count = MEMORY_PROFILER.own.current.count;
    MEMORY_PROFILER.all.total.usage = MEMORY_PROFILER.own.current.usage;
    MEMORY_PROFILER.all.peak.count = MEMORY_PROFILER.own.current.count;
    MEMORY_PROFILER.all.peak.usage = MEMORY_PROFILER.own.current.usage;
}

void dark_memory_profiler_shutdown(const bool print_error_is_)
{
    //print_error_is_

    if(!MEMORY_PROFILER.initialised_is)
    {
        return;
    }

    //TODO

    if(MEMORY_PROFILER.all.current.usage > 0)
    {
        MEMORY_PROFILER.all.current.count -= MEMORY_PROFILER.own.current.count;
        MEMORY_PROFILER.all.current.usage -= MEMORY_PROFILER.own.current.usage;

        MEMORY_PROFILER.own.current.count = 0;
        MEMORY_PROFILER.own.current.usage = 0;

        free(MEMORY_PROFILER.allocation_arr);
    }
}

void dark_memory_profiler_print_info_stdout()
{
    DARK_ASSERT(MEMORY_PROFILER.initialised_is, DARK_ERROR_NOSTATE);

    //TODO
}

Dark_Memory_Info dark_memory_profiler_info_all_get()
{
    DARK_ASSERT(MEMORY_PROFILER.initialised_is, DARK_ERROR_NOSTATE);

    return MEMORY_PROFILER.all;
}

Dark_Memory_Info dark_memory_profiler_info_own_get()
{
    DARK_ASSERT(MEMORY_PROFILER.initialised_is, DARK_ERROR_NOSTATE);

    return MEMORY_PROFILER.own;
}

void* dark_memory_profiler_malloc(const size_t size_, const char* const file_, const char* const func_, const int64_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const module_, const char* const unit_)
{
    if (!(size_ > 0 || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "NULL != pointer", &DARK_ERROR_NULL, "tried to malloc with size =0 from...");
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != func_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != line_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != date_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != time_, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_

    void* const temp = malloc(size_);
    DARK_ASSERT(NULL != temp || !MEMORY_PROFILER.assert_pointer_is, DARK_ERROR_ALLOCATION);

    if(NULL == temp)
    {
        return temp;
    }

    if(!MEMORY_PROFILER.initialised_is)
    {
        return temp;
    }

    size_t usage_own = 0;
    size_t usage_own_sum = 0;
    size_t count_own_sum = 0;
    if(MEMORY_PROFILER.level >= DARK_MEMORY_PROFILE_LEVEL_FULL)
    {
        if(MEMORY_PROFILER.all.current.count + 1 < DARK_MEMORY_PROFILER_INFO_COUNT_MAX)
        {
            usage_own = sizeof(*MEMORY_PROFILER.allocation_arr) * (MEMORY_PROFILER.all.current.count + 1);
            usage_own_sum = sizeof(*MEMORY_PROFILER.allocation_arr);
            count_own_sum++;

            MEMORY_PROFILER.allocation_arr = realloc(MEMORY_PROFILER.allocation_arr, usage_own);
            DARK_ASSERT(NULL != MEMORY_PROFILER.allocation_arr, DARK_ERROR_ALLOCATION);

            MEMORY_PROFILER.allocation_arr[0].adress = MEMORY_PROFILER.allocation_arr;
            MEMORY_PROFILER.allocation_arr[0].size = usage_own;
            MEMORY_PROFILER.allocation_arr[0].at.file = __FILE__;
            MEMORY_PROFILER.allocation_arr[0].at.func = __func__;
            MEMORY_PROFILER.allocation_arr[0].at.line = 0;
            MEMORY_PROFILER.allocation_arr[0].at.date = __DATE__;
            MEMORY_PROFILER.allocation_arr[0].at.time = __TIME__;
            MEMORY_PROFILER.allocation_arr[0].at.library = DARK_LIBRARY;
            MEMORY_PROFILER.allocation_arr[0].at.module = DARK_MODULE;
            MEMORY_PROFILER.allocation_arr[0].at.unit = DARK_UNIT;

            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].adress = temp;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].size = size_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.file = file_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.func = func_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.line = line_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.date = date_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.time = time_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.library = library_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.module = module_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.unit = unit_;
        }
        else
        {
            MEMORY_PROFILER.full_reached_is = true;
        }
    }

    MEMORY_PROFILER.own.current.usage += usage_own_sum;
    MEMORY_PROFILER.own.total.count += count_own_sum;
    MEMORY_PROFILER.own.total.usage += usage_own;
    MEMORY_PROFILER.own.peak.usage = DARK_MAX(MEMORY_PROFILER.own.peak.usage, MEMORY_PROFILER.own.current.usage);

    MEMORY_PROFILER.all.current.usage += usage_own_sum + size_;
    MEMORY_PROFILER.all.current.count += 1;
    MEMORY_PROFILER.all.total.count += count_own_sum + 1;
    MEMORY_PROFILER.all.total.usage += usage_own + size_;
    MEMORY_PROFILER.all.peak.count = DARK_MAX(MEMORY_PROFILER.all.peak.count, MEMORY_PROFILER.all.current.count);
    MEMORY_PROFILER.all.peak.usage = DARK_MAX(MEMORY_PROFILER.all.peak.usage, MEMORY_PROFILER.all.current.usage);

    return temp;
}

void* dark_memory_profiler_realloc(void* const pointer_, const size_t size_, const char* const file_, const char* const func_, const int64_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const module_, const char* const unit_)
{
    if (!(NULL != pointer_ || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "NULL != pointer", &DARK_ERROR_NULL, "tried to realloc with pointer =NULL from...");
    if (!(size_ > 0 || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "NULL != pointer", &DARK_ERROR_NULL, "tried to malloc with size =0 from...");
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != func_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != line_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != date_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != time_, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_

    void* const temp = realloc(pointer_, size_);
    DARK_ASSERT(NULL != temp || !MEMORY_PROFILER.assert_pointer_is, DARK_ERROR_ALLOCATION);

    if(NULL == temp)
    {
        return temp;
    }

    if(!MEMORY_PROFILER.initialised_is)
    {
        return temp;
    }

    int64_t usage_dif = 0;
    if(MEMORY_PROFILER.level >= DARK_MEMORY_PROFILE_LEVEL_FULL)
    {
        for(size_t i = 0; i < MEMORY_PROFILER.all.current.count; i++)
        {
            if(MEMORY_PROFILER.allocation_arr[i].adress == pointer_)
            {
                usage_dif = size_ - MEMORY_PROFILER.allocation_arr[i].size;

                MEMORY_PROFILER.allocation_arr[i].adress = temp;
                MEMORY_PROFILER.allocation_arr[i].size = size_;
                MEMORY_PROFILER.allocation_arr[i].at.file = file_;
                MEMORY_PROFILER.allocation_arr[i].at.func = func_;
                MEMORY_PROFILER.allocation_arr[i].at.line = line_;
                MEMORY_PROFILER.allocation_arr[i].at.date = date_;
                MEMORY_PROFILER.allocation_arr[i].at.time = time_;
                MEMORY_PROFILER.allocation_arr[i].at.library = library_;
                MEMORY_PROFILER.allocation_arr[i].at.module = module_;
                MEMORY_PROFILER.allocation_arr[i].at.unit = unit_;
            }
        }
    }

    MEMORY_PROFILER.all.current.usage += usage_dif;
    MEMORY_PROFILER.all.total.count += 1;
    MEMORY_PROFILER.all.total.usage += size_;
    MEMORY_PROFILER.all.peak.usage = DARK_MAX(MEMORY_PROFILER.all.peak.usage, MEMORY_PROFILER.all.current.usage);

    return temp;
}

void* dark_memory_profiler_calloc(const size_t count_, const size_t size_, const char* const file_, const char* const func_, const int64_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const module_, const char*const unit_)
{
    if (!(count_ > 0 || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "count > 0", &DARK_ERROR_NULL, "tried to calloc with number =0 from...");
    if (!(size_ > 0 || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "size > 0", &DARK_ERROR_NULL, "tried to calloc with size =0 from...");
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != func_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != line_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != date_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != time_, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_

    void* const temp = calloc(count_, size_);
    DARK_ASSERT(NULL != temp || !MEMORY_PROFILER.assert_pointer_is, DARK_ERROR_ALLOCATION);

    if(NULL == temp)
    {
        return temp;
    }

    if(!MEMORY_PROFILER.initialised_is)
    {
        return temp;
    }

    size_t usage_own = 0;
    size_t usage_own_sum = 0;
    size_t count_own_sum = 0;
    if(MEMORY_PROFILER.level >= DARK_MEMORY_PROFILE_LEVEL_FULL)
    {
        if(MEMORY_PROFILER.all.current.count + 1 < DARK_MEMORY_PROFILER_INFO_COUNT_MAX)
        {
            usage_own = sizeof(*MEMORY_PROFILER.allocation_arr) * (MEMORY_PROFILER.all.current.count + 1);
            usage_own_sum = sizeof(*MEMORY_PROFILER.allocation_arr);
            count_own_sum++;

            MEMORY_PROFILER.allocation_arr = realloc(MEMORY_PROFILER.allocation_arr, usage_own);
            DARK_ASSERT(NULL != MEMORY_PROFILER.allocation_arr, DARK_ERROR_ALLOCATION);

            MEMORY_PROFILER.allocation_arr[0].adress = MEMORY_PROFILER.allocation_arr;
            MEMORY_PROFILER.allocation_arr[0].size = usage_own;
            MEMORY_PROFILER.allocation_arr[0].at.file = __FILE__;
            MEMORY_PROFILER.allocation_arr[0].at.func = __func__;
            MEMORY_PROFILER.allocation_arr[0].at.line = 0;
            MEMORY_PROFILER.allocation_arr[0].at.date = __DATE__;
            MEMORY_PROFILER.allocation_arr[0].at.time = __TIME__;
            MEMORY_PROFILER.allocation_arr[0].at.library = DARK_LIBRARY;
            MEMORY_PROFILER.allocation_arr[0].at.module = DARK_MODULE;
            MEMORY_PROFILER.allocation_arr[0].at.unit = DARK_UNIT;

            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].adress = temp;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].size = size_ * count_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.file = file_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.func = func_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.line = line_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.date = date_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.time = time_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.library = library_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.module = module_;
            MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count].at.unit = unit_;
        }
        else
        {
            MEMORY_PROFILER.full_reached_is = true;
        }
    }

    MEMORY_PROFILER.own.current.usage += usage_own_sum;
    MEMORY_PROFILER.own.total.count += count_own_sum;
    MEMORY_PROFILER.own.total.usage += usage_own;
    MEMORY_PROFILER.own.peak.usage = DARK_MAX(MEMORY_PROFILER.own.peak.usage, MEMORY_PROFILER.own.current.usage);

    MEMORY_PROFILER.all.current.usage += usage_own_sum + size_ * count_;
    MEMORY_PROFILER.all.current.count += 1;
    MEMORY_PROFILER.all.total.count += count_own_sum + 1;
    MEMORY_PROFILER.all.total.usage += usage_own + size_ * count_;
    MEMORY_PROFILER.all.peak.count = DARK_MAX(MEMORY_PROFILER.all.peak.count, MEMORY_PROFILER.all.current.count);
    MEMORY_PROFILER.all.peak.usage = DARK_MAX(MEMORY_PROFILER.all.peak.usage, MEMORY_PROFILER.all.current.usage);

    return temp;
}

void dark_memory_profiler_free(void* const pointer_, const char* const file_, const char* const func_, const int64_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const module_, const char* const unit_)
{
    if (!(NULL != pointer_ || !MEMORY_PROFILER.assert_pointer_is)) dark_assert(file_, func_, line_, date_, time_, library_, module_, unit_, "NULL != pointer", &DARK_ERROR_NULL, "tried to free NULL from...");
    DARK_ASSERT(NULL != file_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != func_, DARK_ERROR_NULL);
    DARK_ASSERT(0 != line_, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != date_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != time_, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_

    free(pointer_);

    if(!MEMORY_PROFILER.initialised_is)
    {
        return;
    }

    if(NULL == MEMORY_PROFILER.allocation_arr)
    {
        return;
    }

    size_t usage_sum = 0;
    size_t usage_own = 0;
    size_t usage_own_sum = 0;
    size_t count_own_sum = 0;
    for(size_t i = 0; i < MEMORY_PROFILER.all.current.count; i++)
    {
        if(MEMORY_PROFILER.allocation_arr[i].adress == pointer_)
        {
            usage_sum = MEMORY_PROFILER.allocation_arr[i].size;

            usage_own = sizeof(*MEMORY_PROFILER.allocation_arr) * (MEMORY_PROFILER.all.current.count - 1);
            usage_own_sum= sizeof(*MEMORY_PROFILER.allocation_arr);
            count_own_sum = 1;

            MEMORY_PROFILER.allocation_arr[i] = MEMORY_PROFILER.allocation_arr[MEMORY_PROFILER.all.current.count - 1];

            MEMORY_PROFILER.allocation_arr = realloc(MEMORY_PROFILER.allocation_arr, usage_own);
            DARK_ASSERT(NULL != MEMORY_PROFILER.allocation_arr, DARK_ERROR_ALLOCATION);

            MEMORY_PROFILER.allocation_arr[0].adress = MEMORY_PROFILER.allocation_arr;
            MEMORY_PROFILER.allocation_arr[0].size = usage_own;
            MEMORY_PROFILER.allocation_arr[0].at.file = __FILE__;
            MEMORY_PROFILER.allocation_arr[0].at.func = __func__;
            MEMORY_PROFILER.allocation_arr[0].at.line = 0;
            MEMORY_PROFILER.allocation_arr[0].at.date = __DATE__;
            MEMORY_PROFILER.allocation_arr[0].at.time = __TIME__;
            MEMORY_PROFILER.allocation_arr[0].at.library = DARK_LIBRARY;
            MEMORY_PROFILER.allocation_arr[0].at.module = DARK_MODULE;
            MEMORY_PROFILER.allocation_arr[0].at.unit = DARK_UNIT;
        }
    }

    MEMORY_PROFILER.own.current.usage -= usage_own_sum;
    MEMORY_PROFILER.own.total.count += count_own_sum;
    MEMORY_PROFILER.own.total.usage += usage_own;

    MEMORY_PROFILER.all.current.count -= 1;
    MEMORY_PROFILER.all.current.usage -= usage_own_sum + usage_sum;
    MEMORY_PROFILER.all.total.count += count_own_sum;
    MEMORY_PROFILER.all.total.usage += usage_own;
}
