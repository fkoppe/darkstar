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

#include "platform_module.h"

#include <dark/memory/memory.h>
#include <dark/platform/mutex_struct.h>
#include <dark/platform/platform.h>

#include <dark/core/core.h>

#undef DARK_UNIT
#define DARK_UNIT "mutex"

void dark_mutex_construct(Dark_Allocator* const allocator_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    mutex_->allocator = allocator_;
    mutex_->owned_is = false;
    mutex_->allocator = allocator_;

#if defined(___DARK_WINDOWS)
    InitializeCriticalSectionAndSpinCount(&mutex_->section, 128);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    int result = pthread_mutex_init(&mutex_->lock, NULL);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_init");
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

void dark_mutex_destruct(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

#if defined(___DARK_WINDOWS)
    DeleteCriticalSection(&mutex_->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    pthread_mutex_destroy(&mutex_->lock);
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

Dark_Mutex* dark_mutex_new(Dark_Allocator* const allocator_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);

    Dark_Mutex* const mutex = dark_malloc(allocator_, sizeof(*mutex));
    DARK_ASSERT(NULL != mutex, DARK_ERROR_ALLOCATION);

    dark_mutex_construct(allocator_, mutex);

    return mutex;
}

void dark_mutex_delete(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    dark_mutex_destruct(mutex_);

    dark_free(mutex_->allocator, mutex_, sizeof(*mutex_));
}

bool dark_mutex_trylock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    DARK_ASSERT_CSTRING(!mutex_->owned_is, DARK_ERROR_STATE, "");

#if defined(___DARK_WINDOWS)
    return TryEnterCriticalSection(&mutex_->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    return !pthread_mutex_trylock(&mutex_->lock);
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

void dark_mutex_lock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

#if defined(___DARK_WINDOWS)
    EnterCriticalSection(&mutex_->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    int result = pthread_mutex_lock(&mutex_->lock);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_lock");
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

    mutex_->owned_is = true;
}

void dark_mutex_unlock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

#if defined(___DARK_WINDOWS)
    LeaveCriticalSection(&mutex_->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    int result = pthread_mutex_unlock(&mutex_->lock);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_unlock");
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

    mutex_->owned_is = false;
}

size_t dark_mutex_struct_byte(void)
{
    return sizeof(Dark_Mutex);
}
