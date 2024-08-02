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

#include "memory_debug_helper.h"
#include "memory_module.h"

#include <dark/core/core.h>
#include <dark/memory/memory.h>

#include <stdlib.h>

#undef DARK_UNIT
#define DARK_UNIT "memory_debug"

typedef struct Dark_Debug_Memory
{
    bool initialise_is;
    struct
    {
        size_t count;
        size_t capacity;
        Dark_Memory_Debug_Info* array;
    } info;
} Dark_Debug_Memory;

static const size_t DEBUG_MEMORY_CAPACITY = 2048;

static Dark_Debug_Memory DEBUG_MEMORY = { .initialise_is = false };

void dark_memory_debug_initialise(void)
{
    DARK_ASSERT(!DEBUG_MEMORY.initialise_is, DARK_ERROR_STATE);

    DEBUG_MEMORY.initialise_is = true;
    DEBUG_MEMORY.info.count = 0;
    DEBUG_MEMORY.info.capacity = DEBUG_MEMORY_CAPACITY;

    DEBUG_MEMORY.info.array = malloc(DEBUG_MEMORY_CAPACITY * sizeof(Dark_Memory_Debug_Info));
    DARK_ASSERT(NULL != DEBUG_MEMORY.info.array, DARK_ERROR_ALLOCATION);
}

void dark_memory_debug_tryinitialise(void)
{
    if(!DEBUG_MEMORY.initialise_is)
    {
        dark_memory_debug_initialise();
    }
}

void dark_memory_debug_shutdown(void)
{
    DARK_ASSERT(DEBUG_MEMORY.initialise_is, DARK_ERROR_STATE);

    DEBUG_MEMORY.initialise_is = false;

    for(size_t i = 0; i < DEBUG_MEMORY.info.count; i++)
    {
        dark_memory_debug_print_leak(DEBUG_MEMORY.info.array[i], i);
    }

    const size_t count = DEBUG_MEMORY.info.count;

    free(DEBUG_MEMORY.info.array);

    if(count > 0)
    {
        dark_memory_debug_print_leak_count(count);

        abort();
    }
}

void dark_memory_debug_tryshutdown(void)
{
    if(DEBUG_MEMORY.initialise_is)
    {
        dark_memory_debug_shutdown();
    }
}

void* dark_memory_debug_allocate(const Dark_Location location_, const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const func_name_, Dark_Allocator* const allocator_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != location_.file, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.func, DARK_ERROR_NULL);
    DARK_ASSERT(0 != location_.line, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.date, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.time, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_
    DARK_ASSERT(NULL != func_name_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //address_
    //byte_old_
    //byte_new_

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    Dark_Memory_Debug_Info call_info;
    call_info.allocator = allocator_;
    call_info.address = NULL;
    call_info.byte = byte_old_;
    call_info.location.func = location_.func;
    call_info.location.file = location_.file;
    call_info.location.line = location_.line;
    call_info.location.date = location_.date;
    call_info.location.time = location_.time;
    call_info.library = library_;
    call_info.module = module_;
    call_info.unit = unit_;
    call_info.func_name = func_name_;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_MEMORY_DEBUG_ASSERT(call_info, NULL == address_);
        DARK_MEMORY_DEBUG_ASSERT(call_info, 0 == byte_old_);
        DARK_MEMORY_DEBUG_ASSERT(call_info, byte_new_ > 0);

        void* pointer = allocator->allocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL == pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "allocation failed");

            return pointer;
        }

        if(!DEBUG_MEMORY.initialise_is)
        {
            return pointer;
        }

        if(DEBUG_MEMORY.info.count >= DEBUG_MEMORY.info.capacity)
        {
            DEBUG_MEMORY.info.array = realloc(DEBUG_MEMORY.info.array, (DEBUG_MEMORY.info.capacity + DEBUG_MEMORY_CAPACITY) * sizeof(Dark_Memory_Debug_Info));
            DARK_ASSERT(NULL != DEBUG_MEMORY.info.array, DARK_ERROR_ALLOCATION);

            DEBUG_MEMORY.info.capacity += DEBUG_MEMORY_CAPACITY;
        }

        DEBUG_MEMORY.info.count++;

        call_info.address = pointer;
        call_info.byte = byte_new_;
        DEBUG_MEMORY.info.array[DEBUG_MEMORY.info.count - 1] = call_info;

        return pointer;
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_MEMORY_DEBUG_ASSERT(call_info, byte_old_ > 0);

        bool known_is = false;
        size_t index = 0;

        if(DEBUG_MEMORY.initialise_is)
        {
            for(size_t i = 0; i < DEBUG_MEMORY.info.count; i++)
            {
                if(address_ == DEBUG_MEMORY.info.array[i].address)
                {
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].allocator == allocator_);
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].byte == byte_old_);

                    known_is = true;
                    index = i;
                }
            }

            if(!known_is)
            {
                DARK_MEMORY_DEBUG_EXIT(call_info, "tried to free unknown address");
            }
        }

        void* pointer = allocator->allocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL != pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "free failed");

            return pointer;
        }

        if(known_is)
        {
            DEBUG_MEMORY.info.array[index] = DEBUG_MEMORY.info.array[DEBUG_MEMORY.info.count - 1];

            DEBUG_MEMORY.info.count--;
        }

        return pointer;
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > 0)
    {
        bool known_is = false;
        size_t index = 0;

        if(DEBUG_MEMORY.initialise_is)
        {
            for(size_t i = 0; i < DEBUG_MEMORY.info.count; i++)
            {
                if(address_ == DEBUG_MEMORY.info.array[i].address)
                {
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].allocator == allocator_);
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].byte == byte_old_);

                    known_is = true;
                    index = i;
                }
            }

            if(!known_is)
            {
                DARK_MEMORY_DEBUG_EXIT(call_info, "tried to realloc unknown address");
            }
        }

        void* pointer = allocator->allocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL == pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "realloc failed");

            return pointer;
        }

        if(known_is)
        {
            call_info.address = pointer;
            call_info.byte = byte_new_;
            DEBUG_MEMORY.info.array[index] = call_info;
        }

        return pointer;
    }
    else
    {
        DARK_MEMORY_DEBUG_EXIT(call_info, "invalid use of parameters");

        return NULL;
    }
}

