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
#define DARK_UNIT "murmur2"

uint32_t dark_hash_murmur2_32(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    return dark_hash_murmur2_seed_32(buffer_view_, 123);
}

uint32_t dark_hash_murmur2a_32(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    return dark_hash_murmur2_seed_32(buffer_view_, 123);
}

uint64_t dark_hash_murmur2a_64(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    return dark_hash_murmur2_seed_32(buffer_view_, 123);
}

uint32_t dark_hash_murmur2_seed_32(const Dark_Buffer_View buffer_view_, const uint32_t seed_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);
    //seed_

    const uint32_t m = 0x5bd1e995;
    const int32_t r = 24;

    uint32_t hash = seed_ ^ buffer_view_.byte;

    for(size_t i = 0; i <= buffer_view_.byte / sizeof(uint32_t); i++)
    {
        uint32_t k = *((uint32_t*)buffer_view_.data + i);

        k *= m;
        k ^= k >> r;
        k *= m;
        hash *= m;
        hash ^= k;
    }

    switch(buffer_view_.byte % 4)
    {
    case 3:
        hash ^= ((uint8_t*)buffer_view_.data)[2] << 16;
    case 2:
        hash ^= ((uint8_t*)buffer_view_.data)[1] << 8;
    case 1:
        hash ^= ((uint8_t*)buffer_view_.data)[0];
        hash *= m;
        break;
    };

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

uint32_t dark_hash_murmur2a_seed_32(const Dark_Buffer_View buffer_view_, const uint32_t seed_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);
    //seed_

    const uint32_t m = 0x5bd1e995;
    const int32_t r = 24;

    uint32_t hash = seed_;

    for(size_t i = 0; i <= buffer_view_.byte / sizeof(uint32_t); i++)
    {
        uint32_t k = *((uint32_t*)buffer_view_.data + i);

        k *= m;
        k ^= k >> r;
        k *= m;
        hash *= m;
        hash ^= k;
    }

    uint32_t t = 0;

    switch(buffer_view_.byte % 4)
    {
    case 3:
        t ^= ((uint8_t*)buffer_view_.data)[2] << 16;
    case 2:
        t ^= ((uint8_t*)buffer_view_.data)[1] << 8;
    case 1:
        t ^= ((uint8_t*)buffer_view_.data)[0];
    };

    t *= m;
    t ^= t >> r;
    t *= m;
    hash *= m;
    hash ^= t;

    uint32_t l = buffer_view_.byte * m;
    l ^= l >> r;
    l *= m;
    hash *= m;
    hash ^= l;

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

uint64_t dark_hash_murmur2a_seed_64(const Dark_Buffer_View buffer_view_, const uint64_t seed_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);
    //seed_

    const uint64_t m = 0xc6a4a7935bd1e995;
    const int32_t r = 47;

    uint64_t hash = seed_ ^ (buffer_view_.byte * m);

    const uint64_t* data = buffer_view_.data;
    const uint64_t* end = data + (buffer_view_.byte / sizeof(uint64_t));

    while(data != end)
    {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        hash ^= k;
        hash *= m;
    }

    switch(buffer_view_.byte & 7)
    {
    case 7:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[6]) << 48;
    case 6:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[5]) << 40;
    case 5:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[4]) << 32;
    case 4:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[3]) << 24;
    case 3:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[2]) << 16;
    case 2:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[1]) << 8;
    case 1:
        hash ^= ((uint64_t)((uint8_t*)buffer_view_.data)[0]);
        hash *= m;
    };

    hash ^= hash >> r;
    hash *= m;
    hash ^= hash >> r;

    return hash;
}
