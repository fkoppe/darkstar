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

#if !defined(___DARK___VERSION_H)
#define ___DARK___VERSION_H

#include <dark/core/essential.h>

#define DARK_VERSION_MAKE(major, minor, stage, patch) \
((((uint32_t)(major)) << 24) | (((uint32_t)(minor)) << 15) | (((uint32_t)(stage)) << 12) | ((uint32_t)(patch)))

#define DARK_VERSION_MAJOR(version) \
((uint32_t)(version) >> 24)

#define DARK_VERSION_MINOR(version) \
(((uint32_t)(version) >> 15) & 0x3FF)

#define DARK_VERSION_STAGE(version) \
(((uint32_t)(version) >> 12) & 0x7)

#define DARK_VERSION_PATCH(version) \
((uint32_t)(version) & 0xFFF)

uint32_t dark_version_make(uint8_t major, uint16_t minor, uint8_t stage, uint16_t patch);

uint8_t dark_version_major(uint32_t version);
uint16_t dark_version_minor(uint32_t version);
uint8_t dark_version_stage(uint32_t version);
uint16_t dark_version_patch(uint32_t version);

#endif // !defined(___DARK___VERSION_H)
