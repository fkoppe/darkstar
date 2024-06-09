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
#include <stdlib.h>

#undef DARK_UNIT

DARK_NORETURN void dark_assert(const Dark_Location location_, const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const condition_, const Dark_Error error_, const Dark_Message message_)
{
    assert(NULL != location_.file);
    assert(NULL != location_.func);
    assert(0 != location_.line);
    assert(NULL != location_.date);
    assert(NULL != location_.time);
    //library_
    //module_
    //unit_
    assert(NULL != condition_);
    //error_
    //message_

    dark_print(DARK_SO_ERR, "-------------------------ASSERT-------------------------\n");

    dark_message_print(DARK_SO_ERR, DARK_MESSAGE_ASSERT);

    dark_printf(DARK_SO_ERR, "\n\ncond:\t(%s) was false\n\n", condition_);

    dark_location_print(DARK_SO_ERR, location_);
    dark_library_print(DARK_SO_ERR, library_, module_, unit_);

    dark_print(DARK_SO_ERR, "----------\n\n");

    dark_error_print(DARK_SO_ERR, error_);

    dark_print(DARK_SO_ERR, "\n");

    dark_message_print(DARK_SO_ERR, message_);

    dark_print(DARK_SO_ERR, "\n--------------------------------------------------------\n");

    dark_flush(DARK_SO_ERR);

    abort();
}
