/************************************************************************************
*                                                                                   *
*   darkstar 0.1.0.0 - https://github.com/fkoppe/darkstar                           *
*   ************************************************************************        *
*                                                                                   *
*   Copyright (C) 2023-2025 Felix Koppe <fkoppe@web.de>                             *
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
#include <dark/char/string_struct.h>
#include <dark/container/container.h>
#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "string"

void dark_string_construct_v(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list copy;
    va_copy(copy, arguments_);

    const size_t size = dark_vsnprintf_notterminated(0, NULL, format_, arguments_);

    DARK_ASSERT(size <= DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    string_->allocator = allocator_;
    dark_vector_construct_capacity(allocator_, &string_->vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(&string_->vector, 0, size);

    dark_vsnprintf_notterminated(size + 1, destination, format_, copy);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

void dark_string_construct_f(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const char* format_, ...)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;
    va_list copy;
    va_start(args, format_);
    va_copy(copy, args);

    const size_t size = dark_vsnprintf_notterminated(0, NULL, format_, args);
    va_end(args);

    DARK_ASSERT(size <= DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    string_->allocator = allocator_;
    dark_vector_construct_capacity(allocator_, &string_->vector, growth_, sizeof(char), size + 1);

    char* const destination = dark_vector_emplace(&string_->vector, 0, size);

    dark_snprintf_notterminated(size + 1, destination, format_, copy);
    va_end(copy);

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

void dark_string_construct_cstring(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const char* const cstring_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    dark_string_construct_cbuffer_view(allocator_, string_, growth_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_string_construct_cbuffer_view(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    string_->allocator = allocator_;
    dark_vector_construct_capacity(string_->allocator, &string_->vector, growth_, sizeof(char), cbuffer_view_.size + 1);

    DARK_ASSERT(cbuffer_view_.size <= DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_push(&string_->vector, 0, dark_cbuffer_view_to_array_view(cbuffer_view_));

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

void dark_string_construct_char(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    //character_

    string_->allocator = allocator_;
    dark_vector_construct_capacity(string_->allocator, &string_->vector, growth_, sizeof(char), 1);

    dark_vector_insert_front(&string_->vector, (void*)&character_);

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

void dark_string_construct_size(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    string_->allocator = allocator_;

    string_->allocator = allocator_;
    dark_vector_construct_size(string_->allocator, &string_->vector, growth_, sizeof(char), capacity_ + 1, size_);

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

void dark_string_construct_capacity(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    //capacity_

    dark_string_construct_size(allocator_, string_, growth_, capacity_, 0);
}

void dark_string_construct(Dark_Allocator* const allocator_, Dark_String* const string_, const Dark_Growth growth_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);

    dark_string_construct_capacity(allocator_, string_, growth_, 0);
}

void dark_string_destruct(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    dark_vector_destruct(&string_->vector);
}

Dark_String* dark_string_new_v(Dark_Allocator* const allocator_, const Dark_Growth growth_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    Dark_String* const string = dark_malloc(allocator_, sizeof(Dark_String));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    dark_string_construct_v(allocator_, string, growth_, format_, arguments_);

    return string;
}

Dark_String* dark_string_new_f(Dark_Allocator* const allocator_, const Dark_Growth growth_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    Dark_String* const string = dark_malloc(allocator_, sizeof(Dark_String));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    va_list args;
    va_start(args, format_);
    dark_string_construct_v(allocator_, string, growth_, format_, args);
    va_end(args);

    return string;
}

Dark_String* dark_string_new_cstring(Dark_Allocator* const allocator_, const Dark_Growth growth_, const char* const cstring_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    return dark_string_new_cbuffer_view(allocator_, growth_, dark_cstring_to_cbuffer_view(cstring_));
}

Dark_String* dark_string_new_cbuffer_view(Dark_Allocator* const allocator_, const Dark_Growth growth_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    Dark_String* const string = dark_malloc(allocator_, sizeof(Dark_String));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    dark_string_construct_cbuffer_view(allocator_, string, growth_, cbuffer_view_);

    return string;
}

Dark_String* dark_string_new_char(Dark_Allocator* const allocator_, const Dark_Growth growth_, const char character_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    //character_

    Dark_String* const string = dark_malloc(allocator_, sizeof(Dark_String));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    dark_string_construct_char(allocator_, string, growth_, character_);

    return string;
}

Dark_String* dark_string_new_size(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t capacity_, const size_t size_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    DARK_ASSERT(capacity_ >= size_, DARK_ERROR_VALUE);

    Dark_String* const string = dark_malloc(allocator_, sizeof(*string));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    dark_string_construct_size(allocator_, string, growth_, capacity_, size_);

    return string;
}

Dark_String* dark_string_new_capacity(Dark_Allocator* const allocator_, const Dark_Growth growth_, const size_t capacity_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);
    //capacity_

    return dark_string_new_size(allocator_, growth_, capacity_, 0);
}

Dark_String* dark_string_new(Dark_Allocator* const allocator_, const Dark_Growth growth_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != growth_, DARK_ERROR_NULL);

    Dark_String* const string = dark_malloc(allocator_, sizeof(Dark_String));
    DARK_ASSERT(NULL != string, DARK_ERROR_ALLOCATION);

    dark_string_construct(allocator_, string, growth_);

    return string;
}

void dark_string_delete(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_string_destruct(string_);

    dark_free(string_->allocator, string_, sizeof(Dark_String));
}

char dark_string_at(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(index_ < dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    return DARK_VECTOR_AT(&string_->vector, index_, char);
}

char dark_string_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_at(string_, 0);
}

char dark_string_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_at(string_, dark_string_size(string_) - 1);
}

const char* dark_string_cstring(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return DARK_VECTOR_DATA(&string_->vector, char);
}

const char* dark_string_subcstring(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT(index_ < dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    return &DARK_VECTOR_AT(&string_->vector, index_, char);
}

Dark_Cbuffer dark_string_cbuffer(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_subcbuffer(string_, 0);
}

Dark_Cbuffer dark_string_subcbuffer(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT(index_ < dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    const Dark_Array array = dark_vector_array(&string_->vector);

    const Dark_Cbuffer cbuffer = { array.size - index_ - 1, (char*)array.data + index_ };

    return cbuffer;
}

Dark_Cbuffer_View dark_string_cbuffer_view(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_subcbuffer_view(string_, 0);
}

Dark_Cbuffer_View dark_string_cbuffer_view_terminated(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_string_subcbuffer_view_terminated(string_, 0);
}

Dark_Cbuffer_View dark_string_subcbuffer_view(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT(index_ < dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    return dark_cbuffer_to_view(dark_string_subcbuffer(string_, index_));
}
Dark_Cbuffer_View dark_string_subcbuffer_view_terminated(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    DARK_ASSERT(index_ < dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    const Dark_Array array = dark_vector_array(&string_->vector);

    const Dark_Cbuffer_View cbuffer_view = { array.size - index_, (char*)array.data + index_ };

    return cbuffer_view;
}

char* dark_string_emplace(Dark_String* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_vector_emplace(&string_->vector, index_, count_);
}

char* dark_string_emplace_front(Dark_String* string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_string_emplace(string_, 0, count_);
}

char* dark_string_emplace_back(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - count_, DARK_ERROR_OVERFLOW);

    return dark_string_emplace(string_, dark_string_size(string_), count_);
}

Dark_Cbuffer dark_string_emplace_cbuffer(Dark_String* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(count_ > 0, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    void* const data = dark_string_emplace(string_, index_, count_);

    const Dark_Cbuffer cbuffer = { count_, data };

    return cbuffer;
}

Dark_Cbuffer dark_string_emplace_cbuffer_front(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_emplace_cbuffer(string_, 0, count_);
}

Dark_Cbuffer dark_string_emplace_cbuffer_back(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_emplace_cbuffer(string_, dark_string_size(string_), count_);
}

char* dark_string_inplace(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_emplace(string_, index_, 1);
}

char* dark_string_inplace_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace(string_, 0);
}

char* dark_string_inplace_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace(string_, dark_string_size(string_));
}

Dark_Cbuffer dark_string_inplace_cbuffer(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_emplace_cbuffer(string_, index_, 1);
}

Dark_Cbuffer dark_string_inplace_cbuffer_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace_cbuffer(string_, 0);
}

Dark_Cbuffer dark_string_inplace_cbuffer_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    return dark_string_inplace_cbuffer(string_, dark_string_size(string_));
}

void dark_string_push_v(Dark_String* const string_, const size_t index_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, index_, additional);

    dark_vsnprintf_notterminated(additional + 1, destination, format_, copy);

    va_end(copy);
}

void dark_string_push_f(Dark_String* const string_, const size_t index_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;

    va_start(args, format_);
    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, index_, additional);

    va_start(args, format_);
    dark_vsnprintf_notterminated(additional + 1, destination, format_, args);
    va_end(args);
}

void dark_string_push_cstring(Dark_String* const string_, const size_t index_, const char* const cstring_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_string_push_cbuffer_view(string_, index_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_string_push_cbuffer_view(Dark_String* const string_, const size_t index_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - cbuffer_view_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(&string_->vector, index_, dark_cbuffer_view_to_array_view(cbuffer_view_));
}

void dark_string_append_v(Dark_String* const string_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, dark_string_size(string_), additional);

    dark_vsnprintf_notterminated(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_f(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;
    va_list copy;
    va_start(args, format_);
    va_copy(copy, args);

    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, dark_string_size(string_), additional);

    dark_vsnprintf_notterminated(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_append_cstring(Dark_String* const string_, const char* const cstring_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_string_append_cbuffer_view(string_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_string_append_cbuffer_view(Dark_String* const string_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - cbuffer_view_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(&string_->vector, dark_string_size(string_), dark_cbuffer_view_to_array_view(cbuffer_view_));
}

void dark_string_prepend_v(Dark_String* const string_, const char* const format_, va_list arguments_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);
    //arguments_

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list copy;
    va_copy(copy, arguments_);

    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, arguments_);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, 0, additional);

    dark_vsnprintf_notterminated(additional + 1, destination, format_, copy);
    va_end(copy);
}

void dark_string_prepend_f(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(format_);

    va_list args;

    va_start(args, format_);
    const size_t additional = dark_vsnprintf_notterminated(0, NULL, format_, args);
    va_end(args);

    if(0 == additional)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - additional, DARK_ERROR_OVERFLOW);

    dark_vector_reserve_additional(&string_->vector, additional);

    char* const destination = dark_vector_emplace(&string_->vector, 0, additional);

    va_start(args, format_);
    dark_vsnprintf_notterminated(additional + 1, destination, format_, args);
    va_end(args);
}

void dark_string_prepend_cstring(Dark_String* const string_, const char* const cstring_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != cstring_, DARK_ERROR_NULL);

    DARK_CSTRING_ASSERT_CONTENT(cstring_);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_string_prepend_cbuffer_view(string_, dark_cstring_to_cbuffer_view(cstring_));
}

void dark_string_prepend_cbuffer_view(Dark_String* const string_, const Dark_Cbuffer_View cbuffer_view_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(cbuffer_view_.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != cbuffer_view_.data, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) <= DARK_STRING_SIZE_MAX - cbuffer_view_.size, DARK_ERROR_OVERFLOW);

    dark_vector_push(&string_->vector, 0, dark_cbuffer_view_to_array_view(cbuffer_view_));
}

void dark_string_insert(Dark_String* const string_, const size_t index_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    //character_

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_vector_insert(&string_->vector, index_, (void*)&character_);
}

void dark_string_insert_front(Dark_String* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //character_

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert(string_, 0, character_);
}

void dark_string_insert_back(Dark_String* const string_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //character_

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) < DARK_STRING_SIZE_MAX, DARK_ERROR_OVERFLOW);

    dark_string_insert(string_, dark_string_size(string_), character_);
}

void dark_string_pop(Dark_String* const string_, const size_t index_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    if (0 == count_)
    {
        return;
    }

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) >= count_, DARK_ERROR_UNDERFLOW);

    dark_vector_pop(&string_->vector, index_, count_);
}

void dark_string_pop_front(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) >= count_, DARK_ERROR_UNDERFLOW);

    dark_string_pop(string_, 0, count_);
}

void dark_string_pop_back(Dark_String* const string_, const size_t count_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) >= count_, DARK_ERROR_UNDERFLOW);

    dark_string_pop(string_, dark_string_size(string_) - count_, count_);
}

void dark_string_erase(Dark_String* const string_, const size_t index_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop(string_, index_, 1);
}

void dark_string_erase_front(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop_front(string_, 1);
}

void dark_string_erase_back(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);
    DARK_ASSERT(dark_string_size(string_) > 0, DARK_ERROR_UNDERFLOW);

    dark_string_pop_back(string_, 1);
}

size_t dark_string_capacity(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_vector_capacity(&string_->vector) - 1;
}

void dark_string_reserve(Dark_String* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve(&string_->vector, capacity_ + 1);
}

void dark_string_reserve_additional(Dark_String* const string_, const size_t additional_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(additional_ > 0, DARK_ERROR_ZERO);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve_additional(&string_->vector, additional_);
}

void dark_string_reserve_exact(Dark_String* const string_, const size_t capacity_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_reserve_exact(&string_->vector, capacity_ + 1);
}

void dark_string_shrink_to_fit(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_shrink_to_fit(&string_->vector);
}

size_t dark_string_size(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    return dark_vector_size(&string_->vector) - 1;
}

void dark_string_resize(Dark_String* const string_, const size_t size_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_resize(&string_->vector, size_ + 1);
}

void dark_string_resize_fill(Dark_String* const string_, const size_t size_, const char character_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    //size_
    //character_

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    if(size_ <= dark_string_size(string_))
    {
        dark_string_resize(string_, size_);

        return;
    }

    const uint64_t dif = size_ - dark_string_size(string_);

    dark_vector_resize(&string_->vector, size_ + 1);

    for (size_t i = 0; i < dif; i++)
    {
        DARK_VECTOR_AT(&string_->vector, dark_string_size(string_) - i, char) = character_;
    }
}

void dark_string_clear(Dark_String* const string_)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);

    DARK_ASSERT(dark_vector_size(&string_->vector) > 0, DARK_ERROR_CONTAINER_INTEGRITY);

    dark_vector_clear(&string_->vector);

    const char EOS = '\0';
    dark_vector_insert_back(&string_->vector, (void*)&EOS);
}

size_t dark_string_struct_byte(void)
{
    return sizeof(Dark_String);
}
