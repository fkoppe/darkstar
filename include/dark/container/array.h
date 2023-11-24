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

#if !defined(___DARK___ARRAY_H)
#define ___DARK___ARRAY_H

#include <dark/core/essential.h>

#define DARK_ARRAY_AT(array, index, type) \
(*(type*)dark_array_at((array), (index)))

#define DARK_ARRAY_FRONT(array, type) \
(*(type*)dark_array_front((array)))

#define DARK_ARRAY_BACK(array, type) \
(*(type*)dark_array_back((array)))

#define DARK_ARRAY_DATA(array, type) \
((type*)dark_array_data((array)))

size_t dark_array_struct_size();

void dark_array_create_size(void* array, size_t element_size, size_t capacity, size_t size);
void dark_array_create_capacity(void* array, size_t element_size, size_t capacity);
void dark_array_create(void* array, size_t element_size);
void dark_array_destroy(void* array);

void* dark_array_new_size(size_t element_size, size_t capacity, size_t size);
void* dark_array_new_capacity(size_t element_size, size_t capacity);
void* dark_array_new(size_t element_size);
void dark_array_delete(void* array);

void* dark_array_at(void* array, size_t index);
void* dark_array_front(void* array);
void* dark_array_back(void* array);
void* dark_array_data(void* array);

void dark_array_push(void* array, size_t index, size_t count, void* source);
void dark_array_insert(void* array, size_t index, void* element);
void dark_array_push_front(void* array, void* element);
void dark_array_push_back(void* array, void* element);

void dark_array_pop(void* array, size_t index, size_t count);
void dark_array_erase(void* array, size_t index);
void dark_array_pop_front(void* array);
void dark_array_pop_back(void* array);

size_t dark_array_capacity(void* array);
void dark_array_reserve_exact(void* array, size_t capacity);
void dark_array_shrink_to_fit(void* array);

size_t dark_array_size(void* array);
void dark_array_resize(void* array, size_t size);
void dark_array_clear(void* array);
size_t dark_array_element_size(void* array);

#endif // !defined(___DARK___ARRAY_H)
