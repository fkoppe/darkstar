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

#include "hash_module.h"

#include <dark/hash/hash.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "superfast"

uint32_t dark_hash_superfast_32(const size_t byte_, const void* const data_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    if(0 == byte_)
    {
        return 0;
    }

    const uint16_t* data = data_;
    const uint32_t rem = byte_ & 3;

    uint32_t hash = byte_;
    uint32_t index = 0;
    uint32_t temp = 0;

    for(size_t i = byte_ >> 2; i > 0; i--)
    {
        hash += *(data + index);
        temp = (uint32_t)((*(data + index + 2)) << 11) ^ hash;
        hash = (hash << 16) ^ temp;
        index += 2;
        hash += hash >> 11;
    }

    switch (rem)
    {
        case 1:
            hash += (intptr_t)(data + index);
            hash ^= hash << 10;
            hash += hash >> 1;
            break;
        case 2:
            hash += *(data + index);
            hash ^= hash << 11;
            hash += hash >> 17;
            break;
        case 3:
            hash += *(data + index);
            hash ^= hash << 16;
            hash ^= ((intptr_t)(data + index + 2)) << 18;
            hash += hash >> 11;
            break;
    }

    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}
