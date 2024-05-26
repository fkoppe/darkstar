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

#include "core_helper.h"
#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#undef DARK_UNIT

void dark_terminate(const char* const file_, const char* const func_, const int64_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const configuration_, const char* const module_, const char* const unit_, const int64_t code_, const Dark_Error* const error_, const bool abort_is_, const char* const message_)
{
    assert(NULL != file_);
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != date_);
    assert(NULL != time_);
    //library_
    //configuration_
    //module_
    //unit_
    //code_
    assert(NULL != error_);
    //abort_is_
    //message_

    fputs("-------------------------TERMINATE-------------------------\n", stderr);

    if (abort_is_)
    {
        fputs("abort has been called\n\n", stderr);
    }
    else
    {
        fputs("exit has been called\n\n", stderr);
    }

    if (0 != code_)
    {
        fprintf(stderr, "code:\t%" PRId64 "\n\n", code_);
    }

    dark_core_enviroment_print(stderr, file_, func_, line_, date_, time_, library_, configuration_, module_, unit_);

    fputs("----------\n\n", stderr);

    dark_core_error_print(stderr, error_);

    if (NULL != message_)
    {
        fprintf(stderr, "\nmesg:\t%s\n", message_);
    }

    fputs("-----------------------------------------------------------\n", stderr);

    if (abort_is_)
    {
        abort();
    }
    else
    {
        exit(code_);
    }
}
