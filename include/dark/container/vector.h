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

#include <dark/container/array.h>
#include <dark/container/growth.h>
#include <dark/core/std.h>
#include <dark/memory/allocator.h>

#define DARK_VECTOR_AT(vector, index, type) \
(*(type*)dark_vector_at((vector), (index)))

#define DARK_VECTOR_FRONT(vector, type) \
(*(type*)dark_vector_front((vector)))

#define DARK_VECTOR_BACK(vector, type) \
(*(type*)dark_vector_back((vector)))

#define DARK_VECTOR_DATA(vector, type) \
((type*)dark_vector_data((vector)))

typedef struct Dark_Vector Dark_Vector;

typedef struct Dark_Vector_Struct Dark_Vector_Struct;
struct Dark_Vector_Struct
{
    Dark_Array array;
    size_t capacity;
    Dark_Growth growth;
};

size_t dark_vector_struct_size(void);
Dark_Vector_Struct dark_vector_construct_struct(Dark_Growth growth, size_t element_size, size_t capacity, size_t size);

void dark_vector_construct_size(Dark_Vector* vector, Dark_Growth growth, size_t element_size, size_t capacity, size_t size);
void dark_vector_construct_capacity(Dark_Vector* vector, Dark_Growth growth, size_t element_size, size_t capacity);
void dark_vector_construct(Dark_Vector* vector, Dark_Growth growth, size_t element_size);
void dark_vector_destruct(Dark_Vector* vector);

Dark_Vector* dark_vector_new_size(Dark_Allocator* allocator, Dark_Growth growth, size_t element_size, size_t capacity, size_t size);
Dark_Vector* dark_vector_new_capacity(Dark_Allocator* allocator, Dark_Growth growth, size_t element_size, size_t capacity);
Dark_Vector* dark_vector_new(Dark_Allocator* allocator, Dark_Growth growth, size_t element_size);
void dark_vector_delete(Dark_Allocator* allocator, Dark_Vector* vector);

void* dark_vector_at(Dark_Vector* vector, size_t index);
void* dark_vector_front(Dark_Vector* vector);
void* dark_vector_back(Dark_Vector* vector);
void* dark_vector_data(Dark_Vector* vector);
Dark_Array dark_vector_array(Dark_Vector* vector);
Dark_Array_View dark_vector_array_view(Dark_Vector* vector);

void* dark_vector_emplace(Dark_Allocator* allocator, Dark_Vector* vector, size_t index, size_t count);
void* dark_vector_emplace_front(Dark_Allocator* allocator, Dark_Vector* vector, size_t count);
void* dark_vector_emplace_back(Dark_Allocator* allocator, Dark_Vector* vector, size_t count);
void* dark_vector_inplace(Dark_Allocator* allocator, Dark_Vector* vector, size_t index);
void* dark_vector_inplace_front(Dark_Allocator* allocator, Dark_Vector* vector);
void* dark_vector_inplace_back(Dark_Allocator* allocator, Dark_Vector* vector);

void dark_vector_push(Dark_Allocator* allocator, Dark_Vector* vector, size_t index, size_t count, const void* source);
void dark_vector_push_front(Dark_Allocator* allocator, Dark_Vector* vector, size_t count, const void* element);
void dark_vector_push_back(Dark_Allocator* allocator, Dark_Vector* vector, size_t count, const void* source);
void dark_vector_insert(Dark_Allocator* allocator, Dark_Vector* vector, size_t index, const void* element);
void dark_vector_insert_front(Dark_Allocator* allocator, Dark_Vector* vector, const void* element);
void dark_vector_insert_back(Dark_Allocator* allocator, Dark_Vector* vector, const void* element);

void dark_vector_pop(Dark_Vector* vector, size_t index, size_t count);
void dark_vector_pop_front(Dark_Vector* vector, size_t count);
void dark_vector_pop_back(Dark_Vector* vector, size_t count);
void dark_vector_erase(Dark_Vector* vector, size_t index);
void dark_vector_erase_front(Dark_Vector* vector);
void dark_vector_erase_back(Dark_Vector* vector);

size_t dark_vector_capacity(Dark_Vector* vector);

void dark_vector_reserve(Dark_Allocator* allocator, Dark_Vector* vector, size_t capacity);
void dark_vector_reserve_additional(Dark_Allocator* allocator, Dark_Vector* vector, size_t additional);
void dark_vector_reserve_exact(Dark_Allocator* allocator, Dark_Vector* vector, size_t capacity);
void dark_vector_shrink_to_fit(Dark_Allocator* allocator, Dark_Vector* vector);

size_t dark_vector_size(Dark_Vector* vector);
void dark_vector_resize(Dark_Vector* vector, size_t size);
void dark_vector_clear(Dark_Vector* vector);

size_t dark_vector_element_size(Dark_Vector* vector);

#endif // !defined(___DARK___VECTOR_H)
