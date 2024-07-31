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

#include "time_module.h"

#include <dark/char/char.h>
#include <dark/core/core.h>
#include <dark/platform/platform.h>
#include <dark/time/time.h>

#include <time.h>

#undef DARK_UNIT
#define DARK_UNIT "stamp"

void dark_stamp_hms(const Dark_Cbuffer destination_)
{
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(DARK_STAMP_HMS_SIZE <= destination_.size, DARK_ERROR_OVERFLOW);

    const time_t now = time(NULL);
    DARK_ASSERT((time_t)(-1) != now, DARK_ERROR_API);

    struct tm* tm = localtime(&now);
    DARK_ASSERT(NULL != tm, DARK_ERROR_API);

    const size_t hcount = dark_digit_count_i32(tm->tm_hour);
    const size_t mcount = dark_digit_count_i32(tm->tm_min);
    const size_t scount = dark_digit_count_i32(tm->tm_sec);

    DARK_ASSERT(hcount <= 2 && hcount > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(mcount <= 2 && mcount > 0, DARK_ERROR_VALUE);
    DARK_ASSERT(scount <= 2 && scount > 0, DARK_ERROR_VALUE);

    const Dark_Cbuffer hlocation = { destination_.data + 2 -hcount, hcount };
    const Dark_Cbuffer mlocation = { destination_.data + 5 -mcount, mcount };
    const Dark_Cbuffer slocation = { destination_.data + 8 -scount, scount };

    if(hcount < 2)
    {
        destination_.data[0] = '0';
    }

    dark_digit_write_cbuffer_i(tm->tm_hour, hcount, hlocation);

    destination_.data[2] = ':';

    if(mcount < 2)
    {
        destination_.data[3] = '0';
    }

    dark_digit_write_cbuffer_i(tm->tm_min, mcount, mlocation);

    destination_.data[5] = ':';

    if(scount < 2)
    {
        destination_.data[6] = '0';
    }

    dark_digit_write_cbuffer_i(tm->tm_sec, scount, slocation);
}

void dark_stamp_hms_terminated(const Dark_Cbuffer destination_)
{
    DARK_ASSERT(NULL != destination_.data, DARK_ERROR_NULL);
    DARK_ASSERT(destination_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(DARK_STAMP_HMS_TERMINATED_SIZE <= destination_.size, DARK_ERROR_OVERFLOW);

    dark_stamp_hms(destination_);

    destination_.data[7] = '\0';
}
