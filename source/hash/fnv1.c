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
#define DARK_UNIT "fnv1"

uint32_t dark_hash_fnv1_32(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    uint32_t hash = 0x811C9DC5;

    for (size_t i = 0; i < buffer_view_.byte; ++i)
    {
        hash = (hash * 0x1000193) ^ ((uint8_t*)buffer_view_.data)[i];
    }

    return hash;
}

uint64_t dark_hash_fnv1_64(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    uint64_t hash = 0xCBF29CE484222325;

    for (size_t i = 0; i < buffer_view_.byte; ++i)
    {
        hash = (hash * 0x100000001B3) ^ ((uint8_t*)buffer_view_.data)[i];
    }

    return hash;
}

uint32_t dark_hash_fnv1a_32(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    uint32_t hash = 0x811C9DC5;

    for (size_t i = 0; i < buffer_view_.byte; ++i)
    {
        hash = (hash ^ ((uint8_t*)buffer_view_.data)[i]) * 0x1000193;
    }

    return hash;
}

uint64_t dark_hash_fnv1a_64(const Dark_Buffer_View buffer_view_)
{
    DARK_ASSERT(buffer_view_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != buffer_view_.data, DARK_ERROR_NULL);

    uint64_t hash = 0xCBF29CE484222325;

    for (size_t i = 0; i < buffer_view_.byte; ++i)
    {
        hash = (hash ^ ((uint8_t*)buffer_view_.data)[i]) * 0x100000001B3;
    }

    return hash;
}
