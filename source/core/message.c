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

#undef DARK_UNIT

void dark_message_print(const Dark_So so_, const Dark_Message message_)
{
    assert(___DARK_SO_MIN < so_ && so_ < ___DARK_SO_MAX);
    //message_

    const Dark_Message* msg = &message_;
    const char* data_arr[DARK_MESSAGE_DEPTH_MAX * 2] = { 0 };
    bool not_empty_is = false;
    size_t left = 0;
    size_t right = DARK_MESSAGE_DEPTH_MAX - 1;

    for (size_t i = 0; i < DARK_MESSAGE_DEPTH_MAX; i++)
    {
        if (NULL == msg)
        {
            break;
        }

        if(NULL != msg->prefix)
        {
            not_empty_is = true;
            data_arr[left] = msg->prefix;
            left++;
        }

        if(NULL != msg->suffix)
        {
            not_empty_is = true;
            data_arr[right] = msg->suffix;
            right--;
        }

        msg = msg->parent;
    }

    if (!not_empty_is)
    {
        return;
    }

    for (size_t i = 0; i < DARK_MESSAGE_DEPTH_MAX; i++)
    {
        if (NULL == data_arr[i])
        {
            continue;
        }

        dark_print(DARK_SO_ERR, data_arr[i]);
    }
}
