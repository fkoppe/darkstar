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

#include "order_module.h"

#include <dark/core/core.h>
#include <dark/order/order.h>

#undef DARK_UNIT
#define DARK_UNIT "find"

bool dark_find_linear_index(const void* const element_, const size_t element_size_, const size_t count_, const void* const data_, const Dark_Compare compare_, size_t* const index_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);
    //index_

    for(size_t i = 0; i < count_; i++)
    {
        if(0 == compare_((char*)data_+ (i * element_size_), element_))
        {
            if(NULL != index_)
            {
                *index_ = i;
            }

            return true;
        }
    }

    return false;
}

bool dark_find_linear_reverse_index(const void* const element_, const size_t element_size_, const size_t count_, const void* const data_, const Dark_Compare compare_, size_t* const index_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);
    //index_

    for(size_t i = count_ - 1; i >= 0; i--)
    {
        if(0 == compare_((char*)data_ + (i * element_size_), element_))
        {
            if(NULL != index_)
            {
                *index_ = i;
            }

            return true;
        }
    }

    return false;
}

bool dark_find_binary_index(const void* const element_, const size_t element_size_, const size_t count_, const void* const data_, const Dark_Compare compare_, size_t* const index_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);
    //index_

    size_t low = 0;
    size_t high = count_;

    while(low <= high)
    {
        size_t mid = low + (high - low) / 2;

        switch(compare_((char*)data_ + (mid * element_size_), element_))
        {
            case -1:
                low = mid + 1;
                break;
            case 1:
                high = mid - 1;
                break;
            case 0:
                *index_ = mid;
                return true;
            default:
                DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        }
    }

    return false;
}

void* dark_find_linear(const void* const element_, const size_t element_size_, const size_t count_, void* const data_, const Dark_Compare compare_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    size_t index;

    if(!dark_find_linear_index(element_, element_size_, count_, data_, compare_, &index))
    {
        return NULL;
    }

    return (char*)data_ + (index * element_size_);
}

void* dark_find_linear_reverse(const void* const element_, const size_t element_size_, const size_t count_, void* const data_, const Dark_Compare compare_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    size_t index;

    if(!dark_find_linear_reverse_index(element_, element_size_, count_, data_, compare_, &index))
    {
        return NULL;
    }

    return (char*)data_ + (index * element_size_);
}

void* dark_find_binary(const void* const element_, const size_t element_size_, const size_t count_, void* const data_, const Dark_Compare compare_)
{
    DARK_ASSERT(element_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    size_t index;

    if(!dark_find_binary_index(element_, element_size_, count_, data_, compare_, &index))
    {
        return NULL;
    }

    return (char*)data_ + (index * element_size_);
}
