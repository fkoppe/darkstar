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

#include "platform_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/platform/platform.h>

#undef DARK_UNIT
#define DARK_UNIT "clock"

#if defined(___DARK_LINUX)
#define ___DARK_UNIX
#endif // defined(___DARK_LINUX)

#if defined(___DARK_DARWIN)
#define ___DARK_UNIX
#endif // defined(___DARK_DARWIN)

#if defined(___DARK_WINDOWS)
#include <dark/windows.h>
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
#include <time.h>
#endif // defined(___DARK_UNIX)

uint64_t dark_clock_ns(void)
{
#if defined(___DARK_WINDOWS)
    LARGE_INTEGER tick;
    LARGE_INTEGER freqency;

    bool b1 = QueryPerformanceCounter(&tick);
    bool b2 = QueryPerformanceFrequency(&freqency);

    DARK_ASSERT_CSTRING(b1, DARK_ERROR_PLATFORM, "QueryPerformanceCounter");
    DARK_ASSERT_CSTRING(b2, DARK_ERROR_PLATFORM, "QueryPerformanceFrequency");

    return (uint64_t)((tick.QuadPart * 1000) / (freqency.QuadPart / 1000000));
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    struct timespec time;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time);

    return (uint64_t)(time.tv_nsec + (time.tv_sec * 1000000000));
#endif // defined(___DARK_UNIX)
}

uint64_t dark_clock_ms(void)
{
    return dark_clock_ns() / DARK_MEGA;
}

uint64_t dark_clock_s(void)
{
    return dark_clock_ns() / DARK_GIGA;
}
