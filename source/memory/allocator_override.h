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

#if !defined(___DARK___ALLOCATOR_OVERRIDE_H)
#define ___DARK___ALLOCATOR_OVERRIDE_H

#include <dark/core/std.h>
#include <dark/memory/memory_debug.h>

#if defined(___DARK_DEBUG)
#define dark_malloc(allocator, byte) dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_malloc", (allocator), NULL, 0, (byte))
#define dark_balloc(allocator, byte, count) dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_balloc", (allocator), NULL, 0, (byte) * (count))

#define dark_realloc(allocator, address, byte_old, byte_new) dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_realloc", (allocator), (address), (byte_old), (byte_new))
#define dark_brealloc(allocator, address, byte, count_old, count_new) dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_brealloc", (allocator), (address), (byte) * (count_old), (byte) * (count_new))

#define dark_free(allocator, address, byte) (void)dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_free", (allocator), (address), (byte), 0)
#define dark_bfree(allocator, address, byte, count) (void)dark_memory_debug_allocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_bfree", (allocator), (address), (byte) * (count), 0)

#define dark_calloc(allocator, byte) dark_memory_debug_callocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_calloc", (allocator), NULL, 0, (byte))
#define dark_bcalloc(allocator, byte, count) dark_memory_debug_callocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_bcalloc", (allocator), NULL, 0, (byte) * (count))

#define dark_recalloc(allocator, address, byte_old, byte_new) dark_memory_debug_callocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_recalloc", (allocator), (address), (byte_old), (byte_new))
#define dark_brecalloc(allocator, address, byte, count_old, count_new) dark_memory_debug_callocate((Dark_Location){ __FILE__, __func__, __LINE__, __DATE__, __TIME__ }, DARK_LIBRARY, DARK_MODULE, DARK_UNIT, "dark_brecalloc", (allocator), (address), (byte) * (count_old), (byte) * (count_new))
#endif // defined(___DARK_DEBUG)

#endif // !defined(___DARK___ALLOCATOR_OVERRIDE_H)