void* dark_memory_debug_callocate(const Dark_Location location_, const Dark_Library* const library_, const char* const module_, const char* const unit_, const char* const func_name_, Dark_Allocator* const allocator_, void* const address_, const size_t byte_old_, const size_t byte_new_)
{
    DARK_ASSERT(NULL != location_.file, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.func, DARK_ERROR_NULL);
    DARK_ASSERT(0 != location_.line, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.date, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != location_.time, DARK_ERROR_NULL);
    //library_
    //module_
    //unit_
    DARK_ASSERT(NULL != func_name_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //address_
    //byte_old_
    //byte_new_

    Dark_Allocator_Struct* const allocator = (Dark_Allocator_Struct*)allocator_;

    Dark_Memory_Debug_Info call_info;
    call_info.allocator = allocator_;
    call_info.address = NULL;
    call_info.byte = byte_old_;
    call_info.location.func = location_.func;
    call_info.location.file = location_.file;
    call_info.location.line = location_.line;
    call_info.location.date = location_.date;
    call_info.location.time = location_.time;
    call_info.library = library_;
    call_info.module = module_;
    call_info.unit = unit_;
    call_info.func_name = func_name_;

    if(NULL == address_ || 0 == byte_old_)
    {
        DARK_MEMORY_DEBUG_ASSERT(call_info, NULL == address_);
        DARK_MEMORY_DEBUG_ASSERT(call_info, 0 == byte_old_);
        DARK_MEMORY_DEBUG_ASSERT(call_info, byte_new_ > 0);

        void* pointer = allocator->callocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL == pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "callocation failed");

            return pointer;
        }

        if(!DEBUG_MEMORY.initialise_is)
        {
            return pointer;
        }

        if(DEBUG_MEMORY.info.count >= DEBUG_MEMORY.info.capacity)
        {
            DEBUG_MEMORY.info.array = realloc(DEBUG_MEMORY.info.array, (DEBUG_MEMORY.info.capacity + DEBUG_MEMORY_CAPACITY) * sizeof(Dark_Memory_Debug_Info));
            DARK_ASSERT(NULL != DEBUG_MEMORY.info.array, DARK_ERROR_ALLOCATION);

            DEBUG_MEMORY.info.capacity += DEBUG_MEMORY_CAPACITY;
        }

        DEBUG_MEMORY.info.count++;

        call_info.address = pointer;
        call_info.byte = byte_new_;
        DEBUG_MEMORY.info.array[DEBUG_MEMORY.info.count - 1] = call_info;

        return pointer;
    }
    else if(NULL != address_ && 0 == byte_new_)
    {
        DARK_MEMORY_DEBUG_ASSERT(call_info, byte_old_ > 0);

        bool known_is = false;
        size_t index = 0;

        if(DEBUG_MEMORY.initialise_is)
        {
            for(size_t i = 0; i < DEBUG_MEMORY.info.count; i++)
            {
                if(address_ == DEBUG_MEMORY.info.array[i].address)
                {
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].allocator == allocator_);
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].byte == byte_old_);

                    known_is = true;
                    index = i;
                }
            }

            if(!known_is)
            {
                DARK_MEMORY_DEBUG_EXIT(call_info, "tried to free unknown address");
            }
        }

        void* pointer = allocator->callocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL != pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "free failed");

            return pointer;
        }

        if(known_is)
        {
            DEBUG_MEMORY.info.array[DEBUG_MEMORY.info.count - 1] = DEBUG_MEMORY.info.array[index];

            DEBUG_MEMORY.info.count--;
        }

        return pointer;
    }
    else if(NULL != address_ && byte_old_ > 0 && byte_new_ > 0)
    {
        bool known_is = false;
        size_t index = 0;

        if(DEBUG_MEMORY.initialise_is)
        {
            for(size_t i = 0; i < DEBUG_MEMORY.info.count; i++)
            {
                if(address_ == DEBUG_MEMORY.info.array[i].address)
                {
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].allocator == allocator_);
                    DARK_MEMORY_DEBUG_MATCH(call_info, DEBUG_MEMORY.info.array[i], DEBUG_MEMORY.info.array[i].byte == byte_old_);

                    known_is = true;
                    index = i;
                }
            }

            if(!known_is)
            {
                DARK_MEMORY_DEBUG_EXIT(call_info, "tried to recalloc unknown address");
            }
        }

        void* pointer = allocator->callocate(allocator->context, address_, byte_old_, byte_new_);

        if(NULL == pointer)
        {
            DARK_MEMORY_DEBUG_WARN(call_info, "recalloc failed");

            return pointer;
        }

        if(known_is)
        {
            call_info.address = pointer;
            call_info.byte = byte_new_;
            DEBUG_MEMORY.info.array[index] = call_info;
        }

        return pointer;
    }
    else
    {
        DARK_MEMORY_DEBUG_EXIT(call_info, "invalid use of parameters");

        return NULL;
    }
}
