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

Dark_Entropy dark_entropy_seed()
{
    Dark_Entropy entropy;

    //TODO

    entropy.value[0] = 42;
    entropy.value[1] = 99;
    entropy.value[2] = 13;
    entropy.value[3] = 19;

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

    //TODO

    return (uint32_t*)entropy;
}

uint64_t* dark_entropy_get_64(Dark_Entropy* entropy)
{
    DARK_ASSERT(NULL != entropy, DARK_ERROR_NULL);

    //TODO

    return (uint64_t*)entropy;
}
