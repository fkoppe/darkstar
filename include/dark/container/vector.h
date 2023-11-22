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

#if !defined(___DARK___VECTOR_H)
#define ___DARK___VECTOR_H

#include <dark/core/essential.h>

#define DARK_VECTOR_AT(darray, index, type) \
(*(type*)dark_vector_at((darray), (index)))

#define DARK_VECTOR_FRONT(darray, type) \
(*(type*)dark_vector_front((darray)))

#define DARK_VECTOR_BACK(darray, type) \
(*(type*)dark_vector_back((darray)))

#define DARK_VECTOR_DATA(darray, type) \
((type*)dark_vector_data((darray)))

void* dark_vector_new_size(Dark_Growth growth, size_t element_size, size_t capacity, size_t size);
void* dark_vector_new_capacity(Dark_Growth growth, size_t element_size, size_t capacity);
void* dark_vector_new(Dark_Growth growth, size_t element_size);
void dark_vector_delete(void* darray);

void* dark_vector_at(void* darray, size_t index);
void* dark_vector_front(void* darray);
void* dark_vector_back(void* darray);
void* dark_vector_data(void* darray);

void dark_vector_push(void* darray, size_t index, size_t count, void* array);
void dark_vector_insert(void* darray, size_t index, void* element);
void dark_vector_push_front(void* darray, void* element);
void dark_vector_push_back(void* darray, void* element);

void dark_vector_pop(void* darray, size_t index, size_t count);
void dark_vector_erase(void* darray, size_t index);
void dark_vector_pop_front(void* darray);
void dark_vector_pop_back(void* darray);

size_t dark_vector_capacity(void* darray);
void dark_vector_reserve(void* darray, size_t capacity);
void dark_vector_reserve_exact(void* darray, size_t capacity);
void dark_vector_shrink_to_fit(void* darray);

size_t dark_vector_size(void* darray);
void dark_vector_resize(void* darray, size_t size);
void dark_vector_clear(void* darray);
size_t dark_vector_element_size(void* darray);

#endif // !defined(___DARK___VECTOR_H)

