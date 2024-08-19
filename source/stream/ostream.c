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

#include <dark/char/char.h>
#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/platform/platform.h>
#include <dark/stream/ostream_struct.h>
#include <dark/stream/stream.h>

#include <time.h>
#include <stdio.h>

#undef DARK_UNIT
#define DARK_UNIT "ostream"

void dark_ostream_construct_file(Dark_Allocator* const allocator_, Dark_Ostream* const ostream_, const Dark_Ostream_Settings settings_, const char* const path_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    //mutex_

    DARK_CSTRING_ASSERT_CONTENT(path_);

    ostream_->allocator = allocator_;
    ostream_->settings = settings_;

    dark_vector_construct_capacity(allocator_, &ostream_->buffer_vector, dark_growth_simple, sizeof(char), dark_max_zu(512,settings_. buffer_size));

    ostream_->mutex = mutex_;
    ostream_->type = DARK_OSTREAM_TYPE_FILE;

    ostream_->data.file = dark_file_new(allocator_);

    Dark_File_Flag flag = DARK_FILE_FLAG_NONE;

    if(ostream_->settings.binary_is)
    {
        flag = DARK_FILE_FLAG_BINARY;
    }

    const Dark_Oserror result = dark_file_open(ostream_->data.file, path_, DARK_FILE_MODE_APPEND, flag);

    if(DARK_OSERROR_NONE != result)
    {
        const Dark_Message message = { &DARK_MESSAGE_FILE_OPEN, NULL, path_ };
        DARK_EXIT_MESSAGE(-1, DARK_ERROR_RUNTIME, message);
    }

    if(ostream_->settings.auto_flush_ns > 0)
    {
        ostream_->stopwatch = dark_stopwatch_new_start(allocator_);
    }
}

void dark_ostream_construct_stdout(Dark_Allocator* const allocator_, Dark_Ostream* const ostream_, const Dark_Ostream_Settings settings_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    //mutex_

    ostream_->allocator = allocator_;
    ostream_->settings = settings_;

    dark_vector_construct_capacity(allocator_, &ostream_->buffer_vector, dark_growth_simple, sizeof(char), dark_max_zu(512,settings_. buffer_size));

    ostream_->mutex = mutex_;
    ostream_->type = DARK_OSTREAM_TYPE_STD;

    ostream_->data.std = stdout;

    if(ostream_->settings.auto_flush_ns > 0)
    {
        ostream_->stopwatch = dark_stopwatch_new_start(allocator_);
    }
}

void dark_ostream_construct_stderr(Dark_Allocator* const allocator_, Dark_Ostream* const ostream_, const Dark_Ostream_Settings settings_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    //mutex_

    ostream_->allocator = allocator_;
    ostream_->settings = settings_;

    dark_vector_construct_capacity(allocator_, &ostream_->buffer_vector, dark_growth_simple, sizeof(char), dark_max_zu(512,settings_. buffer_size));

    ostream_->mutex = mutex_;
    ostream_->type = DARK_OSTREAM_TYPE_STD;

    ostream_->data.std = stderr;

    if(ostream_->settings.auto_flush_ns > 0)
    {
        ostream_->stopwatch = dark_stopwatch_new_start(allocator_);
    }
}

void dark_ostream_destruct(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    dark_ostream_flush(ostream_);

    if(ostream_->settings.auto_flush_ns > 0)
    {
        dark_stopwatch_delete(ostream_->stopwatch);
    }

    if(DARK_OSTREAM_TYPE_FILE == ostream_->type)
    {
        DARK_ASSERT(dark_file_open_is(ostream_->data.file), DARK_ERROR_STATE);

        const Dark_Oserror result = dark_file_close(ostream_->data.file);

        if(DARK_OSERROR_NONE != result)
        {
            DARK_EXIT_MESSAGE(-1, DARK_ERROR_RUNTIME, DARK_MESSAGE_FILE_CLOSE);
        }

        dark_file_delete(ostream_->data.file);
    }

    dark_vector_destruct(&ostream_->buffer_vector);
}

