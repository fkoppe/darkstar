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

typedef struct Dark_Array_Struct
{
    size_t element_size;
    size_t capacity;
    size_t size;
    char* data;
} Dark_Array_Struct;

typedef struct Dark_Array Dark_Array;

size_t dark_array_struct_size(void);

void dark_array_create_size(Dark_Array* array, size_t element_size, size_t capacity, size_t size);
void dark_array_create_capacity(Dark_Array* array, size_t element_size, size_t capacity);
void dark_array_create(Dark_Array* array, size_t element_size);
void dark_array_destroy(Dark_Array* array);

Dark_Array* dark_array_new_size(size_t element_size, size_t capacity, size_t size);
Dark_Array* dark_array_new_capacity(size_t element_size, size_t capacity);
Dark_Array* dark_array_new(size_t element_size);
void dark_array_delete(Dark_Array* array);

void* dark_array_at(Dark_Array* array, size_t index);
void* dark_array_front(Dark_Array* array);
void* dark_array_back(Dark_Array* array);
void* dark_array_data(Dark_Array* array);

void* dark_array_emplace(Dark_Array* array, size_t index, size_t count);
void* dark_array_emplace_front_c(Dark_Array* array, size_t count);
void* dark_array_emplace_front(Dark_Array* array);
void* dark_array_emplace_back_c(Dark_Array* array, size_t count);
void* dark_array_emplace_back(Dark_Array* array);

void dark_array_push(Dark_Array* array, size_t index, size_t count, const void* source);
void dark_array_insert(Dark_Array* array, size_t index, const void* element);
void dark_array_push_front_c(Dark_Array* array, size_t count, const void* source);
void dark_array_push_front(Dark_Array* array, const void* element);
void dark_array_push_back_c(Dark_Array* array, size_t count, const void* source);
void dark_array_push_back(Dark_Array* array, const void* element);

void dark_array_pop(Dark_Array* array, size_t index, size_t count);
void dark_array_erase(Dark_Array* array, size_t index);
void dark_array_pop_front_c(Dark_Array* array, size_t count);
void dark_array_pop_front(Dark_Array* array);
void dark_array_pop_back_c(Dark_Array* array, size_t count);
void dark_array_pop_back(Dark_Array* array);

size_t dark_array_capacity(Dark_Array* array);
void dark_array_reserve_exact(Dark_Array* array, size_t capacity);
void dark_array_shrink_to_fit(Dark_Array* array);

size_t dark_array_size(Dark_Array* array);
void dark_array_resize(Dark_Array* array, size_t size);
void dark_array_clear(Dark_Array* array);
size_t dark_array_element_size(Dark_Array* array);

#endif // !defined(___DARK___ARRAY_H)
