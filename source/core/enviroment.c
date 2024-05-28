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
#include <stdio.h>

#undef DARK_UNIT

void dark_core_enviroment_print_stderr(const char* const file_, const char* const func_, const intmax_t line_, const char* const date_, const char* const time_, const Dark_Library* const library_, const char* const configuration_, const char* const module_, const char* const unit_)
{
    assert(NULL != file_);
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != date_);
    assert(NULL != time_);
    //library_
    //configuration_
    //module_
    //unit_

    fprintf(stderr, "file:\t%s\nfunc:\t%s\nline:\t%" PRIdMAX "\ndate:\t%s\ntime:\t%s\n\n", file_, func_, line_, date_, time_);

    if (NULL != library_)
    {
        fprintf(stderr, "----------\n\nname:\t%s\nvers:\t%" PRId8 ".%" PRId16 ".%" PRId8 ".%" PRId16 "\n\n", library_->name, dark_version_major(library_->version), dark_version_minor(library_->version), dark_version_stage(library_->version), dark_version_patch(library_->version));
    }

    if (NULL != configuration_)
    {
        fprintf(stderr, "conf:\t%s\n\n", configuration_);
    }

    if (NULL != module_)
    {
        fprintf(stderr, "modl:\t%s\n", module_);
    }

    if (NULL != unit_)
    {
        fprintf(stderr, "unit:\t%s\n", unit_);
    }

    if (NULL != unit_ || module_)
    {
        fputs("\n", stderr);
    }
}
