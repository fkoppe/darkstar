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

#if !defined(___DARK___VECTOR_H)
#define ___DARK___VECTOR_H

#include <dark/container/growth.h>
#include <dark/core/essential.h>

#define DARK_VECTOR_AT(vector, index, type) \
(*(type*)dark_vector_at((vector), (index)))

#define DARK_VECTOR_FRONT(vector, type) \
(*(type*)dark_vector_front((vector)))

#define DARK_VECTOR_BACK(vector, type) \
(*(type*)dark_vector_back((vector)))

#define DARK_VECTOR_DATA(vector, type) \
((type*)dark_vector_data((vector)))

size_t dark_vector_struct_size();

void dark_vector_create_size(void* vector, Dark_Growth growth, size_t element_size, size_t capacity, size_t size);
void dark_vector_create_capacity(void* vector, Dark_Growth growth, size_t element_size, size_t capacity);
void dark_vector_create(void* vector, Dark_Growth growth, size_t element_size);
void dark_vector_destroy(void* vector);

void* dark_vector_new_size(Dark_Growth growth, size_t element_size, size_t capacity, size_t size);
void* dark_vector_new_capacity(Dark_Growth growth, size_t element_size, size_t capacity);
void* dark_vector_new(Dark_Growth growth, size_t element_size);
void dark_vector_delete(void* vector);

void* dark_vector_at(void* vector, size_t index);
void* dark_vector_front(void* vector);
void* dark_vector_back(void* vector);
void* dark_vector_data(void* vector);

void* dark_vector_emplace(void* vector, size_t index, size_t count);

void dark_vector_push(void* vector, size_t index, size_t count, void* source);
void dark_vector_insert(void* vector, size_t index, void* element);
void dark_vector_push_front(void* vector, void* element);
void dark_vector_push_back(void* vector, void* element);

void dark_vector_pop(void* vector, size_t index, size_t count);
void dark_vector_erase(void* vector, size_t index);
void dark_vector_pop_front(void* vector);
void dark_vector_pop_back(void* vector);

size_t dark_vector_capacity(void* vector);
void dark_vector_reserve(void* vector, size_t capacity);
void dark_vector_reserve_exact(void* vector, size_t capacity);
void dark_vector_shrink_to_fit(void* vector);

size_t dark_vector_size(void* vector);
void dark_vector_resize(void* vector, size_t size);
void dark_vector_clear(void* vector);

size_t dark_vector_element_size(void* vector);

#endif // !defined(___DARK___VECTOR_H)

