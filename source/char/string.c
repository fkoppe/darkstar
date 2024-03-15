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

#include <dark/char/char.h>
#include <dark/container/container.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "string"

size_t dark_string_struct_size(void)
{
    return sizeof(Dark_Vector_Struct);
}

void dark_string_create_v(void* const string_, const Dark_Growth growth_, const char* const format_, va_list arguments_)
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

    void* const vector = string_;

    dark_vector_create_capacity(vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(vector, 0, size);

    dark_cbuffer_vsnprintf(size + 1, destination, format_, copy);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_push_back(vector, (void*)&EOS);
}

void dark_string_create_f(void* const string_, const Dark_Growth growth_, const char* format_, ...)
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

    void* const vector = string_;

    dark_vector_create_capacity(vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(vector, 0, size);

    dark_cbuffer_vsnprintf(size + 1, destination, format_, args);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_push_back(vector, (void*)&EOS);
}

void dark_string_create_cbuffer(void* const string_, const Dark_Growth growth_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //count_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_create_capacity(vector, growth_, sizeof(char), count_ + 1);

    DARK_ASSERT(count_ <= DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, 0, count_, source_);

    const char EOS = '\0';
    dark_vector_push_back(vector, (void*)&EOS);
}

void dark_string_create_char(void* const string_, const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //character_

    void* const vector = string_;

    dark_vector_create_capacity(vector, growth_, sizeof(char), 1);

    dark_vector_push_front(vector, (void*)&character_);

    const char EOS = '\0';
    dark_vector_push_back(vector, (void*)&EOS);
}

void dark_string_create_size(void* const string_, const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    void* const vector = string_;

    dark_vector_create_capacity(vector, growth_, sizeof(char), 1);

    const char EOS = '\0';
    dark_vector_push_back(vector, (void*)&EOS);
}

void dark_string_create_capacity(void* const string_, const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //capacity_

    void* const vector = string_;

    dark_string_create_size(vector, growth_, capacity_, 0);
}

void dark_string_create(void* const string_, const Dark_Growth growth_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);

    void* const vector = string_;

    dark_string_create_capacity(vector, growth_, 0);
}

void dark_string_destroy(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_destroy(vector);
}

void* dark_string_new_v(const Dark_Growth growth_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_create_v(vector, growth_, format_, arguments_);

    return vector;
}

void* dark_string_new_f(const Dark_Growth growth_, const char* const format_, ...)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    va_list args;
    va_start(args, format_);
    dark_string_create_v(vector, growth_, format_, args);
    va_end(args);

    return vector;
}

void* dark_string_new_cbuffer(const Dark_Growth growth_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //count_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_create_cbuffer(vector, growth_, count_, source_);

    return vector;
}

void* dark_string_new_char(const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //character_

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_create_char(vector, growth_, character_);

    return vector;
}

void* dark_string_new_size(const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_create_size(vector, growth_, capacity_, size_);

    return vector;
}

void* dark_string_new_capacity(const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);
    //capacity_

    return dark_string_new_size(growth_, capacity_, 0);
}

void* dark_string_new(const Dark_Growth growth_)
{
    DARK_ASSERT(growth_.min <= growth_.max || 0 == growth_.max, DARK_ERROR_GROWTH);
    DARK_ASSERT(growth_.factor || growth_.min, DARK_ERROR_GROWTH);

    void* vector = malloc(sizeof(Dark_Vector_Struct));
    DARK_ASSERT(NULL != vector, DARK_ERROR_ALLOCATION);

    dark_string_create(vector, growth_);

    return vector;
}

void dark_string_delete(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_string_destroy(vector);

    free(vector);
}

char dark_string_at(void* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    DARK_ASSERT(index_ < dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);

    return DARK_VECTOR_AT(string_, index_, char);
}

char dark_string_front(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    return dark_string_at(vector, 0);
}

char dark_string_back(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    return dark_string_at(vector, dark_string_size(vector) - 1);
}

char* dark_string_cbuffer_terminated(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    return DARK_VECTOR_DATA(vector, char);
}

char* dark_string_substr_terminated(void* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    DARK_ASSERT(index_ < dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);

    return &DARK_VECTOR_AT(string_, index_, char);
}

