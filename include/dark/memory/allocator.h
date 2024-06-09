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

#if !defined(___DARK___ALLOCATOR_H)
#define ___DARK___ALLOCATOR_H

#include <dark/core/error.h>
#include <dark/core/std.h>

typedef struct Dark_Allocator Dark_Allocator;

typedef struct Dark_Allocator_Struct Dark_Allocator_Struct;
struct Dark_Allocator_Struct
{
    void* (*allocate)(void* context, void* pointer, size_t byte_old, size_t byte_new);
    void* (*callocate)(void* context, void* pointer, size_t byte_old, size_t byte_new);
    void* context;
};

typedef struct Dark_Allocator_Info Dark_Allocator_Info;
struct Dark_Allocator_Info
{
    size_t count;
    size_t usage;
};

static const Dark_Error DARK_ERROR_ALLOCATOR_MEMORY = { &DARK_ERROR_RUNTIME, "allocator_memory", "out of memory" };
static const Dark_Error DARK_ERROR_ALLOCATOR_ADDRESS = { &DARK_ERROR_RANGE, "allocator_address", "address is not known" };

void* dark_malloc(Dark_Allocator* allocator, size_t byte);
void* dark_balloc(Dark_Allocator* allocator, size_t size, size_t count);

void* dark_realloc(Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);
void* dark_brealloc(Dark_Allocator* allocator, void* address, size_t size, size_t count_old, size_t count_new);

void dark_free(Dark_Allocator* allocator, void* address, size_t byte);
void dark_bfree(Dark_Allocator* allocator, void* address, size_t size, size_t count);

void* dark_calloc(Dark_Allocator* allocator, size_t byte);
void* dark_bcalloc(Dark_Allocator* allocator, size_t size, size_t count);

void* dark_recalloc(Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);
void* dark_brecalloc(Dark_Allocator* allocator, void* address, size_t size, size_t count_old, size_t count_new);

#endif // !defined(___DARK___ALLOCATOR_H)
