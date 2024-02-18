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
#define DARK_UNIT "thread"

#if defined(___DARK_LINUX)
#define ___DARK_UNIX
#endif // defined(___DARK_LINUX)

#if defined(___DARK_DARWIN)
#define ___DARK_UNIX
#endif // defined(___DARK_DARWIN)

#if defined(___DARK_WINDOWS)
#include <windows.h>
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
#include <pthread.h>
#endif // defined(___DARK_UNIX)

typedef struct DARK_Thread
{
    uint64_t id;
    bool joinable_is;

#if defined(___DARK_WINDOWS)
    HANDLE handle;
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    pthread_t handle;
#endif // defined(___DARK_UNIX)
} DARK_Thread;

void* dark_thread_new(void (* const function_), void* const argument_)
{
    DARK_ASSERT(NULL != function_, DARK_ERROR_NULL);
    //argument_

    DARK_Thread* thread = malloc(sizeof(*thread));
    DARK_ASSERT(NULL != thread, DARK_ERROR_ALLOCATION);

    thread->id = 0;
    thread->joinable_is = true;

#if defined(___DARK_WINDOWS)
    thread->handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function_, argument_, 0, (unsigned long*)&thread->id);
    DARK_ASSERT_MSG(NULL != thread->handle, DARK_ERROR_PLATFORM, "CreateThread");
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    int64_t result = pthread_create(&thread->handle, NULL, function_, argument_);
    DARK_ASSERT_MSG(0 == result, DARK_ERROR_PLATFORM, "pthread_create");

    thread->id = thread->handle;
#endif // defined(___DARK_UNIX)

    return thread;
}

void dark_thread_delete(void* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_Thread* thread = thread_;

    DARK_ASSERT_MSG(!thread->joinable_is, DARK_ERROR_NOSTATE, "thread was not joined or detached");

#if defined(___DARK_WINDOWS)
    bool b1 = CloseHandle(thread->handle);
    DARK_ASSERT_MSG(0 != b1, DARK_ERROR_PLATFORM, "CloseHandle");
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    //nothing
#endif // defined(___DARK_UNIX)

    free(thread);
}

uint64_t dark_thread_id(void* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_Thread* thread = thread_;

    return thread->id;
}

uint64_t dark_thread_id_current(void)
{
#if defined(___DARK_WINDOWS)
    return GetCurrentThreadId();
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    return pthread_self();
#endif // defined(___DARK_UNIX)
}

bool dark_thread_joinable(void* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_Thread* thread = thread_;

    return thread->joinable_is;
}

void dark_thread_join(void* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_Thread* thread = thread_;

#if defined(___DARK_WINDOWS)
    switch (WaitForSingleObject(thread->handle, INFINITE))
    {
    case WAIT_OBJECT_0:
        break;
    case WAIT_FAILED:
    case WAIT_ABANDONED:
    case WAIT_TIMEOUT:
        DARK_EXIT_MSG(-1, DARK_ERROR_PLATFORM, "WaitForSingleObject");
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_UNIX)
    int64_t result = pthread_join(thread->handle, NULL);
    DARK_ASSERT_MSG(0 == result, DARK_ERROR_PLATFORM, "pthread_join");
#endif // defined(___DARK_UNIX)

    thread->joinable_is = false;
}

void dark_thread_detach(void* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_Thread* thread = thread_;

    thread->joinable_is = false;
}
