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

#if !defined(___DARK___DEBUG_MEMORY_H)
#define ___DARK___DEBUG_MEMORY_H

#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>
#include <dark/memory/allocator.h>

#if defined(___DARK_DEBUG)
#define DARK_DEBUG_MEMORY_INITIALISE dark_debug_memory_initialise()
#define DARK_DEBUG_MEMORY_SHUTDOWN dark_debug_memory_shutdown()
#else
#define DARK_DEBUG_MEMORY_INITIALISE
#define DARK_DEBUG_MEMORY_SHUTDOWN
#endif // defined(___DARK_DEBUG)

void dark_debug_memory_initialise(void);
void dark_debug_memory_shutdown(void);

void* dark_debug_memory_allocate(const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* configuration, const char* unit, const char* func_name, Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);

void* dark_debug_memory_callocate(const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* configuration, const char* unit, const char* func_name, Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);

#endif // !defined(___DARK___DEBUG_MEMORY_H)
