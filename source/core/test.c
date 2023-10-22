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

#undef DARK_UNIT

void dark_test(const char* const condition_, const size_t num_, const char* const name_, const int64_t integer_, const uint64_t uinteger_, const char* const cstring_)
{
    assert(NULL != condition_);
    //num_
    assert(!num_ || NULL != name_);
    //integer_
    //uinteger_
    //cstring

    fprintf(stderr, "\n\n-------------------------TEST-------------------------\ntest failed - exit has been called\n\ncond:\t(%s) was false\n\n", condition_);
    
    switch(num_)
    {
    case 1:
        fprintf(stderr, "%" PRId64 " = %s\n\n", integer_, name_);
        break;
    case 2:
        fprintf(stderr, "%" PRIu64 " = %s\n\n", uinteger_, name_);
        break;
    case 3:
        fprintf(stderr, "%s" " = %s\n\n", cstring_, name_);
        break;
    default:
        //nothing
    }

    fputs("------------------------------------------------------\n\n\n", stderr);

    exit(-1);
}
