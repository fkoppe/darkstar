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

#include "algorithm_module.h"

#include <dark/algorithm/algorithm.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "sort"

bool dark_sort_is(const Dark_Array_View array_view_, const Dark_Compare compare_)
{
    DARK_ASSERT(array_view_.element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_view_.data != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);

    for(size_t i = 0; i < array_view_.size - 1; i++)
    {
        if(0 < compare_((uint8_t*)array_view_.data + (i * array_view_.element_byte), (uint8_t*)array_view_.data + ((i + 1) * array_view_.element_byte)))
        {
            return false;
        }
    }

    return true;
}

void dark_sort_insertion(const Dark_Array array_, const Dark_Compare compare_, void* const element_buffer_)
{
    DARK_ASSERT(array_.element_byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(array_.data != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(compare_ != NULL, DARK_ERROR_NULL);
    DARK_ASSERT(element_buffer_ != NULL, DARK_ERROR_NULL);

    for(size_t i = 1; i < array_.size; i++)
    {
        dark_memcpy(element_buffer_, (uint8_t*)array_.data + (i * array_.element_byte), array_.element_byte);

        size_t iter = i;

        while (iter > 0 && 0 < compare_((uint8_t*)array_.data+ ((iter - 1) * array_.element_byte), element_buffer_))
        {
            dark_memcpy((uint8_t*)array_.data + (iter * array_.element_byte), (uint8_t*)array_.data + ((iter - 1) * array_.element_byte), array_.element_byte);
            iter--;
        }

        dark_memcpy((uint8_t*)array_.data + (iter * array_.element_byte), element_buffer_, array_.element_byte);
    }
}


















