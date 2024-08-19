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

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/time/time.h>

#include <time.h>

#undef DARK_UNIT
#define DARK_UNIT "duration"

size_t dark_duration_s_to_ms(const size_t s_)
{
    //s_

    return DARK_DURATION_S_TO_MS(s_);
}

size_t dark_duration_s_to_ns(const size_t s_)
{
    //s_

    return DARK_DURATION_S_TO_NS(s_);
}

size_t dark_duration_ms_to_s(const size_t ms_)
{
    //ms_

    return DARK_DURATION_MS_TO_S(ms_);
}

size_t dark_duration_ms_to_ns(const size_t ms_)
{
    //ms_

    return DARK_DURATION_MS_TO_NS(ms_);
}

size_t dark_duration_ns_to_s(const size_t ns_)
{
    //ns_

    return DARK_DURATION_NS_TO_S(ns_);
}

size_t dark_duration_ns_to_ms(const size_t ns_)
{
    //ns_

    return DARK_DURATION_NS_TO_MS(ns_);
}
