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
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "digit"

uint8_t dark_digit_uint_get(uint64_t integer_, const size_t position_)
{
    //integer_
    //position_

    integer_ /= dark_ppow_uint(10, position_);

    return integer_ % 10;
}

uint8_t dark_digit_int_get(const int64_t integer_, const size_t position_)
{
    //integer_
    //position_

    return dark_digit_uint_get(dark_abs_int64(integer_), position_);
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
    }
}

size_t dark_digit_count_uint8(uint8_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_UINT8_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_UINT8_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_uint16(uint16_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_UINT16_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_UINT16_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_uint32(uint32_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_UINT32_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_UINT32_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_uint64(uint64_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_UINT64_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_UINT64_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_int8(int8_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_INT8_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_INT8_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_int16(int16_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_INT16_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_INT16_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_int32(int32_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_INT32_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_INT32_MAX;
        }
    }

    return count;
}

size_t dark_digit_count_int64(int64_t integer_)
{
    //integer_
    
    size_t count = 1;

    for (size_t i = 0; i < DARK_DIGIT_COUNT_INT64_MAX; i++)
    {
        if(integer_ /= 10)
        {
            count++;
        }
        else
        {
            i = DARK_DIGIT_COUNT_INT64_MAX;
        }
    }

    return count;
}

void dark_digit_uint_to_char_arr(uint64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    //count_
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

void dark_digit_uint_to_char_arr_terminated(const uint64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    //count_
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);
    
    dark_digit_uint_to_char_arr(integer_, count_, destination_);

    destination_[count_] = '\0';
}

void dark_digit_int_to_char_arr(const int64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    //count_
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);
    
    dark_digit_uint_to_char_arr(dark_abs_int64(integer_), count_, destination_);
}

void dark_digit_int_to_char_arr_terminated(const int64_t integer_, const size_t count_, char* const destination_)
{
    //integer_
    //count_
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);
    
    dark_digit_int_to_char_arr(integer_, count_, destination_);

    destination_[count_] = '\0';
}
