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

#if !defined(___DARK___WEAK_REF_H)
#define ___DARK___WEAK_REF_H

#include <dark/container/ref_data.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

#define DARK_WEAK_REF_DATA(weak_ref, type) \
(*(type*)dark_weak_ref_data((weak_ref)))

Dark_Weak_Ref dark_weak_ref_create(Dark_Shared_Ref shared_ref);
void dark_weak_ref_destroy(Dark_Weak_Ref weak_ref);

Dark_Weak_Ref dark_weak_ref_copy(Dark_Weak_Ref weak_ref);

size_t dark_weak_ref_shared_count(Dark_Weak_Ref shared_ref);
size_t dark_weak_ref_weak_count(Dark_Weak_Ref shared_ref);

bool dark_weak_ref_valid_is(Dark_Weak_Ref shared_ref);
Dark_Shared_Ref dark_weak_ref_lock(Dark_Weak_Ref shared_ref);

size_t dark_weak_ref_byte(Dark_Weak_Ref weak_ref);

#endif // !defined(___DARK___WEAK_REF_H)