void dark_string_push_v(void* const string_, const size_t index_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    void* const vector = string_;

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(index_ <= dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    const char overwritten = DARK_VECTOR_AT(vector, index_, char);

    char* const destination = dark_vector_emplace(vector, index_, additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, arguments_);

    DARK_VECTOR_AT(vector, index_ + additional, char) = overwritten;
}

void dark_string_push_f(void* const string_, const size_t index_, const char* const format_, ...)
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

    void* const vector = string_;

    DARK_ASSERT(index_ <= dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    const char overwritten = DARK_VECTOR_AT(vector, index_, char);

    char* const destination = dark_vector_emplace(vector, index_, additional);

    va_start(args, format_);
    dark_cbuffer_vsnprintf(additional + 1, destination, format_, args);
    va_end(args);

    DARK_VECTOR_AT(vector, index_ + additional, char) = overwritten;
}

void dark_string_push_cbuffer(void* const string_, const size_t index_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //count_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* const vector = string_;

    DARK_ASSERT(index_ <= dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, index_, count_, source_);
}

void dark_string_insert(void* const string_, const size_t index_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    void* const vector = string_;

    DARK_ASSERT(index_ <= dark_string_size(vector), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(dark_string_size(vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert(string_, index_, (void*)&character_);
}

void dark_string_push_front(void* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert(string_, 0, character_);
}

void dark_string_push_back(void* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //character_

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) < DARK_CONTAINER_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert(string_, dark_string_size(string_) - 1, character_);
}

void dark_string_append_v(void* const string_, const char* const format_, va_list arguments_)
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

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    char* const destination = dark_vector_emplace(vector, dark_string_size(string_) - 1, additional + 1);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_f(void* const string_, const char* const format_, ...)
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

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    char* const destination = dark_vector_emplace(vector, dark_string_size(string_), additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_cbuffer(void* const string_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //count_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, dark_string_size(string_) - 1, count_, source_);
}

void dark_string_prepend_v(void* const string_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    const size_t additional = dark_cbuffer_vsnprintf(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    const char overwritten = DARK_VECTOR_AT(vector, 0, char);

    char* const destination = dark_vector_emplace(vector, 0, additional);

    dark_cbuffer_vsnprintf(additional + 1, destination, format_, arguments_);

    DARK_VECTOR_AT(vector, additional, char) = overwritten;
}

void dark_string_prepend_f(void* const string_, const char* const format_, ...)
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

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve(vector, dark_vector_size(vector) + additional);

    const char overwritten = DARK_VECTOR_AT(vector, 0, char);

    char* const destination = dark_vector_emplace(vector, 0, additional);

    va_start(args, format_);
    dark_cbuffer_vsnprintf(additional + 1, destination, format_, args);
    va_end(args);

    DARK_VECTOR_AT(vector, additional, char) = overwritten;
}

void dark_string_prepend_cbuffer(void* const string_, const size_t count_, const char* const source_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //count_
    DARK_ASSERT(NULL != source_, DARK_ERROR_NULL);

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) <= DARK_CONTAINER_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    dark_vector_push(vector, 0, count_, source_);
}

void dark_string_pop(void* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!
    //count_!

    void* const vector = string_;

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(dark_string_size(vector) >= count_, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ + count_ <= dark_string_size(vector), DARK_ERROR_VALUE);

    dark_vector_pop(vector, index_, count_);
}

void dark_string_erase(void* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) > 0, DARK_ERROR_UNDERFLOW);
    DARK_ASSERT(index_ < dark_string_size(vector), DARK_ERROR_VALUE);

    dark_string_pop(vector, index_, 1);
}

void dark_string_pop_front(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop(vector, 0, 1);
}

void dark_string_pop_back(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //index_!

    void* const vector = string_;

    DARK_ASSERT(dark_string_size(vector) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop(vector, dark_string_size(vector) - 1, 1);
}

size_t dark_string_capacity(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    return dark_vector_capacity(string_) - 1;
}

void dark_string_reserve(void* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_reserve(vector, capacity_+1);
}

void dark_string_reserve_exact(void* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_reserve_exact(vector, capacity_+1);
}

void dark_string_shrink_to_fit(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_shrink_to_fit(vector);
}

size_t dark_string_size(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    return dark_vector_size(vector) - 1;
}

void dark_string_resize(void* const string_, const size_t size_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_

    void* const vector = string_;

    dark_vector_resize(vector, size_+1);
}

void dark_string_resize_fill(void* const string_, const size_t size_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_
    //character_

    void* const vector = string_;

    const uint64_t dif = size_ - dark_string_size(vector);

    dark_vector_resize(vector, size_+1);

    for (size_t i = 0; i < dif; i++)
    {
        DARK_VECTOR_AT(vector, dark_string_size(vector) - i, char) = character_;
    }
}

void dark_string_clear(void* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    void* const vector = string_;

    dark_vector_clear(vector);
}
