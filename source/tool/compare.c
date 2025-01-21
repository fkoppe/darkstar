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

#include "tool_module.h"

#include <dark/core/core.h>
#include <dark/tool/tool.h>

#undef DARK_UNIT
#define DARK_UNIT "compare"

int8_t dark_compare_u8(const uint8_t* const element_, const uint8_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_u16(const uint16_t* const element_, const uint16_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_u32(const uint32_t* const element_, const uint32_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_u64(const uint64_t* const element_, const uint64_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_umax(const uintmax_t* const element_, const uintmax_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_zu(const size_t* const element_, const size_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_i8(const int8_t* const element_, const int8_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_i16(const int16_t* const element_, const int16_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_i32(const int32_t* const element_, const int32_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_i64(const int64_t* const element_, const int64_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_imax(const intmax_t* const element_, const intmax_t* const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int8_t dark_compare_p(const void** const element_, const void** const other_)
{
    DARK_ASSERT(NULL != element_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != other_, DARK_ERROR_NULL);

    if(*element_ < *other_)
    {
        return -1;
    }
    else if(*element_ > *other_)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
