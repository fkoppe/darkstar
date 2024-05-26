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

#include "core_helper.h"
#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>
#include <stdio.h>

#undef DARK_UNIT

void dark_core_enviroment_print(FILE* stream_, const char* file_, const char* func_, int64_t line_, const char* date_, const char* time_, const Dark_Library* library_, const char* configuration_, const char* module_, const char* unit_)
{
    assert(NULL != stream_);
    assert(NULL != file_);
    assert(NULL != func_);
    assert(0 != line_);
    assert(NULL != date_);
    assert(NULL != time_);
    //library_
    //configuration_
    //module_
    //unit_

    fprintf(stderr, "file:\t%s\nfunc:\t%s\nline:\t%" PRId64 "\ndate:\t%s\ntime:\t%s\n\n", file_, func_, line_, date_, time_);

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

void dark_core_error_print(FILE* stream_, const Dark_Error* error_)
{
    assert(NULL != stream_);
    assert(NULL != error_);

    const Dark_Error* err = error_;
    const char* info_arr[DARK_ERROR_LAYERS_MAX] = { NULL };
    bool info = false;

    fputs("type:\t", stderr);

    for (size_t i = 0; i < DARK_ERROR_LAYERS_MAX; i++)
    {
        if (NULL == err)
        {
            continue;
        }

        if (err->info)
        {
            info = true;
        }

        if (NULL != err->type)
        {
            fprintf(stderr, "%s_", err->type);
        }

        info_arr[DARK_ERROR_LAYERS_MAX - i - 1] = err->info;

        err = err->parent_error;
    }

    fputs("error\n", stderr);

    if (!info)
    {
        return;
    }

    fputs("\ninfo:", stderr);

    for (size_t i = 0; i < DARK_ERROR_LAYERS_MAX; i++)
    {
        if (NULL == info_arr[i])
        {
            continue;
        }

        fprintf(stderr, "\t%s\n", info_arr[i]);
    }
}
