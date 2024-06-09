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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <string.h>

#undef DARK_UNIT

void dark_memset(void* const destination_, const char value_, const size_t count_)
{
    assert(NULL != destination_);
    //value_
    assert(count_ > 0);

    memset(destination_, value_, count_);
}

void dark_memcpy(void* const destination_, const void* const source_, const size_t count_)
{
    assert(NULL != destination_);
    assert(NULL != source_);
    assert(count_ > 0);

    memcpy(destination_, source_, count_);
}

void dark_memmove(void* const destination_, const void* const source_, const size_t count_)
{
    assert(NULL != destination_);
    assert(NULL != source_);
    assert(count_ > 0);

    memmove(destination_, source_, count_);
}

int8_t dark_memcmp(const void* const a_, const void* const b_, const size_t count_)
{
    assert(NULL != a_);
    assert(NULL != b_);
    assert(count_ > 0);

    return DARK_CAST(memcmp(a_, b_, count_), INT8_MIN, INT8_MAX);
}
