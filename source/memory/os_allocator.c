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

#undef malloc
#undef calloc
#undef realloc
#undef free

#include <stdlib.h>

#undef DARK_UNIT
#define DARK_UNIT "os_allocator"

size_t dark_os_allocator_context_size(void)
{
    return sizeof(Dark_Os_Allocator_Context);
}

Dark_Allocator_Struct dark_os_allocator_create(void* const context_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    Dark_Allocator_Struct allocator;
    allocator.allocate = dark_os_allocator_allocate;
    allocator.callocate = dark_os_allocator_callocate;
    allocator.context = context_;

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)allocator.context;
    context->info.count = 0;
    context->info.usage = 0;

    return allocator;
}

void dark_os_allocator_destroy(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)os_allocator_;

    //nothing
}

Dark_Allocator* dark_os_allocator_new(void)
{
    Dark_Allocator_Struct* const allocator = malloc(sizeof(Dark_Allocator_Struct) + dark_os_allocator_context_size());
    DARK_ASSERT(NULL != allocator, DARK_ERROR_ALLOCATION);

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)((char*)allocator + sizeof(Dark_Allocator_Struct));

    *allocator = dark_os_allocator_create(context);

    context->info.count = 1;
    context->info.usage = sizeof(Dark_Allocator_Struct) + sizeof(dark_os_allocator_context_size());

    return (Dark_Allocator*)allocator;
}

void dark_os_allocator_delete(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)os_allocator_;

    dark_os_allocator_destroy((Dark_Allocator*)allocator);

    free(allocator);
}

Dark_Allocator_Info dark_os_allocator_info(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)os_allocator_;
    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)allocator->context;

    return context->info;
}

void* dark_os_allocator_allocate(void* const context_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)context_;

    void* pointer = NULL;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_ASSERT(NULL == address_, DARK_ERROR_LOGIC);
        DARK_ASSERT(0 == byte_old_, DARK_ERROR_LOGIC);
        DARK_ASSERT(byte_new_ > 0, DARK_ERROR_LOGIC);

        pointer = malloc(byte_new_);

        context->info.count++;
        context->info.usage += byte_new_;
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_ASSERT(byte_old_ > 0, DARK_ERROR_LOGIC);

        free(address_);

        context->info.count--;
        context->info.usage -= byte_old_;
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > 0)
    {
        pointer = realloc(address_, byte_new_);

        context->info.usage += (int64_t)(byte_new_ - byte_old_);
    }
    else
    {
        DARK_EXIT_ERROR(-1, DARK_ERROR_LOGIC);
    }

    return pointer;
}

void* dark_os_allocator_callocate(void* const context_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)context_;

    void* pointer = NULL;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_ASSERT(NULL == address_, DARK_ERROR_LOGIC);
        DARK_ASSERT(0 == byte_old_, DARK_ERROR_LOGIC);
        DARK_ASSERT(byte_new_ > 0, DARK_ERROR_LOGIC);

        pointer = calloc(1, byte_new_);

        context->info.count++;
        context->info.usage += byte_new_;
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_ASSERT(byte_old_ > 0, DARK_ERROR_LOGIC);

        free(address_);

        context->info.count--;
        context->info.usage -= byte_old_;
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > 0)
    {
        pointer = realloc(address_, byte_new_);

        context->info.usage += (int64_t)(byte_new_ - byte_old_);

        if(byte_new_ > byte_old_ && NULL != pointer)
        {
            dark_memset((char*)pointer + byte_old_, 0, byte_new_ - byte_old_);
        }
    }
    else
    {
        DARK_EXIT_ERROR(-1, DARK_ERROR_LOGIC);
    }

    return pointer;
}
