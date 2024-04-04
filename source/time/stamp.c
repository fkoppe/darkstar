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

#include <time.h>

#undef DARK_UNIT
#define DARK_UNIT "stamp"

void dark_stamp_hms(char* const destination_)
{
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

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

    if(hcount < 2)
    {
        destination_[0] = '0';
    }

    dark_digit_to_cbuffer_i(tm->tm_hour, hcount, destination_ + 2 - hcount);

    destination_[2] = ':';

    if(mcount < 2)
    {
        destination_[3] = '0';
    }

    dark_digit_to_cbuffer_i(tm->tm_min, mcount, destination_ + 5 - mcount);

    destination_[5] = ':';

    if(scount < 2)
    {
        destination_[6] = '0';
    }

    dark_digit_to_cbuffer_i(tm->tm_sec, scount, destination_ + 8 - scount);
}

void dark_stamp_hms_terminated(char* const destination_)
{
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    dark_stamp_hms(destination_);

    destination_[7] = '\0';
}
