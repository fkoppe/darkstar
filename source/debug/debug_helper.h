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

#if !defined(___DARK___DEBUG_HELPER_H)
#define ___DARK___DEBUG_HELPER_H

#include <dark/core/essential.h>

#if defined(___DARK_DEBUG)
#define DARK_DEBUG_MEMORY_ASSERT(call_info, condition) if(!(condition)) dark_debug_memory_assert((call_info), (#condition))
#define DARK_DEBUG_MEMORY_MATCHING(call_info, mem_info, condition) if(!(condition)) dark_debug_memory_matching((call_info), (mem_info), (#condition))
#define DARK_DEBUG_MEMORY_EXIT(call_info, message) dark_debug_memory_exit((call_info), (message))
#define DARK_DEBUG_MEMORY_WARN(call_info, message) dark_debug_memory_warn((call_info), (message))
#else
#define DARK_DEBUG_MEMORY_ASSERT(call_info, condition)
#define DARK_DEBUG_MEMORY_MATCHING(call_info, mem_info, condition)
#define DARK_DEBUG_MEMORY_EXIT(call_info, message)
#define DARK_DEBUG_MEMORY_WARN(call_info, message)
#endif // defined(___DARK_DEBUG)

typedef struct Dark_Debug_Memory_Info
{
    void* allocator;
    void* address;
    size_t byte;
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
        const char* func_name;
    } at;
} Dark_Debug_Memory_Info;

void dark_debug_memory_assert(Dark_Debug_Memory_Info call_info, const char* condition);
void dark_debug_memory_matching(Dark_Debug_Memory_Info call_info, Dark_Debug_Memory_Info mem_info, const char* condition);
void dark_debug_memory_exit(Dark_Debug_Memory_Info call_info, const char* message);
void dark_debug_memory_warn(Dark_Debug_Memory_Info call_info, const char* message);

void dark_debug_memory_print_info(Dark_Debug_Memory_Info info, const char* text);
void dark_debug_memory_print_leak(Dark_Debug_Memory_Info info);

#endif // !defined(___DARK___DEBUG_HELPER_H)
