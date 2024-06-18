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

#include "memory_debug_helper.h"
#include "memory_module.h"

#include <dark/core/core.h>
#include <dark/memory/memory.h>

#include <stdlib.h>

#undef DARK_UNIT
#define DARK_UNIT "memory_debug_helper"

void dark_memory_debug_assert(const Dark_Memory_Debug_Info call_info_, const char* const condition_)
{
    //call_info_
    DARK_ASSERT(NULL != condition_, DARK_ERROR_NULL);

    dark_print(DARK_SO_ERR, "-------------------------MEMORY_DEBUG-------------------------\n");

    dark_message_print(DARK_SO_ERR, DARK_MESSAGE_MEMORY_DEBUG_ASSERT);

    dark_printf(DARK_SO_ERR, "\n\ncond:\t(%s) was false\n\n", condition_);

    dark_memory_debug_print_info(call_info_, DARK_MESSAGE_MEMORY_DEBUG_FUNCTION);

    dark_print(DARK_SO_ERR, "\n--------------------------------------------------------------\n");

    dark_flush(DARK_SO_ERR);

    abort();
}

void dark_memory_debug_match(Dark_Memory_Debug_Info call_info_, Dark_Memory_Debug_Info mem_info_, const char* const condition_)
{
    //call_info_
    //mem_info_
    DARK_ASSERT(NULL != condition_, DARK_ERROR_NULL);

    dark_print(DARK_SO_ERR, "-------------------------MEMORY_DEBUG-------------------------\n");

    dark_message_print(DARK_SO_ERR, DARK_MESSAGE_MEMORY_DEBUG_MISMATCH);

    dark_printf(DARK_SO_ERR, "\n\ncond:\t(%s) was false\n\n", condition_);

    dark_print(DARK_SO_ERR, "----------INFO#1");

    dark_memory_debug_print_info(call_info_, DARK_MESSAGE_MEMORY_DEBUG_FUNCTION);

    dark_print(DARK_SO_ERR, "----------INFO#2");

    dark_memory_debug_print_info(call_info_, DARK_MESSAGE_MEMORY_DEBUG_LAST);

    dark_print(DARK_SO_ERR, "\n--------------------------------------------------------------\n");

    dark_flush(DARK_SO_ERR);

    exit(-1);
}

void dark_memory_debug_exit(const Dark_Memory_Debug_Info call_info_, const Dark_Message message_)
{
    //call_info_
    //message_

    dark_print(DARK_SO_ERR, "-------------------------MEMORY_DEBUG-------------------------\n");

    dark_message_print(DARK_SO_ERR, DARK_MESSAGE_EXIT);

    dark_print(DARK_SO_ERR, "mesg:\t");

    dark_message_print(DARK_SO_ERR, message_);

    dark_print(DARK_SO_ERR, "\n\n\n--------------------------------------------------------------\n");

    dark_flush(DARK_SO_ERR);

    exit(-1);
}

void dark_memory_debug_warn(const Dark_Memory_Debug_Info call_info_, const Dark_Message message_)
{
    //call_info_
    //message_

    dark_print(DARK_SO_ERR, "-------------------------MEMORY_DEBUG_WARNING-------------------------\n");

    dark_message_print(DARK_SO_ERR, message_);

    dark_memory_debug_print_info(call_info_, DARK_MESSAGE_MEMORY_DEBUG_FUNCTION);

    dark_print(DARK_SO_ERR, "\n\n\n----------------------------------------------------------------------\n");
}

void dark_memory_debug_print_leak(const Dark_Memory_Debug_Info info_, const size_t index_)
{
    //info_
    //index_

    dark_printf(DARK_SO_ERR, "-------------------------MEMORY_DEBUG_LEAK-------------------------\nmemory leak#%zu detected\n\n", index_);

    dark_memory_debug_print_info(info_, DARK_MESSAGE_MEMORY_DEBUG_LAST);

    dark_print(DARK_SO_ERR, "\n-------------------------------------------------------------------\n");
}

void dark_memory_debug_print_leak_count(const size_t count_)
{
    //count_

    dark_printf(DARK_SO_ERR, "---------------MEMORY_DEBUG---------------\nabort has been called - memory leaked\n\ninfo:\t%zu leaks\n------------------------------------------\n", count_);
}

void dark_memory_debug_print_info(const Dark_Memory_Debug_Info info_, const Dark_Message message_)
{
    //info_
    //message_

    const Dark_Message message = { &message_ , "----------\n", "\n\n"};
    dark_message_print(DARK_SO_ERR, message);

    dark_location_print(DARK_SO_ERR, info_.location);
    dark_library_print(DARK_SO_ERR, info_.library, info_.module, info_.unit);

    dark_printf(DARK_SO_ERR, "----------\nlast:\t%s:\nallo:\t%p\naddr:\t%p\nbyte:\t%zu\n\n", info_.func_name, info_.allocator, info_.address, info_.byte);
}
