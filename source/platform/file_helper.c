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
#include <dark/platform/platform.h>

#undef DARK_UNIT
#define DARK_UNIT "file_helper"

void dark_file_modifier_get(const Dark_File_Mode mode_, const Dark_File_Flag flag_, char* const destination_)
{
    DARK_ASSERT(___DARK_FILE_MODE_MIN < mode_ && mode_ < ___DARK_FILE_MODE_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(___DARK_FILE_FLAG_MIN < flag_ && flag_ < ___DARK_FILE_FLAG_MAX, DARK_ERROR_ENUM);
    DARK_ASSERT(NULL != destination_, DARK_ERROR_NULL);

    switch (mode_)
    {
    case DARK_FILE_MODE_READ:
        *destination_ = 'r';
        break;
    case DARK_FILE_MODE_WRITE:
        *destination_ = 'w';
        break;
    case DARK_FILE_MODE_APPEND:
        *destination_ = 'a';
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }

    size_t i = 1;

    if (flag_ & DARK_FILE_FLAG_BINARY)
    {
        destination_[i] = 'b';
        i++;
    }

    if (flag_ & DARK_FILE_FLAG_UPDATE)
    {
        destination_[i] = '+';
        i++;
    }
}
