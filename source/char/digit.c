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

uint8_t dark_digit_get_u(uint64_t number_, const size_t position_)
{
    //number_
    DARK_ASSERT_MESSAGE(dark_digit_count_umax(number_) > position_, DARK_ERROR_VALUE, DARK_MESSAGE_DIGIT_LEADING_ZERO);

    number_ /= dark_upow_u(10, position_);

    return number_ % 10;
}

uint8_t dark_digit_get_i(const int64_t number_, const size_t position_)
{
    //number_
    DARK_ASSERT_MESSAGE(dark_digit_count_i64(number_) > position_, DARK_ERROR_VALUE, DARK_MESSAGE_DIGIT_LEADING_ZERO);

    return dark_digit_get_u(dark_abs_i64(number_), position_);
}

char dark_digit_to_char(const uint8_t digit_)
{
    DARK_ASSERT_CSTRING(digit_ < 10, DARK_ERROR_RANGE, "digit has to be <10");

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
    }
}

size_t dark_digit_count_u8(uint8_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U8; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_u16(uint16_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U16; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_u32(uint32_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U32; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_u64(uint64_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_U64; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_umax(uintmax_t number_)
{
    //number_

    size_t count = 1;

    while (number_ /= 10)
    {
        count++;
    }

    return count;
}

size_t dark_digit_count_zu(size_t number_)
{
    //number_

    size_t count = 1;

    while (number_ /= 10)
    {
        count++;
    }

    return count;
}

size_t dark_digit_count_i8(int8_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I8; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_i16(int16_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I16; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_i32(int32_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I32; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_i64(int64_t number_)
{
    //number_

    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_MAX_I64; i++)
    {
        if(number_ /= 10)
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

size_t dark_digit_count_imax(intmax_t number_)
{
    //number_

    size_t count = 1;

    while (number_ /= 10)
    {
        count++;
    }

    return count;
}

void dark_digit_write_u(uintmax_t number_, const size_t digit_count_, const Dark_Cbuffer destination_)
{
    //number_
    DARK_ASSERT(digit_count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(digit_count_ <= destination_.size, DARK_ERROR_OVERFLOW);

    for(size_t i = 0; i < digit_count_; i++)
    {
        if(number_ > 0)
        {
            destination_.data[digit_count_ - i - 1] = dark_digit_to_char(number_ % 10);
        }
        else
        {
            destination_.data[digit_count_ - i - 1] = '0';
        }

        number_ /= 10;
    }
}

void dark_digit_write_u_terminated(const uintmax_t number_, const size_t digit_count_, const Dark_Cbuffer destination_)
{
    //number_
    DARK_ASSERT(digit_count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(digit_count_ < destination_.size, DARK_ERROR_OVERFLOW);

    dark_digit_write_u(number_, digit_count_, destination_);

    destination_.data[digit_count_] = '\0';
}

void dark_digit_write_i(const intmax_t number_, const size_t digit_count_, const Dark_Cbuffer destination_)
{
    //number_
    DARK_ASSERT(digit_count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(digit_count_ <= destination_.size, DARK_ERROR_OVERFLOW);

    dark_digit_write_u(dark_abs_i64(number_), digit_count_, destination_);
}

void dark_digit_write_i_terminated(const intmax_t number_, const size_t digit_count_, const Dark_Cbuffer destination_)
{
    //number_
    DARK_ASSERT(digit_count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(digit_count_ < destination_.size, DARK_ERROR_OVERFLOW);

    dark_digit_write_i(number_, digit_count_, destination_);

    destination_.data[digit_count_] = '\0';
}
