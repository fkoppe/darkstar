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

#if !defined(___DARK___LINEAR_MAP_H)
#define ___DARK___LINEAR_MAP_H

#include <dark/container/vector.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>
#include <dark/tool/compare.h>
#include <dark/tool/foreach.h>
#include <dark/tool/iterator.h>

#define DARK_LINEAR_MAP_VALUE(linear_map, key, type) \
(*(type*)dark_linear_map_value((linear_map), (key)))

#define DARK_LINEAR_MAP_SIZE_MAX 32

typedef struct Dark_Linear_Map Dark_Linear_Map;

void dark_linear_map_construct_capacity(Dark_Allocator* allocator, Dark_Linear_Map* linear_map, Dark_Compare compare, size_t key_byte, size_t value_byte, size_t capacity);
void dark_linear_map_construct(Dark_Allocator* allocator, Dark_Linear_Map* linear_map, Dark_Compare compare, size_t key_byte, size_t value_byte);
void dark_linear_map_destruct(Dark_Linear_Map* linear_map);

Dark_Linear_Map* dark_linear_map_new_capacity(Dark_Allocator* allocator, Dark_Compare compare, size_t key_byte, size_t value_byte, size_t capacity);
Dark_Linear_Map* dark_linear_map_new(Dark_Allocator* allocator, Dark_Compare compare, size_t key_byte, size_t value_byte);
void dark_linear_map_delete(Dark_Linear_Map* linear_map);

Dark_Array_View dark_linear_map_array_view(Dark_Linear_Map* linear_map);
Dark_Buffer_View dark_linear_map_buffer_view(Dark_Linear_Map* linear_map);

bool dark_linear_map_contain_is(Dark_Linear_Map* linear_map, const void* key);
void* dark_linear_map_value(Dark_Linear_Map* linear_map, const void* key);

void* dark_linear_map_inplace(Dark_Linear_Map* linear_map, const void* key);
void dark_linear_map_insert(Dark_Linear_Map* linear_map, const void* key, const void* value);

void dark_linear_map_erase(Dark_Linear_Map* linear_map, const void* key);

size_t dark_linear_map_capacity(Dark_Linear_Map* linear_map);
void dark_linear_map_reserve_exact(Dark_Linear_Map* linear_map, size_t capacity);
void dark_linear_map_shrink_to_fit(Dark_Linear_Map* linear_map);

size_t dark_linear_map_size(Dark_Linear_Map* linear_map);
void dark_linear_map_clear(Dark_Linear_Map* linear_map);

void dark_linear_map_iterator(Dark_Linear_Map* linear_map, Dark_Iterator* iterator);
size_t dark_linear_map_iterator_context_byte(void);

size_t dark_linear_map_key_byte(Dark_Linear_Map* linear_map);
size_t dark_linear_map_value_byte(Dark_Linear_Map* linear_map);

void dark_linear_map_foreach(Dark_Linear_Map* linear_map, void* context, Dark_Foreach foreach);

size_t dark_linear_map_struct_byte(void);

#endif // !defined(___DARK___LINEAR_MAP_H)
