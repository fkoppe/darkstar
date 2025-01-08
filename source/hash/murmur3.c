/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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
#define DARK_UNIT "murmur3"

uint32_t dark_hash_murmur3_32(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    return dark_hash_murmur3_seed_32(buffer_view_, 123);
}

uint32_t dark_hash_murmur3_seed_32(const Dark_Buffer_View buffer_view_, const uint32_t seed_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);
    //seed_

    uint32_t c1 = 0xcc9e2d51;
    uint32_t c2 = 0x1b873593;
    uint32_t r1 = 15;
    uint32_t h = seed_;
    uint32_t k = 0;

    const uint8_t* const data = ((uint8_t*)buffer_view_.data + ((buffer_view_.byte / 4) * sizeof(uint32_t)));

    for(size_t i = 0; i < buffer_view_.byte / 4; i++)
    {
        k = ((uint32_t*)data)[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
        h = (h << 13) | (h >> (32 - 13));
        h = h * 5 + 0xe6546b64;
    }

    k = 0;

    switch (buffer_view_.byte % 4)
    {
    case 3:
        k ^= data[2] << 16;
    case 2:
        k ^= data[1] << 8;
    case 1:
        k ^= data[0];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;
        h ^= k;
        break;
    }

    h ^= buffer_view_.byte;
    h ^= (h >> 16);
    h *= 0x85ebca6b;
    h ^= (h >> 13);
    h *= 0xc2b2ae35;
    h ^= (h >> 16);

    return h;
}
