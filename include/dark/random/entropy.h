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

#if !defined(___DARK___ENTROPY_H)
#define ___DARK___ENTROPY_H

#include <dark/core/essential.h>

typedef struct Dark_Entropy
{
    uint64_t next;
    uint64_t value[4];
} Dark_Entropy;

Dark_Entropy dark_entropy_seed();

void dark_entropy_randomize(Dark_Entropy* entropy);

uint32_t* dark_entropy_get_32(Dark_Entropy* entropy);
uint64_t* dark_entropy_get_64(Dark_Entropy* entropy);

#endif // !defined(___DARK___ENTROPY_H)
