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

#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "container"

Dark_Array_View dark_array_view(const Dark_Array array_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    Dark_Array_View view;
    view.data = array_.data;
    view.size = array_.size;
    view.element_byte = array_.element_byte;

    return view;
}

Dark_Buffer dark_array_buffer(const Dark_Array array_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    const Dark_Buffer buffer = { array_.element_byte * array_.size, array_.data };

    return buffer;
}

Dark_Buffer_View dark_array_buffer_view(const Dark_Array array_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);

    const Dark_Buffer_View buffer_view = { array_.element_byte * array_.size, array_.data };

    return buffer_view;
}

Dark_Buffer_View dark_array_view_buffer_view(const Dark_Array_View array_view_)
{
    DARK_ASSERT(NULL != array_view_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_view_.element_byte > 0, DARK_ERROR_ZERO);

    const Dark_Buffer_View buffer_view = { array_view_.element_byte * array_view_.size, array_view_.data };

    return buffer_view;
}

void dark_array_foreach(const Dark_Array array_, void* const context_, const Dark_Foreach foreach_)
{
    DARK_ASSERT(NULL != array_.data, DARK_ERROR_NULL);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);
    //context_
    DARK_ASSERT(NULL != foreach_, DARK_ERROR_NULL);

    for(size_t i = 0; i < array_.size; i++)
    {
        foreach_((uint8_t*)array_.data + (array_.element_byte * i), context_);
    }
}

int8_t dark_array_compare(const Dark_Array* const a_, const Dark_Array* const b_)
{
    DARK_ASSERT(NULL != a_->data, DARK_ERROR_NULL);
    DARK_ASSERT(a_->size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(a_->element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != b_->data, DARK_ERROR_NULL);
    DARK_ASSERT(b_->size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(b_->element_byte > 0, DARK_ERROR_ZERO);

    const Dark_Array_View av = dark_array_view(*a_);
    const Dark_Array_View bv = dark_array_view(*b_);

    return dark_array_view_compare(&av, &bv);
}

int8_t dark_array_view_compare(const Dark_Array_View* const a_, const Dark_Array_View* const b_)
{
    DARK_ASSERT(NULL != a_->data, DARK_ERROR_NULL);
    DARK_ASSERT(a_->size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(a_->element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != b_->data, DARK_ERROR_NULL);
    DARK_ASSERT(b_->size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(b_->element_byte > 0, DARK_ERROR_ZERO);

    if(dark_compare_zu(&a_->element_byte, &b_->element_byte))
    {
        return dark_compare_zu(&a_->element_byte, &b_->element_byte);
    }

    if(dark_compare_zu(&a_->size, &b_->size))
    {
        return dark_compare_zu(&a_->size, &b_->size);
    }

    if(dark_memcmp(a_->data, b_->data, a_->element_byte * a_->size))
    {
        return dark_memcmp(a_->data, b_->data, a_->element_byte * a_->size);
    }

    return 0;
}
