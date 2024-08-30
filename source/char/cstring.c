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

#include <dark/char/char.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "cstring"

size_t dark_cstring_lenght(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    for(size_t i = 0; i < DARK_CSTRING_LENGHT_MAX; i++)
    {
        if('\0' == cstring_[i])
        {
            return i;
        }
    }

    DARK_EXIT_CSTRING(-1, DARK_ERROR_RUNTIME, "cstring lost integrity");
}

Dark_Cbuffer_View dark_cstring_to_cbuffer_view(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

    Dark_Cbuffer_View cbuffer_view;
    cbuffer_view.size = dark_cstring_lenght(cstring_);
    cbuffer_view.data = cstring_;

    return cbuffer_view;
}

Dark_Cbuffer_View dark_cstring_to_cbuffer_view_terminated(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

    Dark_Cbuffer_View cbuffer_view;
    cbuffer_view.size = dark_cstring_lenght(cstring_) + 1;
    cbuffer_view.data = cstring_;

    return cbuffer_view;
}

Dark_Array_View dark_cstring_to_array_view(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

    Dark_Array_View array_view;
    array_view.size = dark_cstring_lenght(cstring_);
    array_view.data = cstring_;

    return array_view;
}

Dark_Array_View dark_cstring_to_array_view_terminated(const char* const cstring_)
{
     DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

     DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

     Dark_Array_View array_view;
     array_view.size = dark_cstring_lenght(cstring_) + 1;
     array_view.data = cstring_;

     return array_view;
}

Dark_Buffer_View dark_cstring_to_buffer_view(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

    Dark_Buffer_View buffer_view;
    buffer_view.byte = dark_cstring_lenght(cstring_);
    buffer_view.data = cstring_;

    return buffer_view;
}

Dark_Buffer_View dark_cstring_to_buffer_view_terminated(const char* const cstring_)
{
     DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

     DARK_CSTRING_ASSERT_INTEGRITY(cstring_);

     Dark_Buffer_View buffer_view;
     buffer_view.byte = dark_cstring_lenght(cstring_) + 1;
     buffer_view.data = cstring_;

     return buffer_view;
}

int8_t dark_cstring_compare(const char* const a_, const char* const b_)
{
    DARK_ASSERT(NULL != a_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != b_, DARK_ERROR_NULL);

    const Dark_Cbuffer_View a = dark_cstring_to_cbuffer_view(a_);
    const Dark_Cbuffer_View b = dark_cstring_to_cbuffer_view(b_);

    return dark_cbuffer_view_compare(&a, &b);
}
