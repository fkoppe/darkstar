/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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

#if !defined(___DARK___MEMORY_DEBUG_H)
#define ___DARK___MEMORY_DEBUG_H

#include <dark/core/enviroment.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

#undef DARK_MEMORY_DEBUG_INITIALISE
#undef DARK_MEMORY_DEBUG_SHUTDOWN
#undef DARK_MEMORY_DEBUG_TRYINITIALISE
#undef DARK_MEMORY_DEBUG_TRYSHUTDOWN

#if defined(___DARK_DEBUG)
#define DARK_MEMORY_DEBUG_INITIALISE dark_memory_debug_initialise()
#define DARK_MEMORY_DEBUG_SHUTDOWN dark_memory_debug_shutdown()
#define DARK_MEMORY_DEBUG_TRYINITIALISE dark_memory_debug_tryinitialise()
#define DARK_MEMORY_DEBUG_TRYSHUTDOWN dark_memory_debug_tryshutdown()
#else
#define DARK_MEMORY_DEBUG_INITIALISE
#define DARK_MEMORY_DEBUG_SHUTDOWN
#define DARK_MEMORY_DEBUG_TRYINITIALISE
#define DARK_MEMORY_DEBUG_TRYSHUTDOWN
#endif // defined(___DARK_DEBUG)

void dark_memory_debug_initialise(void);
void dark_memory_debug_shutdown(void);
void dark_memory_debug_tryinitialise(void);
void dark_memory_debug_tryshutdown(void);

void* dark_memory_debug_allocate(Dark_Location location, const Dark_Library* library, const char* module, const char* unit, const char* func_name, Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);
void* dark_memory_debug_callocate(Dark_Location location, const Dark_Library* library, const char* module, const char* unit, const char* func_name, Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);

#endif // !defined(___DARK___MEMORY_DEBUG_H)
