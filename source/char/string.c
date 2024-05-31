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

#include "char_module.h"
#include "dark/container/vector.h"

#include <dark/char/char.h>
#include <dark/container/container.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "string"

size_t dark_string_struct_size(void)
{
    return sizeof(Dark_Vector_Struct);
}

void dark_string_construct_v(Dark_String* const string_, const Dark_Growth growth_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    va_list copy;
    va_copy(copy, arguments_);

    const size_t size = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    DARK_ASSERT(size <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_construct_capacity(vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(vector, 0, size);

    dark_cbuffer_vsnprintf(size + 1, destination, format_, copy);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}

void dark_string_construct_f(Dark_String* const string_, const Dark_Growth growth_, const char* format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_list copy;
    va_start(args, format_);
    va_copy(copy, args);

    const size_t size = dark_cbuffer_vsnprintf(0, NULL, format_, args);
    va_end(args);

    DARK_ASSERT(size <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_construct_capacity(vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(vector, 0, size);

    dark_cbuffer_vsnprintf(size + 1, destination, format_, copy);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}

void dark_string_construct_cbuffer(Dark_String* const string_, const Dark_Growth growth_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_construct_capacity(vector, growth_, sizeof(char), count_ + 1);

    DARK_ASSERT(count_ <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, 0, count_, source_);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}

void dark_string_construct_char(Dark_String* const string_, const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //character_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_construct_capacity(vector, growth_, sizeof(char), 1);

    dark_vector_insert_front(vector, (void*)&character_);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}

void dark_string_construct_size(Dark_String* const string_, const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_construct_size(vector, growth_, sizeof(char), capacity_ + 1, size_);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}

void dark_string_construct_capacity(Dark_String* const string_, const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //capacity_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_string_construct_size((Dark_String*)vector, growth_, capacity_, 0);
}

void dark_string_construct(Dark_String* const string_, const Dark_Growth growth_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_string_construct_capacity((Dark_String*)vector, growth_, 0);
}

void dark_string_destruct(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_vector_destruct(vector);
}

Dark_String* dark_string_new_v(const Dark_Growth growth_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_construct_v(vector, growth_, format_, arguments_);

    return vector;
}

Dark_String* dark_string_new_f(const Dark_Growth growth_, const char* const format_, ...)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    va_list args;
    va_start(args, format_);
    dark_string_construct_v(vector, growth_, format_, args);
    va_end(args);

    return vector;
}

Dark_String* dark_string_new_cbuffer(const Dark_Growth growth_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_construct_cbuffer(vector, growth_, count_, source_);

    return vector;
}

Dark_String* dark_string_new_char(const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //character_

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_construct_char(vector, growth_, character_);

    return vector;
}

Dark_String* dark_string_new_size(const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_construct_size(vector, growth_, capacity_, size_);

    return vector;
}

Dark_String* dark_string_new_capacity(const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //capacity_

    return dark_string_new_size(growth_, capacity_, 0);
}

Dark_String* dark_string_new(const Dark_Growth growth_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_construct(vector, growth_);

    return vector;
}

void dark_string_delete(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    dark_string_destruct((Dark_String*)vector);

    free(vector);
}

char dark_string_at(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ < dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);

    return DARK_VECTOR_AT(vector, index_, char);
}

char dark_string_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_at((Dark_String*)vector, 0);
}

char dark_string_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_at((Dark_String*)vector, dark_string_size((Dark_String*)vector) - 1);
}

char* dark_string_cbuffer_terminated(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return DARK_VECTOR_DATA(vector, char);
}

char* dark_string_substring_terminated(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT(index_ < dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);

    return &DARK_VECTOR_AT(vector, index_, char);
}

char* dark_string_emplace(Dark_String* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace(vector, index_, count_);
}

char* dark_string_emplace_front(Dark_String* string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_string_emplace((Dark_String*)vector, 0, count_);
}

char* dark_string_emplace_back(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_string_emplace((Dark_String*)vector, dark_string_size((Dark_String*)vector), count_);
}

char* dark_string_inplace(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_emplace((Dark_String*)vector, index_, 1);
}

char* dark_string_inplace_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace((Dark_String*)vector, 0);
}

char* dark_string_inplace_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace((Dark_String*)vector, dark_string_size((Dark_String*)vector));
}

void dark_string_push_v(Dark_String* const string_, const size_t index_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    const char overwritten = DARK_VECTOR_AT(vector, index_, char);

    char* const destination = dark_vector_emplace(vector, index_, additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);

    va_end(copy);

    DARK_VECTOR_AT(vector, index_ + additional, char) = overwritten;
}

