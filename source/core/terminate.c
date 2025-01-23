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

#undef DARK_UNIT

DARK_NORETURN void dark_exit(const int8_t code_)
{
    exit(code_);
}

DARK_NORETURN void dark_abort(void)
{
    abort();
}

DARK_NORETURN void dark_terminate(const Dark_Location location_, const Dark_Library* const library_, const char* const module_, const char* const unit_, const int8_t code_, const Dark_Error error_, const Dark_Message message_, const bool abort_is_)
{
    assert(NULL != location_.file);
    assert(NULL != location_.func);
    assert(0 != location_.line);
    assert(NULL != location_.date);
    assert(NULL != location_.time);
    //library_
    //module_
    //unit_
    //code_
    //error_
    //message_

    dark_print(DARK_SO_ERR, "-------------------------TERMINATE-------------------------\n");

    if(abort_is_)
    {
        dark_message_print(DARK_SO_ERR, DARK_MESSAGE_ABORT);
    }
    else
    {
        dark_message_print(DARK_SO_ERR, DARK_MESSAGE_EXIT);
    }

    dark_print(DARK_SO_ERR, "\n\n");

    dark_location_print(DARK_SO_ERR, location_);
    dark_library_print(DARK_SO_ERR, library_, module_, unit_);

    dark_print(DARK_SO_ERR, "----------\n\n");

    dark_error_print(DARK_SO_ERR, error_);

    dark_print(DARK_SO_ERR, "\n");

    dark_message_print(DARK_SO_ERR, message_);

    dark_print(DARK_SO_ERR, "\n-----------------------------------------------------------\n");

    dark_flush(DARK_SO_ERR);

    if(abort_is_)
    {
        dark_abort();
    }
    else
    {
        dark_exit(code_);
    }
}
