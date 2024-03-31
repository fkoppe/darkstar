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

uint32_t dark_hash_murmur2_32(const size_t byte_, const void* const data_, const uint32_t seed_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);
    //seed_

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t hash = seed_ ^ byte_;

    for(size_t i = 0; i <= byte_ / sizeof(uint32_t); i++)
    {
        uint32_t k = *((uint32_t*)data_ + i);

        k *= m;
        k ^= k >> r;
        k *= m;
        hash *= m;
        hash ^= k;
    }

    switch(byte_ % 4)
    {
    case 3:
        hash ^= ((char*)data_)[2] << 16;
    case 2:
        hash ^= ((char*)data_)[1] << 8;
    case 1:
        hash ^= ((char*)data_)[0];
        hash *= m;
        break;
    };

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

uint32_t dark_hash_murmur2a_32(const size_t byte_, const void* const data_, const uint32_t seed_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);
    //seed_

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t hash = seed_;

    for(size_t i = 0; i <= byte_ / sizeof(uint32_t); i++)
    {
        uint32_t k = *((uint32_t*)data_ + i);

        k *= m;
        k ^= k >> r;
        k *= m;
        hash *= m;
        hash ^= k;
    }

    uint32_t t = 0;

    switch(byte_ % 4)
    {
    case 3:
        t ^= ((char*)data_)[2] << 16;
    case 2:
        t ^= ((char*)data_)[1] << 8;
    case 1:
        t ^= ((char*)data_)[0];
    };

    t *= m;
    t ^= t >> r;
    t *= m;
    hash *= m;
    hash ^= t;

    uint32_t l = byte_ * m;
    l ^= l >> r;
    l *= m;
    hash *= m;
    hash ^= l;

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

uint64_t dark_hash_murmur2a_64(const size_t byte_, const void* const data_, const uint64_t seed_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);
    //seed_

    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    uint64_t hash = seed_ ^ (byte_ * m);

    for(size_t i = 0; i <= byte_ / sizeof(uint64_t); i++)
    {
        uint64_t k = *((uint64_t*)data_ + i );

        k *= m;
        k ^= k >> r;
        k *= m;
        hash ^= k;
        hash *= m;
    }

    switch((byte_ % 8) & 7)
    {
    case 7:
        hash ^= ((uint64_t*)data_)[6] << 48;
    case 6:
        hash ^= ((uint64_t*)data_)[5] << 40;
    case 5:
        hash ^= ((uint64_t*)data_)[4] << 32;
    case 4:
        hash ^= ((uint64_t*)data_)[3] << 24;
    case 3:
        hash ^= ((uint64_t*)data_)[2] << 16;
    case 2:
        hash ^= ((uint64_t*)data_)[1] << 8;
    case 1:
        hash ^= ((uint64_t*)data_)[0];
        hash *= m;
        break;
    };

    hash ^= hash >> r;
    hash *= m;
    hash ^= hash >> r;

  return hash;
}
