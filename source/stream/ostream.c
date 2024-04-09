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

#include <dark/container/container.h>
#include <dark/core/core.h>
#include <dark/stream/stream.h>
#include <dark/platform/platform.h>

#include <stdio.h>

#undef DARK_UNIT
#define DARK_UNIT "ostream"

typedef struct Dark_Ostream_Struct
{
    Dark_Stream_Setting settings;
    Dark_Array* file_array;
    Dark_Array* buffer_array;
    struct
    {
        bool out_is;
        bool err_is;
        void* out_mutex;
        void* err_mutex;
    } std;
} Dark_Ostream_Struct;

size_t dark_ostream_struct_size(void)
{
    return sizeof(Dark_Ostream_Struct);
}

Dark_Ostream* dark_ostream_new(const Dark_Stream_Setting settings_)
{
    DARK_ASSERT_MSG(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");

    Dark_Ostream_Struct* const ostream = malloc(sizeof(*ostream));
    DARK_ASSERT(NULL != ostream, DARK_ERROR_ALLOCATION);

    ostream->settings = settings_;
    ostream->file_array = dark_array_new(dark_file_struct_size() + sizeof(void*));

    if(0 != settings_.buffer_size)
    {
        ostream->buffer_array = dark_array_new_capacity(sizeof(char), settings_.buffer_size);
    }
    ostream->std.out_is = false;
    ostream->std.err_is = false;
    ostream->std.out_mutex = NULL;
    ostream->std.err_mutex = NULL;

    return (Dark_Ostream*)ostream;
}

void dark_ostream_delete(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    dark_ostream_flush((Dark_Ostream*)ostream);

    for(size_t i = 0; i < dark_array_size(ostream->file_array); i++)
    {
        void* const file = dark_array_at(ostream->file_array, i);

        DARK_ASSERT(dark_file_open_is(file), DARK_ERROR_STATE);

        dark_file_destroy(file);
    }

    if(0 != ostream->settings.buffer_size)
    {
        dark_array_delete(ostream->buffer_array);
    }

    dark_array_delete(ostream->file_array);

    free(ostream);
}

void dark_ostream_write(Dark_Ostream* const ostream_, const size_t byte_, const void* const data_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    if(byte_ == 0)
    {
        return;
    }

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    if(dark_array_size(ostream->buffer_array) + byte_ < ostream->settings.buffer_size)
    {
        dark_array_push_back_c(ostream->buffer_array, byte_, data_);

        return;
    }

    if(ostream->settings.force_size_is)
    {
        const size_t fit = ostream->settings.buffer_size - dark_array_size(ostream->buffer_array);

        dark_array_push_back_c(ostream->buffer_array, fit, data_);

        for(size_t written = fit; written < byte_; written += DARK_MIN(byte_ - written, ostream->settings.buffer_size))
        {
            dark_ostream_flush((Dark_Ostream*)ostream);

            dark_array_push_back_c(ostream->buffer_array, DARK_MIN(byte_ - written, ostream->settings.buffer_size), (char*)data_ + written);
        }
    }
    else
    {
        dark_ostream_flush((Dark_Ostream*)ostream);
        dark_ostream_flush_unbuffered((Dark_Ostream*)ostream, byte_, data_);
    }
}

void dark_ostream_flush(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    if(0 == dark_array_size(ostream->buffer_array))
    {
        return;
    }

    dark_ostream_flush_unbuffered((Dark_Ostream*)ostream, dark_array_size(ostream->buffer_array), dark_array_data(ostream->buffer_array));

    dark_array_clear(ostream->buffer_array);
}

void dark_ostream_flush_unbuffered(Dark_Ostream* const ostream_, const size_t byte_, const void* const data_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(byte_ > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != data_, DARK_ERROR_NULL);

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    if(byte_ == 0)
    {
        return;
    }

    for(size_t i = 0; i < dark_array_size(ostream->file_array); i++)
    {
        void* const file = dark_array_at(ostream->file_array, i);
        void* const mutex = *(void**)((char*)file + dark_file_struct_size());

        if(NULL != mutex)
        {
            dark_mutex_lock(mutex);
        }

        DARK_ASSERT(dark_file_open_is(file), DARK_ERROR_STATE);

        dark_file_write(file, sizeof(char), byte_, data_);

        if(NULL != mutex)
        {
            dark_mutex_unlock(mutex);
        }
    }

    if(ostream->std.out_is)
    {
        if(NULL != ostream->std.out_mutex)
        {
            dark_mutex_lock(ostream->std.out_mutex);
        }

        const size_t result =fwrite(data_, sizeof(char), byte_, stdout);
        DARK_ASSERT_MSG(result == byte_, DARK_ERROR_RUNTIME, "writing to stdout failed");

        fflush(stdout);

        if(NULL != ostream->std.out_mutex)
        {
            dark_mutex_unlock(ostream->std.out_mutex);
        }
    }

    if(ostream->std.err_is)
    {
        if(NULL != ostream->std.err_mutex)
        {
            dark_mutex_lock(ostream->std.err_mutex);
        }

        const size_t result =fwrite(data_, sizeof(char), byte_, stderr);
        DARK_ASSERT_MSG(result == byte_, DARK_ERROR_RUNTIME, "writing to stderr failed");

        fflush(stderr);

        if(NULL != ostream->std.err_mutex)
        {
            dark_mutex_unlock(ostream->std.err_mutex);
        }
    }
}

void dark_ostream_add_file(Dark_Ostream* const ostream_, const char* const path_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    //mutex_

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    void* file = dark_array_emplace(ostream->file_array, dark_array_size(ostream->file_array), 1);
    dark_file_create(file);
    *(void**)((char*)file + dark_file_struct_size()) = mutex_;

    Dark_File_Flag flag = DARK_FILE_FLAG_NONE;

    if(ostream->settings.binary_is)
    {
        flag = DARK_FILE_FLAG_BINARY;
    }

    bool b = dark_file_open(file, path_, DARK_FILE_MODE_APPEND, flag);
    DARK_ASSERT_MSG(b, DARK_ERROR_UNKNOWN, "could not open file");
}

void dark_ostream_add_stdout(Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    ostream->std.out_is = true;
    ostream->std.out_mutex = mutex_;
}

void dark_ostream_add_sterr(Dark_Ostream* const ostream_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    //mutex_

    Dark_Ostream_Struct* const ostream = (Dark_Ostream_Struct*)ostream_;

    ostream->std.err_is = true;
    ostream->std.err_mutex = mutex_;
}
