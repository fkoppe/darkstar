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

#undef DARK_UNIT
#define DARK_UNIT "cstring"

size_t dark_cstring_lenght(const char* const cstring_)
{
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);
    
    for(size_t i = 0; i < DARK_CSTRING_LENGHT_MAX; i++)
    {
        if('\0' == cstring_[i])
        {
            return i;
        }
    }
    
    DARK_EXIT_MSG(-1, DARK_ERROR_RUNTIME, "cstring lost integrity");
}
