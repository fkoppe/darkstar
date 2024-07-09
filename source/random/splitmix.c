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
#define DARK_UNIT "splitmix"

uint32_t dark_random_splitmix_32(uint32_t* const random_)
{
    DARK_ASSERT(NULL != random_, DARK_ERROR_NULL);

    *random_ += 0x9e3779b9;

    uint32_t rand = *random_;
    rand = (rand ^ (rand >> 16)) * 0x85ebca6b;
    rand = (rand ^ (rand >> 13)) * 0xc2b2ae35;
    rand ^= (rand >> 16);

    return rand;
}

uint64_t dark_random_splitmix_64(uint64_t* const random_)
{
    DARK_ASSERT(NULL != random_, DARK_ERROR_NULL);

	*random_ += 0x9e3779b97f4a7c15;

    uint64_t rand = *random_;
	rand = (rand ^ (rand >> 30)) * 0xbf58476d1ce4e5b9;
	rand = (rand ^ (rand >> 27)) * 0x94d049bb133111eb;
    rand ^= (rand >> 31);

	return rand;
}
