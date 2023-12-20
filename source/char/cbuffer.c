/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

#define STB_SPRINTF_IMPLEMENTATION
#include <stb/sprintf.h>

#undef DARK_UNIT
#define DARK_UNIT "cbuffer"

size_t dark_cbuffer_lenght(char* const cbuffer_, const size_t max_)
{
    DARK_ASSERT(NULL != cbuffer_, DARK_ERROR_NULL);

    for(size_t i = 0; i < max_; i++)
    {
        if('\0' == cbuffer_[i])
        {
            return i;
        }
    }

    DARK_EXIT_MSG(-1, DARK_ERROR_RUNTIME, "cbuffer lost integrity");
}

size_t dark_cbuffer_snprintf(char* const cbuffer_, const size_t max_, const char* const format_, ...)
{
    DARK_ASSERT(!cbuffer_ == !max_, DARK_ERROR_LOGIC);
    DARK_ASSERT(NULL!= format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    const size_t result = stbsp_vsnprintf(cbuffer_, max_, format_, args);
    va_end(args);

    return result;
}

size_t dark_cbuffer_vsnprintf(char* const cbuffer_, const size_t max_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(!cbuffer_ == !max_, DARK_ERROR_LOGIC);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    const size_t result = stbsp_vsnprintf(cbuffer_, max_, format_, arguments_);

    return result;
}
