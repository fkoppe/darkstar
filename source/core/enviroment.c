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

/*X X X X X X X X X X X X X X
X                           X
X   THIS IS A CORE FILE     X
X                           X
X X X X X X X X X X X X X X*/

#include "core_module.h"

#include <dark/core/core.h>

#include <assert.h>

#undef DARK_UNIT

void dark_location_print(const Dark_So so_, const Dark_Location location_)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);
    assert(NULL != location_.file);
    assert(NULL != location_.func);
    assert(0 != location_.line);
    assert(NULL != location_.date);
    assert(NULL != location_.time);

    dark_printf(so_, "file:\t%s\nfunc:\t%s\nline:\t%" PRIdMAX "\ndate:\t%s\ntime:\t%s\n\n", location_.file, location_.func, location_.line, location_.date, location_.time);
}

void dark_library_print(const Dark_So so_, const Dark_Library* const library_, const char* const module_, const char* const unit_)
{
    assert(___DARK_SO_MIN < so_ < ___DARK_SO_MAX);
    //library_
    //module_
    //unit_

    if(NULL == library_)
    {
        return;
    }

    dark_printf(so_, "----------\n\nname:\t%s\nvers:\t%" PRId8 ".%" PRId16 ".%" PRId8 ".%" PRId16 "\n\n", library_->name, dark_version_major(library_->version), dark_version_minor(library_->version), dark_version_stage(library_->version), dark_version_patch(library_->version));

    if(NULL != library_->configuration)
    {
        dark_printf(so_, "conf:\t%s\n\n", library_->configuration);
    }

    if(NULL != module_)
    {
        dark_printf(so_, "modl:\t%s\n", module_);
    }

    if(NULL != unit_)
    {
        dark_printf(so_, "unit:\t%s\n", unit_);
    }

    if(NULL != unit_ || module_)
    {
        dark_print(so_, "\n");
    }
}
