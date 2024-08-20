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
#include <dark/math/math.h>
#include <dark/memory/memory.h>
#include <dark/platform/platform.h>
#include <dark/platform/thread_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "thread"

void dark_thread_construct(Dark_Allocator* const allocator_, Dark_Thread* const thread_, const Dark_Thread_Worker function_, void* const argument_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != function_, DARK_ERROR_NULL);
    //argument_

    thread_->allocator = allocator_;
    thread_->id = 0;
    thread_->joinable_is = true;

#if defined(___DARK_WINDOWS)
    thread_->handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function_, argument_, 0, (LPDWORD)&thread_->id);
    DARK_ASSERT_CSTRING(NULL != thread_->handle, DARK_ERROR_PLATFORM, "CreateThread");
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    int64_t result = pthread_create(&thread_->handle, NULL, (void*)function_, argument_);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_create");

    thread_->id = thread_->handle;
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

void dark_thread_destruct(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

#if defined(___DARK_WINDOWS)
    bool b1 = CloseHandle(thread_->handle);
    DARK_ASSERT_CSTRING(0 != b1, DARK_ERROR_PLATFORM, "CloseHandle");
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    //nothing
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}

void* dark_thread_new(Dark_Allocator* const allocator_, const Dark_Thread_Worker function_, void* const argument_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != function_, DARK_ERROR_NULL);
    //argument_

    Dark_Thread* const thread = dark_malloc(allocator_, sizeof(*thread));
    DARK_ASSERT(NULL != thread, DARK_ERROR_ALLOCATION);

    dark_thread_construct(allocator_, thread, function_, argument_);

    return thread;
}

void dark_thread_delete(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(!thread_->joinable_is, DARK_ERROR_STATE, DARK_MESSAGE_THREAD_JOINABLE);

    dark_thread_destruct(thread_);

    dark_free(thread_->allocator, thread_, sizeof(*thread_));
}

uint64_t dark_thread_id(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    return thread_->id;
}

bool dark_thread_joinable(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    return thread_->joinable_is;
}

void dark_thread_join(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(thread_->joinable_is, DARK_ERROR_STATE, DARK_MESSAGE_THREAD_JOINABLE_NOT);

#if defined(___DARK_WINDOWS)
    switch (WaitForSingleObject(thread_->handle, INFINITE))
    {
    case WAIT_OBJECT_0:
        break;
    case WAIT_FAILED:
    case WAIT_ABANDONED:
    case WAIT_TIMEOUT:
        DARK_ASSERT_CSTRING(-1, DARK_ERROR_PLATFORM, "WaitForSingleObject");
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
        break;
    }
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    int64_t result = pthread_join(thread_->handle, NULL);
    DARK_ASSERT_CSTRING(0 == result, DARK_ERROR_PLATFORM, "pthread_join");
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)

    thread_->joinable_is = false;
}

void dark_thread_detach(Dark_Thread* const thread_)
{
    DARK_ASSERT(NULL != thread_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(thread_->joinable_is, DARK_ERROR_STATE, DARK_MESSAGE_THREAD_JOINABLE_NOT);

    thread_->joinable_is = false;
}

size_t dark_thread_struct_byte(void)
{
    return sizeof(Dark_Thread);
}

uint64_t dark_thread_current_id(void)
{
#if defined(___DARK_WINDOWS)
    return (uint64_t)GetCurrentThreadId();
#endif // defined(___DARK_WINDOWS)

#if defined(___DARK_LINUX) || defined(___DARK_DARWIN)
    return (uint64_t)pthread_self();
#endif // defined(___DARK_LINUX) || defined(___DARK_DARWIN)
}
