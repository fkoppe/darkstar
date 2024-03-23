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

#if !defined(___DARK___STRING_H)
#define ___DARK___STRING_H

#include <dark/container/growth.h>
#include <dark/core/essential.h>

#include <stdarg.h>

size_t dark_string_struct_size(void);

void dark_string_create_v(void* string, Dark_Growth growth, const char* format, va_list arguments);
void dark_string_create_f(void* string, Dark_Growth growth, const char* format, ...);
void dark_string_create_cbuffer(void* string, Dark_Growth growth, size_t count, const char* source);
void dark_string_create_char(void* string, Dark_Growth growth, char character);
void dark_string_create_size(void* string, Dark_Growth growth, size_t capacity, size_t size);
void dark_string_create_capacity(void* string, Dark_Growth growth, size_t capacity);
void dark_string_create(void* string, Dark_Growth growth);
void dark_string_destroy(void* string);

void* dark_string_new_v(Dark_Growth growth, const char* format, va_list arguments);
void* dark_string_new_f(Dark_Growth growth, const char* format, ...);
void* dark_string_new_cbuffer(Dark_Growth growth, size_t count, const char* source);
void* dark_string_new_char(Dark_Growth growth, char character);
void* dark_string_new_size(Dark_Growth growth, size_t capacity, size_t size);
void* dark_string_new_capacity(Dark_Growth growth, size_t capacity);
void* dark_string_new(Dark_Growth growth);
void dark_string_delete(void* string);

char dark_string_at(void* string, size_t index);
char dark_string_front(void* string);
char dark_string_back(void* string);
char* dark_string_cbuffer_terminated(void* string);
char* dark_string_substring_terminated(void* string, size_t index);

void dark_string_push_v(void* string, size_t index, const char* format, va_list arguments);
void dark_string_push_f(void* string, size_t index, const char* format, ...);
void dark_string_push_cbuffer(void* string, size_t index, size_t count, const char* source);
void dark_string_insert(void* string, size_t index, char character);
void dark_string_push_front(void* string, char character);
void dark_string_push_back(void* string, char character);

void dark_string_append_v(void* string, const char* format, va_list arguments);
void dark_string_append_f(void* string, const char* format, ...);
void dark_string_append_cbuffer(void* string, size_t count, const char* source);
void dark_string_prepend_v(void* string, const char* format, va_list arguments);
void dark_string_prepend_f(void* string, const char* format, ...);
void dark_string_prepend_cbuffer(void* string, size_t count, const char* source);

void dark_string_pop(void* string, size_t index, size_t count);
void dark_string_erase(void* string, size_t index);
void dark_string_pop_front_c(void* string, size_t count);
void dark_string_pop_front(void* string);
void dark_string_pop_back_c(void* string, size_t count);
void dark_string_pop_back(void* string);

size_t dark_string_capacity(void* string);
void dark_string_reserve(void* string, size_t capacity);
void dark_string_reserve_exact(void* string, size_t capacity);
void dark_string_shrink_to_fit(void* string);

size_t dark_string_size(void* string);
void dark_string_resize(void* string, size_t size);
void dark_string_resize_fill(void* string, size_t size, char character);
void dark_string_clear(void* string);

#endif // !defined(___DARK___STRING_H)
