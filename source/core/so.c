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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#undef DARK_UNIT

void dark_print(const Dark_So so_, const char* const cstring_)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);
    assert(NULL != cstring_);

    FILE* filestream = NULL;

    switch(so_)
    {
        case DARK_SO_OUT:
            filestream = stdout;
            break;
        case DARK_SO_ERR:
            filestream = stderr;
            break;
        default:
            abort();
    }

    fputs(cstring_, filestream);
}

void dark_printf(const Dark_So so_, const char* const format_, ...)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);
    assert(NULL != format_);

    FILE* filestream = NULL;

    switch(so_)
    {
        case DARK_SO_OUT:
            filestream = stdout;
            break;
        case DARK_SO_ERR:
            filestream = stderr;
            break;
        default:
            abort();
    }

    char buffer[DARK_PRINTF_MAX] = { 0 };

    va_list args;
    va_start(args, format_);
    const size_t result = dark_vsnprintf_terminated(DARK_PRINTF_MAX, buffer, format_, args);
    va_end(args);

    fwrite(buffer, sizeof(char), DARK_MIN(DARK_PRINTF_MAX, result), filestream);
}

void dark_flush(const Dark_So so_)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);

    FILE* filestream = NULL;

    switch(so_)
    {
        case DARK_SO_OUT:
            filestream = stdout;
            break;
        case DARK_SO_ERR:
            filestream = stderr;
            break;
        default:
            abort();
    }

    fflush(filestream);
}
