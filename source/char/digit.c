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
#define DARK_UNIT "digit"

uint8_t dark_digit_get(const int32_t integer_, const size_t position_)
{
    uint16_t num = abs(integer_);
    
    num /= pow(10, position_);
    
    return num % 10;
}

size_t dark_digit_count(const int32_t integer_)
{
    size_t count = 1;
    int32_t num = integer_;
    
    while(num /= 10)
    {
        count++;
    }
    
    return count;
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

void dark_digit_int32_to_char_arr(int32_t integer_, size_t count_, char* destination_)
{
    uint64_t num = abs(integer_);
    
    for(size_t i = 0; i < count_; i++)
    {
        if(num > 0)
        {
            destination_[count_ - i - 1] = dark_digit_to_char(num % 10);
        }
        else
        {
            destination_[count_ - i - 1] = '0';
        }
        
        num /= 10;
    }
}

void dark_digit_int32_to_char_arr_terminated(int32_t integer_, size_t count_, char* destination_)
{
    dark_digit_int32_to_char_arr(integer_, count_, destination_);
    
    destination_[count_] = '\0';
}
