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

#include "os_allocator_helper.h"
#include "memory_module.h"

#include <dark/core/core.h>
#include <dark/memory/allocator_struct.h>
#include <dark/memory/memory.h>
#include <dark/memory/os_allocator_context.h>

#undef malloc
#undef calloc
#undef realloc
#undef free

#include <stdlib.h>

#undef DARK_UNIT
#define DARK_UNIT "os_allocator"

void dark_os_allocator_construct(Dark_Allocator* const os_allocator_, Dark_Os_Allocator_Context* const context_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != context_, DARK_ERROR_NULL);

    os_allocator_->allocate = dark_os_allocator_allocate;
    os_allocator_->callocate = dark_os_allocator_callocate;
    os_allocator_->context = context_;

    context_->info.count = 0;
    context_->info.usage = 0;
}

void dark_os_allocator_destruct(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    //nothing
}

Dark_Allocator* dark_os_allocator_new(void)
{
    Dark_Allocator* const allocator = malloc(sizeof(*allocator) + dark_os_allocator_context_byte());
    DARK_ASSERT(NULL != allocator, DARK_ERROR_ALLOCATION);

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)((int8_t*)allocator + sizeof(Dark_Allocator));

    dark_os_allocator_construct((Dark_Allocator*)allocator, context);

    context->info.count = 1;
    context->info.usage = sizeof(Dark_Allocator) + sizeof(dark_os_allocator_context_byte());

    return (Dark_Allocator*)allocator;
}

void dark_os_allocator_delete(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    dark_os_allocator_destruct(os_allocator_);

    free(os_allocator_);
}

Dark_Allocator_Info dark_os_allocator_info(Dark_Allocator* const os_allocator_)
{
    DARK_ASSERT(NULL != os_allocator_, DARK_ERROR_NULL);

    Dark_Os_Allocator_Context* const context = (Dark_Os_Allocator_Context*)os_allocator_->context;

    return context->info;
}

size_t dark_os_allocator_context_byte(void)
{
    return sizeof(Dark_Os_Allocator_Context);
}