void dark_string_push_f(Dark_String* const string_, const size_t index_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;

    va_start(args, format_);
    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    const char overwritten = DARK_VECTOR_AT(vector, index_, char);

    char* const destination = dark_vector_emplace(vector, index_, additional);

    va_start(args, format_);
    dark_cbuffer_vsnprintf(additional + 1, destination, format_, args);
    va_end(args);

    DARK_VECTOR_AT(vector, index_ + additional, char) = overwritten;
}

void dark_string_push_cbuffer(Dark_String* const string_, const size_t index_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, index_, count_, source_);
}

void dark_string_append_v(Dark_String* const string_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    char* const destination = dark_vector_emplace(vector, dark_string_size((Dark_String*)vector), additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_f(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_list copy;
    va_start(args, format_);
    va_copy(copy, args);

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    char* const destination = dark_vector_emplace(vector, dark_string_size((Dark_String*)vector), additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_cbuffer(Dark_String* const string_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, dark_string_size((Dark_String*)vector), count_, source_);
}

void dark_string_prepend_v(Dark_String* const string_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    const char overwritten = DARK_VECTOR_AT(vector, 0, char);

    char* const destination = dark_vector_emplace(vector, 0, additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);
    va_end(copy);

    DARK_VECTOR_AT(vector, additional, char) = overwritten;
}

void dark_string_prepend_f(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;

    va_start(args, format_);
    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(vector, additional);

    const char overwritten = DARK_VECTOR_AT(vector, 0, char);

    char* const destination = dark_vector_emplace(vector, 0, additional);

    va_start(args, format_);
    dark_cbuffer_vsnprintf(additional + 1, destination, format_, args);
    va_end(args);

    DARK_VECTOR_AT(vector, additional, char) = overwritten;
}

void dark_string_prepend_cbuffer(Dark_String* const string_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, 0, count_, source_);
}

void dark_string_insert(Dark_String* const string_, const size_t index_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert(vector, index_, (void*)&character_);
}

void dark_string_insert_front(Dark_String* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert((Dark_String*)vector, 0, character_);
}

void dark_string_insert_back(Dark_String* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert((Dark_String*)vector, dark_string_size((Dark_String*)vector), character_);
}

void dark_string_pop(Dark_String* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    if (0 == count_)
    {
        return;
    }

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= dark_string_size((Dark_String*)vector), DARK_ERROR_VALUE);

    dark_vector_pop(vector, index_, count_);
}

void dark_string_pop_front(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) >= count_, DARK_ERROR_UNDERFLOW);

    dark_string_pop((Dark_String*)vector, 0, count_);
}

void dark_string_pop_back(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) >= count_, DARK_ERROR_UNDERFLOW);

    dark_string_pop((Dark_String*)vector, dark_string_size((Dark_String*)vector) - count_, count_);
}

void dark_string_erase(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) > 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ < dark_string_size((Dark_String*)vector), DARK_ERROR_VALUE);

    dark_string_pop((Dark_String*)vector, index_, 1);
}

void dark_string_erase_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop_front((Dark_String*)vector, 1);
}

void dark_string_erase_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size((Dark_String*)vector) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop_back((Dark_String*)vector, 1);
}

size_t dark_string_capacity(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_vector_capacity(vector) - 1;
}

void dark_string_reserve(Dark_String* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve(vector, capacity_ + 1);
}

void dark_string_reserve_additional(Dark_String* const string_, const size_t additional_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve_additional(vector, additional_);
}

void dark_string_reserve_exact(Dark_String* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve_exact(vector, capacity_ + 1);
}

void dark_string_shrink_to_fit(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_shrink_to_fit(vector);
}

size_t dark_string_size(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_vector_size(vector) - 1;
}

void dark_string_resize(Dark_String* const string_, const size_t size_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_resize(vector, size_ + 1);
}

void dark_string_resize_fill(Dark_String* const string_, const size_t size_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_
    //character_

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    if(size_ <= dark_string_size((Dark_String*)vector))
    {
        dark_string_resize((Dark_String*)vector, size_);

        return;
    }

    const uint64_t dif = size_ - dark_string_size((Dark_String*)vector);

    dark_vector_resize(vector, size_ + 1);

    for (size_t i = 0; i < dif; i++)
    {
        DARK_VECTOR_AT(vector, dark_string_size((Dark_String*)vector) - i, char) = character_;
    }
}

void dark_string_clear(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    Dark_Vector* const vector = (Dark_Vector*)string_;

    DARK_ASSERT(dark_vector_size(vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_clear(vector);

    const char EOS = '\0';
    dark_vector_insert_back(vector, (void*)&EOS);
}