Dark_Ostream* dark_ostream_new_file(Dark_Allocator* const allocator_, const Dark_Ostream_Settings settings_, const char* const path_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    DARK_ASSERT(NULL != path_, DARK_ERROR_NULL);
    //mutex_

    DARK_CSTRING_ASSERT_CONTENT(path_);

    Dark_Ostream* const ostream = dark_malloc(allocator_, sizeof(*ostream));
    DARK_ASSERT(NULL != ostream, DARK_ERROR_ALLOCATION);

    dark_ostream_construct_file(allocator_, (Dark_Ostream*)ostream, settings_, path_, mutex_);

    return (Dark_Ostream*)ostream;
}

Dark_Ostream* dark_ostream_new_stdout(Dark_Allocator* const allocator_, const Dark_Ostream_Settings settings_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    //mutex_

    Dark_Ostream* const ostream = dark_malloc(allocator_, sizeof(*ostream));
    DARK_ASSERT(NULL != ostream, DARK_ERROR_ALLOCATION);

    dark_ostream_construct_stdout(allocator_, (Dark_Ostream*)ostream, settings_, mutex_);

    return (Dark_Ostream*)ostream;
}

Dark_Ostream* dark_ostream_new_stderr(Dark_Allocator* const allocator_, const Dark_Ostream_Settings settings_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT_CSTRING(!(0 == settings_.buffer_size) || !settings_.force_size_is, DARK_ERROR_LOGIC, "can not force size to 0");
    //mutex_

    Dark_Ostream* const ostream = dark_malloc(allocator_, sizeof(*ostream));
    DARK_ASSERT(NULL != ostream, DARK_ERROR_ALLOCATION);

    dark_ostream_construct_stderr(allocator_, (Dark_Ostream*)ostream, settings_, mutex_);

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

        dark_ostream_update(ostream_);

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

    if(ostream_->settings.auto_flush_ns > 0)
    {
        dark_stopwatch_restart(ostream_->stopwatch);
    }

    if(NULL != ostream_->mutex)
    {
        dark_mutex_lock(ostream_->mutex);
    }

    if(DARK_OSTREAM_TYPE_FILE == ostream_->type)
    {
        DARK_ASSERT(dark_file_open_is(ostream_->data.file), DARK_ERROR_STATE);

        Dark_Oserror result;

        if(ostream_->settings.binary_is)
        {
            const Dark_Array_View array_view = { sizeof(uint8_t), source_.byte, source_.data };
            result = dark_file_write_binary(ostream_->data.file, array_view);
        }
        else
        {
            const Dark_Cbuffer_View cbuffer_view = { source_.byte, source_.data };
            result = dark_file_write(ostream_->data.file, cbuffer_view);
        }

        if(DARK_OSERROR_NONE != result)
        {
            DARK_EXIT_MESSAGE(-1, DARK_ERROR_RUNTIME, DARK_MESSAGE_FILE_WRITE);
        }
    }
    else
    {
        const size_t result = fwrite(source_.data, sizeof(char), source_.byte, ostream_->data.std);
        DARK_ASSERT_CSTRING(result == source_.byte, DARK_ERROR_RUNTIME, "writing to stdout/err failed");

        fflush(stdout);

        if(NULL != ostream_->mutex)
        {
            dark_mutex_unlock(ostream_->mutex);
        }
    }

    if(NULL != ostream_->mutex)
    {
        dark_mutex_unlock(ostream_->mutex);
    }
}

void dark_ostream_update(Dark_Ostream* const ostream_)
{
    DARK_ASSERT(NULL != ostream_, DARK_ERROR_NULL);

    if(0 == ostream_->settings.auto_flush_ns)
    {
        return;
    }

    if(dark_stopwatch_ns(ostream_->stopwatch) >= ostream_->settings.auto_flush_ns)
    {
        dark_ostream_flush(ostream_);
    }
}

size_t dark_ostream_struct_byte(void)
{
    return sizeof(Dark_Ostream);
}
