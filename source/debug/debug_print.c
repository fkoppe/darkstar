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

#include "debug_helper.h"
#include "debug_module.h"

#include <dark/core/core.h>
#include <dark/debug/debug.h>

#undef DARK_UNIT
#define DARK_UNIT "debug_print"

#include <stdarg.h>
#include <stdio.h>

void dark_debug_print_stdout(const char* const message_)
{
    DARK_ASSERT(NULL != message_, DARK_ERROR_NULL);

    fputs(message_, stdout);
}

void dark_debug_printf_stdout(const char* format_, ...)
{
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    vfprintf(stdout, format_, args);
    va_end(args);
}
