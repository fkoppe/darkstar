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

#include "stream_module.h"

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/platform/platform.h>
#include <dark/stream/ostream_struct.h>
#include <dark/stream/stream.h>

#include <time.h>
#include <stdio.h>

#undef DARK_UNIT
#define DARK_UNIT "ostream"

size_t dark_ostream_struct_size(void)
{
    return sizeof(Dark_Ostream_Struct);
}

void dark_ostream_construct(Dark_Allocator* const allocator_, Dark_Ostream* const ostream_, const Dark_Ostream_Settings settings_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");

    ostream_->settings = settings_;
    ostream_->allocator = allocator_;

    dark_vector_construct(allocator_, &ostream_->file_vector, dark_growth_simple, dark_file_struct_byte() + sizeof(void*));
    dark_vector_construct_capacity(allocator_, &ostream_->buffer_vector, dark_growth_simple, sizeof(char), dark_max_zu(512,settings_. buffer_size));

    ostream_->std.out_is = false;
    ostream_->std.err_is = false;
    ostream_->std.out_mutex = NULL;
    ostream_->std.err_mutex = NULL;
}

void dark_ostream_destruct(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    dark_ostream_flush(ostream_);

    for(size_t i = 0; i < dark_vector_size(&ostream_->file_vector); i++)
    {
        void* const file = dark_vector_at(&ostream_->file_vector, i);

        DARK_ASSERT(dark_file_open_is(file), DARK_ERROR_STATE);

        dark_file_destruct(file);
    }

    dark_vector_destruct(&ostream_->buffer_vector);
    dark_vector_destruct(&ostream_->file_vector);
}

Dark_Ostream* dark_ostream_new(Dark_Allocator* const allocator_, const Dark_Ostream_Settings settings_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");

    Dark_Ostream* const ostream = dark_malloc(allocator_, sizeof(*ostream));
    DARK_ASSERT(NULL != ostream, DARK_ERROR_ALLOCATION);

    dark_ostream_construct(allocator_, (Dark_Ostream*)ostream, settings_);

    return (Dark_Ostream*)ostream;
}

void dark_ostream_delete(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    dark_ostream_destruct(ostream_);

    dark_free(ostream_->allocator, ostream_, sizeof(*ostream_));
}

void dark_ostream_write(Dark_Ostream* const ostream_, const Dark_Buffer_View source_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(source_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);

    if(source_.byte == 0)
    {
        return;
    }

    if(dark_vector_size(&ostream_->buffer_vector) + source_.byte < ostream_->settings.buffer_size)
    {
        const Dark_Array_View view = { sizeof(uint8_t), source_.byte, source_.data };
        dark_vector_push_back(&ostream_->buffer_vector, view);

        return;
    }

    if(ostream_->settings.force_size_is)
    {
        const size_t fit = ostream_->settings.buffer_size - dark_vector_size(&ostream_->buffer_vector);

        const Dark_Array_View view = { sizeof(uint8_t), fit, source_.data };
        dark_vector_push_back(&ostream_->buffer_vector, view);

        for(size_t written = fit; written < source_.byte; written += DARK_MIN(source_.byte - written, ostream_->settings.buffer_size))
        {
            dark_ostream_flush(ostream_);

            const Dark_Array_View view = { sizeof(uint8_t), DARK_MIN(source_.byte - written, ostream_->settings.buffer_size), (uint8_t*)source_.data + written };
            dark_vector_push_back(&ostream_->buffer_vector, view);
        }
    }
    else
    {
        dark_ostream_flush(ostream_);
        dark_ostream_flush_unbuffered(ostream_, source_);
    }
}

void dark_ostream_flush(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    if(0 == dark_vector_size(&ostream_->buffer_vector))
    {
        return;
    }

    dark_ostream_flush_unbuffered(ostream_, dark_vector_buffer_view(&ostream_->buffer_vector));

    dark_vector_clear(&ostream_->buffer_vector);
}

void dark_ostream_flush_unbuffered(Dark_Ostream* const ostream_, const Dark_Buffer_View source_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(source_.byte > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != source_.data, DARK_ERROR_NULL);

    if(source_.byte == 0)
    {
        return;
    }

    for(size_t i = 0; i < dark_vector_size(&ostream_->file_vector); i++)
    {
        void* const file = dark_vector_at(&ostream_->file_vector, i);
        void* const mutex = *(void**)((char*)file + dark_file_struct_byte());

        if(NULL != mutex)
        {
            dark_mutex_lock(mutex);
        }

        DARK_ASSERT(dark_file_open_is(file), DARK_ERROR_STATE);

        if(ostream_->settings.binary_is)
        {
            const Dark_Array_View array_view = { sizeof(uint8_t), source_.byte, source_.data };

            dark_file_write_binary(file, array_view);
        }
        else
        {
            const Dark_Cbuffer_View cbuffer_view = { source_.byte, source_.data };

            dark_file_write(file, cbuffer_view);
        }

        if(NULL != mutex)
        {
            dark_mutex_unlock(mutex);
        }
    }

    if(ostream_->std.out_is)
    {
        if(NULL != ostream_->std.out_mutex)
        {
            dark_mutex_lock(ostream_->std.out_mutex);
        }

        const size_t result = fwrite(source_.data, sizeof(char), source_.byte, stdout);
        DARK_ASSERT_CSTRING(result == source_.byte, DARK_ERROR_RUNTIME, "writing to stdout failed");

        fflush(stdout);

        if(NULL != ostream_->std.out_mutex)
        {
            dark_mutex_unlock(ostream_->std.out_mutex);
        }
    }

    if(ostream_->std.err_is)
    {
        if(NULL != ostream_->std.err_mutex)
        {
            dark_mutex_lock(ostream_->std.err_mutex);
        }

        const size_t result = fwrite(source_.data, sizeof(char), source_.byte, stderr);
        DARK_ASSERT_CSTRING(result == source_.byte, DARK_ERROR_RUNTIME, "writing to stderr failed");

        fflush(stderr);

        if(NULL != ostream_->std.err_mutex)
        {
            dark_mutex_unlock(ostream_->std.err_mutex);
        }
    }
}

void dark_ostream_add_file(Dark_Ostream* const ostream_, const char* const path_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    //mutex_

    void* file = dark_vector_emplace(&ostream_->file_vector, dark_vector_size(&ostream_->file_vector), 1);
    dark_file_construct(ostream_->allocator, file);
    *(void**)((char*)file + dark_file_struct_byte()) = mutex_;

    Dark_File_Flag flag = DARK_FILE_FLAG_NONE;

    if(ostream_->settings.binary_is)
    {
        flag = DARK_FILE_FLAG_BINARY;
    }

    bool b = dark_file_open(file, path_, DARK_FILE_MODE_APPEND, flag);
    DARK_ASSERT_CSTRING(b, DARK_ERROR_UNKNOWN, "could not open file");
}

void dark_ostream_add_stdout(Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    ostream_->std.out_is = true;
    ostream_->std.out_mutex = mutex_;
}

void dark_ostream_add_stderr(Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    ostream_->std.err_is = true;
    ostream_->std.err_mutex = mutex_;
}
