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

#if !defined(___DARK___UUID4_H)
#define ___DARK___UUID4_H

#include <dark/char/cbuffer.h>
#include <dark/core/std.h>

#define DARK_UUID4_SIZE (sizeof("xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx") - 1)
#define DARK_UUID4_SIZE_TERMINATED sizeof("xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx")

typedef union Dark_Uuid4
{
    uint8_t byte[16];
    uint32_t quad[4];
    uint64_t oct[2];
} Dark_Uuid4;

static const Dark_Uuid4 DARK_UUID4_ZERO = { .oct = { 0, 0 } };

Dark_Uuid4 dark_uuid4_generate(uint64_t* random);

void dark_uuid4_write(Dark_Uuid4 uuid4, Dark_Cbuffer destination);

int dark_uuid4_compare(const Dark_Uuid4* element, const Dark_Uuid4* other);

#endif // !defined(___DARK___UUID4_H)
