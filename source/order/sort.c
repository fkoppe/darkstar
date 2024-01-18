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
#define DARK_UNIT "sort"

#include <string.h>

bool dark_sort_is(const size_t element_size_, const size_t count_, void* const data_, const DARK_Compare compare_)
{
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    //count_
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    for(size_t i = 0; i < count_ - 1; i++)
    {
        if(0 < compare_(data_ + (i * element_size_), data_ + ((i + 1) * element_size_)))
        {
            return false;
        }
    }

    return true;
}

void dark_sort_insertion(const size_t element_size_, const size_t count_, void* const data_, const DARK_Compare compare_)
{
    DARK_ASSERT(element_size_ > 0, DARK_ERROR_ZERO);
    //count_
    DARK_ASSERT(data_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    void* elem = malloc(element_size_);
    DARK_ASSERT(NULL != elem, DARK_ERROR_ALLOCATION);

    for(size_t i = 1; i < count_; i++)
    {
        memcpy(elem, data_ + (i * element_size_), element_size_);

        size_t iter = i;

        while (iter > 0 && 0 < compare_(data_ + ((iter - 1) * element_size_), elem))
        {
            memcpy(data_ + (iter * element_size_), data_ + ((iter - 1) * element_size_), element_size_);
            iter--;
        }

        memcpy(data_ + (iter * element_size_), elem, element_size_);
    }

    free(elem);
}


















