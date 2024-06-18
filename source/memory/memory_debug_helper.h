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

#if !defined(___DARK___MEMORY_DEBUG_HELPER_H)
#define ___DARK___MEMORY_DEBUG_HELPER_H

#include <dark/core/assert.h>
#include <dark/core/enviroment.h>
#include <dark/core/std.h>
#include <dark/core/util.h>
#include <dark/memory/allocator.h>

#if defined(___DARK_DEBUG)
#define DARK_MEMORY_DEBUG_ASSERT(call_info, condition) if(!(condition)) dark_memory_debug_assert((call_info), (#condition))
#define DARK_MEMORY_DEBUG_MATCH(call_info, mem_info, condition) if(!(condition)) dark_memory_debug_match((call_info), (mem_info), (#condition))
#define DARK_MEMORY_DEBUG_EXIT(call_info, cstring) dark_memory_debug_exit((call_info), (Dark_Message){ NULL, NULL, (cstring) })
#define DARK_MEMORY_DEBUG_WARN(call_info, cstring) dark_memory_debug_warn((call_info), (Dark_Message){ NULL, NULL, (cstring) })
#else
#define DARK_MEMORY_DEBUG_ASSERT(call_info, condition)
#define DARK_MEMORY_DEBUG_MATCH(call_info, mem_info, condition)
#define DARK_MEMORY_DEBUG_EXIT(call_info, cstring)
#define DARK_MEMORY_DEBUG_WARN(call_info, cstring)
#endif // defined(___DARK_DEBUG)

typedef struct Dark_Memory_Debug_Info
{
    Dark_Location location;
    const Dark_Library* library;
    const char* configuration;
    const char* module;
    const char* unit;
    const char* func_name;
    Dark_Allocator* allocator;
    void* address;
    size_t byte;
} Dark_Memory_Debug_Info;

static const Dark_Message DARK_MESSAGE_MEMORY_DEBUG_ASSERT = { &DARK_MESSAGE_ASSERT, "memory_debug ", NULL };
static const Dark_Message DARK_MESSAGE_MEMORY_DEBUG_MISMATCH = { &DARK_MESSAGE_EXIT, "info mismatch - ", NULL };
static const Dark_Message DARK_MESSAGE_MEMORY_DEBUG_FUNCTION = { NULL, "function called from:", NULL };
static const Dark_Message DARK_MESSAGE_MEMORY_DEBUG_LAST = { &DARK_MESSAGE_MEMORY_DEBUG_FUNCTION, "last ", NULL };

DARK_NORETURN void dark_memory_debug_assert(Dark_Memory_Debug_Info call_info, const char* condition);
DARK_NORETURN void dark_memory_debug_match(Dark_Memory_Debug_Info call_info, Dark_Memory_Debug_Info mem_info, const char* condition);
DARK_NORETURN void dark_memory_debug_exit(Dark_Memory_Debug_Info call_info, Dark_Message message);

void dark_memory_debug_warn(Dark_Memory_Debug_Info call_info, Dark_Message message);

void dark_memory_debug_print_leak(Dark_Memory_Debug_Info info, size_t index);
void dark_memory_debug_print_leak_count(size_t count);

void dark_memory_debug_print_info(Dark_Memory_Debug_Info info, Dark_Message message);

#endif // !defined(___DARK___MEMORY_DEBUG_HELPER_H)
