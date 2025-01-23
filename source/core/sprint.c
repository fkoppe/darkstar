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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <stdlib.h>

#define STB_SPRINTF_IMPLEMENTATION
#include <stb/sprintf.h>

#undef DARK_UNIT

size_t dark_snprintf_notterminated(const size_t count_, char* const destination_, const char* const format_, ...)
{
    assert((0 == count_) || (NULL != destination_));
    assert(NULL != format_);

    va_list args;
    va_start(args, format_);
    const size_t result = dark_vsnprintf_notterminated(count_, destination_, format_, args);
    va_end(args);

    return result;
}

size_t dark_snprintf_terminated(const size_t count_, char* const destination_, const char* const format_, ...)
{
    assert((0 == count_) || (NULL != destination_));
    assert(NULL != format_);

    va_list args;
    va_start(args, format_);
    const size_t result = dark_vsnprintf_terminated(count_, destination_, format_, args);
    va_end(args);

    return result;
}

size_t dark_vsnprintf_notterminated(const size_t count_, char* const destination_, const char* const format_, va_list arguments_)
{
    assert((0 == count_) || (NULL != destination_));
    assert(NULL != format_);
    //arguments_

    stbsp__context context;

    if((count_ == 0) && !destination_)
    {
        context.length = 0;

        STB_SPRINTF_DECORATE(vsprintfcb)(stbsp__count_clamp_callback, &context, context.tmp, format_, arguments_);
    }
    else
    {
        int l;

        context.buf = destination_;
        context.count = count_;
        context.length = 0;

        STB_SPRINTF_DECORATE(vsprintfcb)(stbsp__clamp_callback, &context, stbsp__clamp_callback(0, &context, 0), format_, arguments_);
    }

    return context.length;
}

size_t dark_vsnprintf_terminated(const size_t count_, char* const destination_, const char* const format_, va_list arguments_)
{
    assert((0 == count_) || (NULL != destination_));
    assert(NULL != format_);
    //arguments_

   return stbsp_vsnprintf(destination_, count_, format_, arguments_);
}
