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
#include <dark/core/essential.h>

typedef struct Dark_Allocator Dark_Allocator;

typedef struct Dark_Allocator_Struct
{
    void* (*allocate)(void* context, void* pointer, size_t size_old, size_t size_new);
    void* (*callocate)(void* context, void* pointer, size_t size_old, size_t size_new);
    void* context;
} Dark_Allocator_Struct;

typedef struct Dark_Allocator_Info
{
    bool debug_is;
    size_t count;
    size_t usage;
} Dark_Allocator_Info;

static const Dark_Error DARK_ERROR_ALLOCATOR_INTEGRITY = { &DARK_ERROR_RUNTIME, "allocator_integrity", "allocator memory corrupted"};
static const Dark_Error DARK_ERROR_ALLOCATOR_NOMEMORY = { &DARK_ERROR_RUNTIME, "allocator_nomemory", "out of memory"};
static const Dark_Error DARK_ERROR_ALLOCATOR_FREE = { &DARK_ERROR_LOGIC, "allocator_free", "address is already free"};
static const Dark_Error DARK_ERROR_ALLOCATOR_ADDRESS = { &DARK_ERROR_RANGE, "allocator_address", "address is not known"};
static const Dark_Error DARK_ERROR_ALLOCATOR_INTERNAL = { &DARK_ERROR_INTERNAL, "allocator_internal", NULL};

void* dark_malloc(Dark_Allocator* allocator, size_t byte);
void* dark_balloc(Dark_Allocator* allocator, size_t count, size_t size);

void* dark_realloc(Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);
void* dark_brealloc(Dark_Allocator* allocator, void* address, size_t size, size_t count_old, size_t count_new);

void dark_free(Dark_Allocator* allocator, void* address, size_t byte);
void dark_bfree(Dark_Allocator* allocator, void* address, size_t size, size_t count);

void* dark_calloc(Dark_Allocator* allocator, size_t byte);
void* dark_bcalloc(Dark_Allocator* allocator, size_t size, size_t count);

void* dark_recalloc(Dark_Allocator* allocator, void* address, size_t byte_old, size_t byte_new);
void* dark_brecalloc(Dark_Allocator* allocator, void* address, size_t size, size_t count_old, size_t count_new);

#endif // !defined(___DARK___ALLOCATOR_H)
