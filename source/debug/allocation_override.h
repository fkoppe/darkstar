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

#if !defined(___DARK___ALLOCATION_OVERRIDE_H)
#define ___DARK___ALLOCATION_OVERRIDE_H

#include <dark/core/essential.h>
#include <dark/debug/debug_memory.h>

#if defined(___DARK_DEBUG)
#define dark_malloc(allocator, byte) dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_malloc", (allocator), NULL, 0, (byte))
#define dark_balloc(allocator, size, count) dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_balloc", (allocator), NULL, 0, (size) * (count))

#define dark_realloc(allocator, address, byte_old, byte_new) dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_realloc", (allocator), (address), (byte_old), (byte_new))
#define dark_brealloc(allocator, address, size, count_old, count_new) dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_brealloc", (allocator), (address), (size) * (count_old), (size) * (count_new))

#define dark_free(allocator, address, byte) (void)dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_free", (allocator), (address), (byte), 0)
#define dark_bfree(allocator, address, size, count) (void)dark_debug_memory_allocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_bfree", (allocator), (address), (size) * (count), 0)

#define dark_calloc(allocator, byte) dark_debug_memory_callocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_calloc", (allocator), NULL, 0, (byte))
#define dark_bcalloc(allocator, size, count) dark_debug_memory_callocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_bcalloc", (allocator), NULL, 0, (size) * (count))

#define dark_recalloc(allocator, address, byte_old, byte_new) dark_debug_memory_callocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_recalloc", (allocator), (address), (byte_old), (byte_new))
#define dark_brecalloc(allocator, address, size, count_old, count_new) dark_debug_memory_callocate(__FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_CONFIGURATION, DARK_MODULE, DARK_UNIT, "dark_brecalloc", (allocator), (address), (size) * (count_old), (size) * (count_new))
#endif // defined(___DARK_DEBUG)

#endif // !defined(___DARK___ALLOCATION_OVERRIDE_H)
