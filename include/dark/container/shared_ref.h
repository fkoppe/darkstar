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

#if !defined(___DARK___SHARED_REF_H)
#define ___DARK___SHARED_REF_H

#include <dark/container/ref_data.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

#define DARK_SHARED_REF_DATA(shared_ref, type) \
(*(type*)dark_shared_ref_data((shared_ref)))

Dark_Shared_Ref dark_shared_ref_create(Dark_Allocator* allocator, size_t byte, const void* data);
void dark_shared_ref_destroy(Dark_Shared_Ref shared_ref);

Dark_Shared_Ref dark_shared_ref_copy(Dark_Shared_Ref shared_ref);

size_t dark_shared_ref_shared_count(Dark_Shared_Ref shared_ref);
size_t dark_shared_ref_weak_count(Dark_Shared_Ref shared_ref);

Dark_Weak_Ref dark_shared_ref_unlock(Dark_Shared_Ref shared_ref);

size_t dark_shared_ref_byte(Dark_Shared_Ref shared_ref);
void* dark_shared_ref_data(Dark_Shared_Ref shared_ref);

#endif // !defined(___DARK___SHARED_REF_H)
