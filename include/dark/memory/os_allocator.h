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

#if !defined(___DARK___OS_ALLOCATOR_H)
#define ___DARK___OS_ALLOCATOR_H

#include <dark/core/essential.h>
#include <dark/memory/allocator.h>

void* dark_os_allocator_allocate(void* context, void* address, size_t size_old, size_t size_new);
void* dark_os_allocator_callocate(void* context, void* address, size_t size_old, size_t size_new);

static const Dark_Allocator_Struct DARK_ALLOCATOR_NATIVE_STRUCT = { dark_os_allocator_allocate, dark_os_allocator_callocate, NULL };
static Dark_Allocator* const DARK_ALLOCATOR_NATIVE = (Dark_Allocator*)&DARK_ALLOCATOR_NATIVE_STRUCT;

size_t dark_os_allocator_context_size(void);

void dark_os_allocator_create(Dark_Allocator* allocator, bool debug_is);
void dark_os_allocator_destroy(Dark_Allocator* allocator);

Dark_Allocator* dark_os_allocator_new(bool debug_is);
void dark_os_allocator_delete(Dark_Allocator* allocator);

Dark_Allocator_Info dark_os_allocator_info(Dark_Allocator* allocator);

#endif // !defined(___DARK___OS_ALLOCATOR_H)

