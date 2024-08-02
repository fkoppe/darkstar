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

#include "platform_module.h"

#include <dark/core/core.h>
#include <dark/platform/platform.h>

#undef DARK_UNIT
#define DARK_UNIT "mutex"

#if defined(___DARK_LINUX)
#define ___DARK_UNIX
#endif // defined(___DARK_LINUX)

#if defined(___DARK_DARWIN)
#define ___DARK_UNIX
#endif // defined(___DARK_DARWIN)

#if defined(___DARK_WINDOWS)
#include <dark/windows.h>
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
#include <pthread.h>
#endif // defined(___DARK_UNIX)

typedef struct Dark_Mutex_Struct Dark_Mutex_Struct;
struct Dark_Mutex_Struct
{
    bool owned_is;
    Dark_Allocator* allocator;
#if defined(___DARK_WINDOWS)
    CRITICAL_SECTION section;
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    pthread_mutex_t lock;
#endif // defined(___DARK_UNIX)
};

size_t dark_mutex_struct_byte(void)
{
    return sizeof(Dark_Mutex_Struct);
}

void dark_mutex_create(Dark_Allocator* const allocator_, Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

    mutex->owned_is = false;
    mutex->allocator = allocator_;

#if defined(___DARK_WINDOWS)
    InitializeCriticalSectionAndSpinCount(&mutex->section, 128);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    int result = pthread_mutex_init(&mutex->lock, NULL);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_init");
#endif // defined(___DARK_UNIX)
}

void dark_mutex_destroy(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

#if defined(___DARK_WINDOWS)
    DeleteCriticalSection(&mutex->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    pthread_mutex_destroy(&mutex->lock);
#endif // defined(___DARK_UNIX)
}

Dark_Mutex* dark_mutex_new(Dark_Allocator* const allocator_)
{
    Dark_Mutex_Struct* const mutex = dark_malloc(allocator_, sizeof(*mutex));
    DARK_ASSERT(NULL != mutex, DARK_ERROR_ALLOCATION);

    dark_mutex_create(allocator_, (Dark_Mutex*)mutex);

    return (Dark_Mutex*)mutex;
}

void dark_mutex_delete(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

    dark_mutex_destroy((Dark_Mutex*)mutex);

    dark_free(mutex->allocator, mutex, sizeof(*mutex));
}

bool dark_mutex_trylock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

    DARK_ASSERT_CSTRING(!mutex->owned_is, DARK_ERROR_STATE, "");

#if defined(___DARK_WINDOWS)
    return TryEnterCriticalSection(&mutex->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    return !pthread_mutex_trylock(&mutex->lock);
#endif // defined(___DARK_UNIX)
}

void dark_mutex_lock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

#if defined(___DARK_WINDOWS)
    EnterCriticalSection(&mutex->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    int result = pthread_mutex_lock(&mutex->lock);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_lock");
#endif // defined(___DARK_UNIX)

    mutex->owned_is = true;
}

void dark_mutex_unlock(Dark_Mutex* const mutex_)
{
    DARK_ASSERT(NULL != mutex_, DARK_ERROR_NULL);

    Dark_Mutex_Struct* const mutex = (Dark_Mutex_Struct*)mutex_;

#if defined(___DARK_WINDOWS)
    LeaveCriticalSection(&mutex->section);
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    int result = pthread_mutex_unlock(&mutex->lock);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_mutex_unlock");
#endif // defined(___DARK_UNIX)

    mutex->owned_is = false;
}
