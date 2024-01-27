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

#include "random_module.h"

#include <dark/core/core.h>
#include <dark/random/random.h>

#undef DARK_UNIT
#define DARK_UNIT "uuid4"

Dark_Uuid4 dark_uuid4_generate(uint64_t* const random_)
{
    DARK_ASSERT(NULL != random_, DARK_ERROR_NULL);

    Dark_Uuid4 uuid4;

    uuid4.oct[0] = dark_prng_splitmix_64(random_);
    uuid4.oct[1] = dark_prng_splitmix_64(random_);

    uuid4.byte[6] = (uuid4.byte[6] & 0xf) | 0x40;
    uuid4.byte[8] = (uuid4.byte[8] & 0x3f) | 0x80;

    return uuid4;
}

void dark_uuid4_write(const Dark_Uuid4 uuid4_, char* const destination_)
{
    //uuid4_
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    const char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    const size_t group[] = { 8, 4, 4, 4, 12 };
    size_t index = 0;

    char* ptr = destination_;

    for (size_t i = 0; i < (sizeof(group) / sizeof(group[0])); i++)
    {
        for (size_t j = 0; j < group[i]; j += 2)
        {
            uint8_t byte = uuid4_.byte[index++];

            *ptr++ = hex[byte >> 4];
            *ptr++ = hex[byte & 0xf];
        }

        *ptr++ = '-';
    }

    *--ptr = 0;
}
