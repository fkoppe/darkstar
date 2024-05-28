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

#include "debug_helper.h"
#include "debug_module.h"

#include <dark/core/core.h>
#include <dark/debug/debug.h>

#undef DARK_UNIT
#define DARK_UNIT "debug_helper"

#include <stdio.h>
#include <stdlib.h>

void dark_debug_memory_assert(const Dark_Debug_Memory_Info call_info_, const char* const condition_)
{
    //call_info_
    DARK_ASSERT(NULL != condition_, DARK_ERROR_NULL);

    fprintf(stderr, "---------------MEMORY_DEBUG---------------\nassertion failed - abort has been called\n\ncond:\t(%s) was false\n\n", condition_);

    dark_debug_memory_print_info(call_info_, "function called from");

    fputs("------------------------------------------\n", stderr);

    abort();
}

void dark_debug_memory_match(Dark_Debug_Memory_Info call_info_, Dark_Debug_Memory_Info mem_info_, const char* const condition_)
{
    //call_info_
    //mem_info_
    DARK_ASSERT(NULL != condition_, DARK_ERROR_NULL);

    fprintf(stderr, "---------------MEMORY_DEBUG---------------\ninfo mismatch - exit has been called\n\ncond:\t(%s) was false\n\n", condition_);

    fputs("----------INFO#1", stderr);

    dark_debug_memory_print_info(call_info_, "function called from");

    fputs("----------INFO#2", stderr);

    dark_debug_memory_print_info(mem_info_, "last function call");

    fputs("------------------------------------------\n", stderr);

    exit(-1);
}

void dark_debug_memory_exit(const Dark_Debug_Memory_Info call_info_, const char* const message_)
{
    //call_info_
    DARK_ASSERT(NULL != message_, DARK_ERROR_NULL);

    fprintf(stderr, "---------------MEMORY_DEBUG---------------\nexit has been called\n\nmesg: %s\n\n", message_);

    dark_debug_memory_print_info(call_info_, "function called from");

    fputs("------------------------------------------\n", stderr);

    exit(-1);
}

void dark_debug_memory_warn(const Dark_Debug_Memory_Info call_info_, const char* const message_)
{
    //call_info_
    DARK_ASSERT(NULL != message_, DARK_ERROR_NULL);;

    fprintf(stderr, "---------------MEMORY_DEBUG_WARNING---------------\n%s\n\n", message_);

    dark_debug_memory_print_info(call_info_, "function called from");

    fputs("--------------------------------------------------\n", stderr);
}

void dark_debug_memory_print_info(const Dark_Debug_Memory_Info info_, const char* const text_)
{
    //info_
    DARK_ASSERT(NULL != text_, DARK_ERROR_NULL);

    fprintf(stderr, "----------\n%s:\n\nfile:\t%s\nfunc:\t%s\nline:\t%" PRId64 "\ndate:\t%s\ntime:\t%s\n\nconf:\t%s\n\nname:\t%s\n\n----------\nallo:\t%p\naddr:\t%p\nbyte:\t%zu\n\n", text_, info_.at.file, info_.at.func, info_.at.line, info_.at.date, info_.at.time, ___DARK_CONFIGURATION, info_.at.func_name, info_.allocator, info_.address, info_.byte);

    if (NULL != info_.at.library)
    {
        fprintf(stderr, "----------\n\nname:\t%s\nvers:\t%" PRId8 ".%" PRId16 ".%" PRId8 ".%" PRId16 "\n\n", info_.at.library->name, dark_version_major(info_.at.library->version), dark_version_minor(info_.at.library->version), dark_version_stage(info_.at.library->version), dark_version_patch(info_.at.library->version));
    }

    if (NULL != info_.at.configuration)
    {
        fprintf(stderr, "conf:\t%s\n\n", info_.at.configuration);
    }

    if (NULL != info_.at.module)
    {
        fprintf(stderr, "modl:\t%s\n", info_.at.module);
    }

    if (NULL != info_.at.unit)
    {
        fprintf(stderr, "unit:\t%s\n", info_.at.unit);
    }

    if (NULL != info_.at.unit || info_.at.module)
    {
        fputs("\n", stderr);
    }
}

void dark_debug_memory_print_leak(const Dark_Debug_Memory_Info info_, const size_t index_)
{
    //info_
    //index_

    fprintf(stderr, "---------------MEMORY_DEBUG_LEAK---------------\nmemory leak#%zu detected\n\n", index_);

    dark_debug_memory_print_info(info_, "last function call");

    fputs("-----------------------------------------------\n", stderr);
}
