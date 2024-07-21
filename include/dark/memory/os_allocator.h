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

#include <dark/core/std.h>
#include <dark/memory/allocator.h>

typedef struct Dark_Os_Allocator_Context Dark_Os_Allocator_Context;
struct Dark_Os_Allocator_Context
{
    Dark_Allocator_Info info;
};

size_t dark_os_allocator_context_size(void);

Dark_Allocator_Struct dark_os_allocator_construct_struct(void* context);

void dark_os_allocator_construct(Dark_Allocator* os_allocator, void* context);
void dark_os_allocator_destruct(Dark_Allocator* os_allocator);

Dark_Allocator* dark_os_allocator_new(void);
void dark_os_allocator_delete(Dark_Allocator* os_allocator);

Dark_Allocator_Info dark_os_allocator_info(Dark_Allocator* os_allocator);

void* dark_os_allocator_allocate(void* context, void* address, size_t byte_old, size_t byte_new);
void* dark_os_allocator_callocate(void* context, void* address, size_t byte_old, size_t byte_new);

#endif // !defined(___DARK___OS_ALLOCATOR_H)

