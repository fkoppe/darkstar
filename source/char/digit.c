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

#include "char_module.h"

#include <dark/char/char.h>
#include <dark/core/core.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "digit"

uint8_t dark_digit_get_u(uint64_t integer_, const size_t position_)
{
    //integer_
    DARK_ASSERT_MSG((integer_ % dark_ppow_u(10, position_)) > 0, DARK_ERROR_VALUE, "leading zero at position");

    integer_ /= dark_ppow_u(10, position_);

    return integer_ % 10;
}

uint8_t dark_digit_get_i(const int64_t integer_, const size_t position_)
{
    //integer_
    DARK_ASSERT_MSG((integer_ % dark_ppow_u(10, position_)) > 0, DARK_ERROR_VALUE, "leading zero at position");

    return dark_digit_get_u(dark_abs_i64(integer_), position_);
}

char dark_digit_to_char(const uint8_t digit_)
{
    DARK_ASSERT_MSG(digit_ < 10, DARK_ERROR_RANGE, "digit has to be <10");

    switch(digit_)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    default:
        DARK_EXIT_ERROR(-1, DARK_ERROR_UNKNOWN);
        return 'x';
    }
}

size_t dark_digit_count_u8(uint8_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U8; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_U8;
        }
    }

    return count;
}

size_t dark_digit_count_u16(uint16_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U16; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_U16;
        }
    }

    return count;
}

size_t dark_digit_count_u32(uint32_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U32; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_U32;
        }
    }

    return count;
}

size_t dark_digit_count_u64(uint64_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U64; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_U64;
        }
    }

    return count;
}

size_t dark_digit_count_i8(int8_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I8; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_I8;
        }
    }

    return count;
}

size_t dark_digit_count_i16(int16_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I16; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_I16;
        }
    }

    return count;
}

size_t dark_digit_count_i32(int32_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I32; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_I32;
        }
    }

    return count;
}

size_t dark_digit_count_i64(int64_t integer_)
{
    //integer_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I64; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_MAX_I64;
        }
    }

    return count;
}

void dark_digit_to_cbuffer_u(uint64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    for(size_t i = 0; i < count_; i++)
    {
        if(integer_ > 0)
        {
            destination_[count_ - i - 1] = dark_digit_to_char(integer_ % 10);
        }
        else
        {
            destination_[count_ - i - 1] = '0';
        }

        integer_ /= 10;
    }
}

void dark_digit_to_cbuffer_u_terminated(const uint64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    dark_digit_to_cbuffer_u(integer_, count_, destination_);

    destination_[count_] = '\0';
}

void dark_digit_to_cbuffer_i(const int64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    dark_digit_to_cbuffer_u(dark_abs_i64(integer_), count_, destination_);
}

void dark_digit_to_cbuffer_i_terminated(const int64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    dark_digit_to_cbuffer_i(integer_, count_, destination_);

    destination_[count_] = '\0';
}
