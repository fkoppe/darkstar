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

#include "math_module.h"

#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "abs"

uint8_t dark_abs_i8(const int8_t integer_)
{
    //interger_

    if(integer_ < 0)
    {
        return -integer_;
    }
    else
    {
        return integer_;
    }
}

uint16_t dark_abs_i16(const int16_t integer_)
{
    //interger_

    if(integer_ < 0)
    {
        return -integer_;
    }
    else
    {
        return integer_;
    }
}

uint32_t dark_abs_i32(const int32_t integer_)
{
    //interger_

    if(integer_ < 0)
    {
        return -integer_;
    }
    else
    {
        return integer_;
    }
}

uint64_t dark_abs_i64(const int64_t integer_)
{
    //interger_

    if(integer_ < 0)
    {
        return -integer_;
    }
    else
    {
        return integer_;
    }
}

uintmax_t dark_abs_imax(const intmax_t integer_)
{
    //interger_

    if(integer_ < 0)
    {
        return -integer_;
    }
    else
    {
        return integer_;
    }
}
