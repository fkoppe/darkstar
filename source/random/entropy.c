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
#define DARK_UNIT "entropy"

Dark_Entropy dark_entropy_seed(void)
{
    Dark_Entropy entropy;

    entropy.next = 0;

    //TODO

    return entropy;
}

void dark_entropy_randomize(Dark_Entropy* entropy)
{
    DARK_ASSERT(NULL != entropy, DARK_ERROR_NULL);

    //TODO
}

uint32_t* dark_entropy_get_32(Dark_Entropy* entropy)
{
    DARK_ASSERT(NULL != entropy, DARK_ERROR_NULL);

    entropy->next++;

    return (uint32_t*)(((uint8_t*)entropy->pool) + (entropy->next % 28));
}

uint64_t* dark_entropy_get_64(Dark_Entropy* entropy)
{
    DARK_ASSERT(NULL != entropy, DARK_ERROR_NULL);

    entropy->next++;

    return (uint64_t*)(((uint8_t*)entropy->pool) + (entropy->next % 24));
}
