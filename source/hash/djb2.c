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
#define DARK_UNIT "djb2"

uint32_t dark_hash_djb2_32(const size_t byte_, const void* const data_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    uint32_t hash = 0x1505;

    for(size_t i = 0; i < byte_; i++)
    {
        hash = ((hash << 5) + hash) + ((char*)data_)[i];
    }

    return hash;
}

uint32_t dark_hash_djb2a_32(const size_t byte_, const void* const data_)
{
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    uint32_t hash = 0x1505;

    for(size_t i = 0; i < byte_; i++)
    {
       hash = ((hash << 5) + hash) ^ ((char*)data_)[i];
    }

    return hash;
}
