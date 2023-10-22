/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023 Felix Koppe <fkoppe@web.de>                                  *
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

uint32_t dark_version_make(const uint8_t major_, const uint16_t minor_, const uint8_t stage_, const uint16_t patch_)
{
    assert(255 >= major_);
    assert(1023 >= minor_);
    assert(3 >= stage_);
    assert(4095 >= patch_);

    return DARK_VERSION_MAKE(major_, minor_, stage_, patch_);
}

uint8_t dark_version_major(const uint32_t version_)
{
    //version_

    return DARK_VERSION_MAJOR(version_);
}

uint16_t dark_version_minor(const uint32_t version_)
{
    //version_

    return DARK_VERSION_MINOR(version_);
}

uint8_t dark_version_stage(const uint32_t version_)
{
    //version_

    return DARK_VERSION_STAGE(version_);
}

uint16_t dark_version_patch(const uint32_t version_)
{
    //version_

    return DARK_VERSION_PATCH(version_);
}
