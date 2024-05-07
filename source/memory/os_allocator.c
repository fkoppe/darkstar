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

#include "memory_module.h"

#include <dark/memory/memory.h>
#include <dark/core/core.h>

#include <stdlib.h>
#include <string.h>

#undef DARK_UNIT
#define DARK_UNIT "os_allocator"

typedef struct Dark_Os_Allocator_Context
{
    int i;
} Dark_Os_Allocator_Context;

void* dark_os_allocator_allocate(void* const context_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    //NO ASSERT

    if(NULL != context_)
    {
        //TODO debug is on
    }

    void* pointer = NULL;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_ASSERT(NULL == address_, DARK_ERROR_LOGIC);
        DARK_ASSERT(0 == byte_old_, DARK_ERROR_LOGIC);
        DARK_ASSERT(byte_new_ > 0, DARK_ERROR_LOGIC);

        pointer = malloc(byte_new_);
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_ASSERT(byte_old_ > 0, DARK_ERROR_ALLOCATOR_FREE);

        free(address_);
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > byte_old_)
    {
        pointer = realloc(address_, byte_new_);
    }
    else
    {
        DARK_EXIT_ERROR(-1, DARK_ERROR_LOGIC);
    }

    return pointer;
}

void* dark_os_allocator_callocate(void* const context_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    //NO ASSERT

    if(NULL != context_)
    {
        //TODO debug is true
    }

    void* pointer = NULL;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_ASSERT(NULL == address_, DARK_ERROR_LOGIC);
        DARK_ASSERT(0 == byte_old_, DARK_ERROR_LOGIC);
        DARK_ASSERT(byte_new_ > 0, DARK_ERROR_LOGIC);

        pointer = calloc(1, byte_new_);
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_ASSERT(byte_old_ > 0, DARK_ERROR_ALLOCATOR_FREE);

        free(address_);
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > byte_old_)
    {
        pointer = realloc(address_, byte_new_);

        if(byte_new_ > byte_old_)
        {
            memset((char*)pointer + byte_old_, 0, byte_new_ - byte_old_);
        }
    }
    else
    {
        DARK_EXIT_ERROR(-1, DARK_ERROR_LOGIC);
    }

    return pointer;
}

size_t dark_os_allocator_context_size(void)
{
    return sizeof(Dark_Os_Allocator_Context);
}

void dark_os_allocator_create(Dark_Allocator* const allocator_, const bool debug_is_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //debug_is_

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;
    allocator->allocate = dark_os_allocator_allocate;
    allocator->callocate = dark_os_allocator_callocate;
    allocator->context = NULL;

    if(debug_is_)
    {
        //TODO
        allocator->context = dark_os_allocator_create;

        //allocator->context = malloc(sizeof(Dark_Os_Allocator_Context));
        //DARK_ASSERT(NULL != allocator->context, DARK_ERROR_ALLOCATION);
    }
}

void dark_os_allocator_destroy(Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    if(NULL != allocator->context)
    {
        //TODO

        //free(allocator->context);
    }
}

Dark_Allocator* dark_os_allocator_new(const bool debug_is_)
{
    //debug_is_

    Dark_Allocator_Struct* const allocator = malloc(sizeof(Dark_Allocator_Struct));
    DARK_ASSERT(NULL != allocator, DARK_ERROR_ALLOCATION);

    dark_os_allocator_create((Dark_Allocator*)allocator, debug_is_);

    return (Dark_Allocator*)allocator;
}

void dark_os_allocator_delete(Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    dark_os_allocator_destroy((Dark_Allocator*)allocator);

    free(allocator);
}

Dark_Allocator_Info dark_os_allocator_info(Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    Dark_Os_Allocator_Context* const context = allocator->context;

    Dark_Allocator_Info info = { 0 };

    if(NULL != context)
    {
        //TODO debug is true

        info.debug_is = true;
    }

    return info;
}
