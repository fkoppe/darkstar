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
#define DARK_UNIT "cbuffer"

Dark_Cbuffer_View dark_cbuffer_to_view(const Dark_Cbuffer cbuffer_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);

    const Dark_Cbuffer_View view = { cbuffer_.size, cbuffer_.data };

    return view;
}

Dark_Array dark_cbuffer_to_array(const Dark_Cbuffer cbuffer_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);

    const Dark_Array array = { sizeof(char), cbuffer_.size, cbuffer_.data };

    return array;
}

Dark_Array_View dark_cbuffer_to_array_view(const Dark_Cbuffer cbuffer_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);

    const Dark_Array_View array_view = { sizeof(char), cbuffer_.size, cbuffer_.data };

    return array_view;
}

Dark_Buffer dark_cbuffer_to_buffer(const Dark_Cbuffer cbuffer_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);

    const Dark_Buffer buffer = { cbuffer_.size, cbuffer_.data };

    return buffer;
}

Dark_Buffer_View dark_cbuffer_to_buffer_view(const Dark_Cbuffer cbuffer_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);

    const Dark_Buffer_View buffer_view = { cbuffer_.size, cbuffer_.data };

    return buffer_view;
}

bool dark_cbuffer_terminated_is(const Dark_Cbuffer cbuffer_, size_t* const cstring_lenght_)
{
    DARK_ASSERT(cbuffer_.data == NULL || cbuffer_.size > 0, DARK_ERROR_VALUE);
    //cstring_lenght_

    return dark_cbuffer_view_terminated_is(dark_cbuffer_to_view(cbuffer_), cstring_lenght_);
}

int8_t dark_cbuffer_compare(const Dark_Cbuffer* a_, const Dark_Cbuffer* b_)
{
    DARK_ASSERT(a_->data == NULL || a_->size > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(b_->data == NULL || b_->size > 0, DARK_ERROR_VALUE);

    const Dark_Cbuffer_View a = dark_cbuffer_to_view(*a_);
    const Dark_Cbuffer_View b = dark_cbuffer_to_view(*b_);

    return dark_cbuffer_view_compare(&a, &b);
}
