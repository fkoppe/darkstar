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

#include "container_module.h"
#include "ref_helper.h"

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/memory/memory.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "weak_ref"

Dark_Weak_Ref dark_weak_ref_create(const Dark_Shared_Ref shared_ref_)
{
    DARK_ASSERT(NULL != shared_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = shared_ref_.handle;

    DARK_ASSERT(control->shared_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(NULL != control->data, DARK_ERROR_CONTAINER_INTEGRITY);

    control->weak_count++;

    const Dark_Weak_Ref weak_ref = { control };

    return weak_ref;
}

void dark_weak_ref_destroy(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    control->weak_count--;

    if(0 == control->weak_count && 0 == control->shared_count)
    {
        dark_free(control->allocator, control, sizeof(*control));
    }
}

Dark_Weak_Ref dark_weak_ref_copy(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    control->weak_count++;

    const Dark_Weak_Ref weak_ref = { control };

    return weak_ref;
}

size_t dark_weak_ref_shared_count(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return control->shared_count;
}

size_t dark_weak_ref_weak_count(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return control->weak_count;
}

bool dark_weak_ref_valid_is(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return control->shared_count > 0;
}

Dark_Shared_Ref dark_weak_ref_lock(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT_CSTRING(control->shared_count > 0, DARK_ERROR_STATE, "weak_ref is not valid");

    control->shared_count++;
    control->weak_count--;

    const Dark_Shared_Ref shared_ref = { control };

    return shared_ref;
}

size_t dark_weak_ref_byte(const Dark_Weak_Ref weak_ref_)
{
    DARK_ASSERT(NULL != weak_ref_.handle, DARK_ERROR_NULL);

    Dark_Ref_Control* const control = weak_ref_.handle;

    DARK_ASSERT(control->weak_count > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return control->byte;
}
