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

#include "char_module.h"

#include <dark/algorithm/algorithm.h>
#include <dark/char/char.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "cbuffer_view"

Dark_Array_View dark_cbuffer_view_to_array_view(const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);

    const Dark_Array_View array_view = { sizeof(char), cbuffer_view_.size, cbuffer_view_.data };

    return array_view;
}

Dark_Buffer_View dark_cbuffer_view_to_buffer_view(const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);

    const Dark_Buffer_View buffer_view = { cbuffer_view_.size, cbuffer_view_.data };

    return buffer_view;
}

bool dark_cbuffer_view_terminated_is(const Dark_Cbuffer_View cbuffer_view_, size_t* const cstring_lenght_)
{
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    //cstring_lenght_

    const char element = '\0';
    const Dark_Array_View array_view = { sizeof(char), cbuffer_view_.size, cbuffer_view_.data };

    return dark_find_linear_index(&element, array_view, (Dark_Compare)dark_compare_u8, cstring_lenght_);
}

int8_t dark_cbuffer_view_compare(const Dark_Cbuffer_View* const a_, const Dark_Cbuffer_View* const b_)
{
    DARK_ASSERT(NULL != a_, DARK_ERROR_NULL);
    DARK_ASSERT(a_->size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != b_, DARK_ERROR_NULL);
    DARK_ASSERT(b_->size > 0, DARK_ERROR_ZERO);

    if(a_->size < b_->size)
    {
        return -1;
    }
    else if(a_->size > b_->size)
    {
        return 1;
    }

    for(size_t i = 0; i < a_->size; i++)
    {
        const int8_t result = dark_compare_i8((int8_t*)a_->data + i, (int8_t*)b_->data + i);

        if(result != 0)
        {
            return result;
        }
    }

    return 0;
}
