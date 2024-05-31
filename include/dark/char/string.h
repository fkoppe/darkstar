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

typedef struct Dark_String Dark_String;

size_t dark_string_struct_size(void);

void dark_string_construct_v(Dark_String* string, Dark_Growth growth, const char* format, va_list arguments);
void dark_string_construct_f(Dark_String* string, Dark_Growth growth, const char* format, ...);
void dark_string_construct_cbuffer(Dark_String* string, Dark_Growth growth, size_t count, const char* source);
void dark_string_construct_char(Dark_String* string, Dark_Growth growth, char character);
void dark_string_construct_size(Dark_String* string, Dark_Growth growth, size_t capacity, size_t size);
void dark_string_construct_capacity(Dark_String* string, Dark_Growth growth, size_t capacity);
void dark_string_construct(Dark_String* string, Dark_Growth growth);
void dark_string_destruct(Dark_String* string);

Dark_String* dark_string_new_v(Dark_Growth growth, const char* format, va_list arguments);
Dark_String* dark_string_new_f(Dark_Growth growth, const char* format, ...);
Dark_String* dark_string_new_cbuffer(Dark_Growth growth, size_t count, const char* source);
Dark_String* dark_string_new_char(Dark_Growth growth, char character);
Dark_String* dark_string_new_size(Dark_Growth growth, size_t capacity, size_t size);
Dark_String* dark_string_new_capacity(Dark_Growth growth, size_t capacity);
Dark_String* dark_string_new(Dark_Growth growth);
void dark_string_delete(Dark_String* string);

char dark_string_at(Dark_String* string, size_t index);
char dark_string_front(Dark_String* string);
char dark_string_back(Dark_String* string);
char* dark_string_cbuffer_terminated(Dark_String* string);
char* dark_string_substring_terminated(Dark_String* string, size_t index);

char* dark_string_emplace(Dark_String* string, size_t index, size_t count);
char* dark_string_emplace_front(Dark_String* string, size_t count);
char* dark_string_emplace_back(Dark_String* string, size_t count);
char* dark_string_inplace(Dark_String* string, size_t index);
char* dark_string_inplace_front(Dark_String* string);
char* dark_string_inplace_back(Dark_String* string);

void dark_string_push_v(Dark_String* string, size_t index, const char* format, va_list arguments);
void dark_string_push_f(Dark_String* string, size_t index, const char* format, ...);
void dark_string_push_cbuffer(Dark_String* string, size_t index, size_t count, const char* source);
void dark_string_append_v(Dark_String* string, const char* format, va_list arguments);
void dark_string_append_f(Dark_String* string, const char* format, ...);
void dark_string_append_cbuffer(Dark_String* string, size_t count, const char* source);
void dark_string_prepend_v(Dark_String* string, const char* format, va_list arguments);
void dark_string_prepend_f(Dark_String* string, const char* format, ...);
void dark_string_prepend_cbuffer(Dark_String* string, size_t count, const char* source);

void dark_string_insert(Dark_String* string, size_t index, char character);
void dark_string_insert_front(Dark_String* string, char character);
void dark_string_insert_back(Dark_String* string, char character);

void dark_string_pop(Dark_String* string, size_t index, size_t count);
void dark_string_pop_front(Dark_String* string, size_t count);
void dark_string_pop_back(Dark_String* string, size_t count);
void dark_string_erase(Dark_String* string, size_t index);
void dark_string_erase_front(Dark_String* string);
void dark_string_erase_back(Dark_String* string);

size_t dark_string_capacity(Dark_String* string);
void dark_string_reserve(Dark_String* string, size_t capacity);
void dark_string_reserve_additional(Dark_String* string, size_t additional);
void dark_string_reserve_exact(Dark_String* string, size_t capacity);
void dark_string_shrink_to_fit(Dark_String* string);

size_t dark_string_size(Dark_String* string);
void dark_string_resize(Dark_String* string, size_t size);
void dark_string_resize_fill(Dark_String* string, size_t size, char character);
void dark_string_clear(Dark_String* string);

#endif // !defined(___DARK___STRING_H)
