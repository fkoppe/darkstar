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
#include <dark/order/order.h>

#define STB_SPRINTF_IMPLEMENTATION
#include <stb/sprintf.h>

#undef DARK_UNIT
#define DARK_UNIT "cbuffer"

bool dark_cbuffer_terminated_is(const size_t count_, char* const source_, size_t* const lenght_)
{
    //byte_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);
    //count_

    const char element = '\0';

    return dark_find_linear_index(&element, sizeof(char), count_, source_, (Dark_Compare)dark_compare_u8, lenght_);
}

size_t dark_cbuffer_snprintf(const size_t count_, char* const destination_, const char* const format_, ...)
{
    DARK_ASSERT((0 == count_) || (NULL != destination_), DARK_ERROR_NULL);
    DARK_ASSERT(NULL!= format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    const size_t result = stbsp_vsnprintf(destination_, count_, format_, args);
    va_end(args);

    return result;
}

size_t dark_cbuffer_vsnprintf(const size_t count_, char* const destination_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT((0 == count_) || (NULL != destination_), DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    const size_t result = stbsp_vsnprintf(destination_, count_, format_, arguments_);

    return result;
}
