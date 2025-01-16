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

#include "math_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>

#undef DARK_UNIT
#define DARK_UNIT "log"

uint8_t dark_log_u8(const uintmax_t base_, const uint8_t value_)
{
    DARK_ASSERT(base_ >= 2, DARK_ERROR_MATH);

    uint8_t value = value_;
    uint8_t log = 0;

    while (value >= base_)
    {
        value /= base_;
        log++;
    }

    return log;
}

uint8_t dark_log_u16(const uintmax_t base_, const uint16_t value_)
{
    DARK_ASSERT(base_ >= 2, DARK_ERROR_MATH);

    uint16_t value = value_;
    uint8_t log = 0;

    while (value >= base_)
    {
        value /= base_;
        log++;
    }

    return log;
}

uint8_t dark_log_u32(const uintmax_t base_, const uint32_t value_)
{
    DARK_ASSERT(base_ >= 2, DARK_ERROR_MATH);

    uint32_t value = value_;
    uint8_t log = 0;

    while (value >= base_)
    {
        value /= base_;
        log++;
    }

    return log;
}

uint8_t dark_log_u64(const uintmax_t base_, const uint64_t value_)
{
    DARK_ASSERT(base_ >= 2, DARK_ERROR_MATH);

    uint64_t value = value_;
    uint8_t log = 0;

    while (value >= base_)
    {
        value /= base_;
        log++;
    }

    return log;
}

uint8_t dark_log_zu(const uintmax_t base_, const size_t value_)
{
    DARK_ASSERT(base_ >= 2, DARK_ERROR_MATH);

    size_t value = value_;
    uint8_t log = 0;

    while (value >= base_)
    {
        value /= base_;
        log++;
    }

    return log;
}
