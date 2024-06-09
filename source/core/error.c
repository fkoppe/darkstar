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

#undef DARK_UNIT

void dark_error_print(const Dark_So so_, const Dark_Error error_)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);
    //error_

    const Dark_Error* err = &error_;
    const char* info_arr[DARK_ERROR_DEPTH_MAX] = { 0 };
    bool info_is = false;

    dark_print(DARK_SO_ERR, "type:\t");

    for (size_t i = 0; i < DARK_ERROR_DEPTH_MAX; i++)
    {
        if (NULL == err)
        {
            break;
        }

        if (NULL != err->info)
        {
            info_is = true;
        }

        if (NULL != err->type)
        {
            dark_printf(DARK_SO_ERR, "%s_", err->type);
        }

        info_arr[DARK_ERROR_DEPTH_MAX - i - 1] = err->info;

        err = err->parent;
    }

    dark_print(DARK_SO_ERR, "error\n");

    if (!info_is)
    {
        return;
    }

    dark_print(DARK_SO_ERR, "\ninfo:");

    for (size_t i = 0; i < DARK_ERROR_DEPTH_MAX; i++)
    {
        if (NULL == info_arr[i])
        {
            continue;
        }

        dark_printf(DARK_SO_ERR, "\t%s\n", info_arr[i]);
    }
}
