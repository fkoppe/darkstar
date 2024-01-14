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

#if !defined(___DARK___MEMPROF_H)
#define ___DARK___MEMPROF_H

#include <dark/core/essential.h>
#include <dark/core/library.h>
#include <dark/core/module.h>
#include <dark/core/unit.h>

#if defined(___DARK_DEBUG)
#define malloc(size) dark_memory_profiler_malloc((size), __FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT)
#define realloc(pointer, size) dark_memory_profiler_realloc((pointer), (size), __FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT)
#define calloc(count, size) dark_memory_profiler_calloc((count), (size), __FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT)
#define free(pointer) dark_memory_profiler_free((pointer), __FILE__, __func__, __LINE__, __DATE__, __TIME__, DARK_LIBRARY, DARK_MODULE, DARK_UNIT)
#endif // defined(___DARK_DEBUG)

#if !defined(DARK_MEMORY_PROFILER_INFO_COUNT_MAX)
#define DARK_MEMORY_PROFILER_INFO_COUNT_MAX 1024
#endif // !defined(DARK_MEMORY_PROFILER_INFO_COUNT_MAX)

typedef enum Dark_Memory_Profile_Level
{
    DARK_MEMORY_PROFILE_LEVEL_NONE,
    DARK_MEMORY_PROFILE_LEVEL_REDUCED,
    DARK_MEMORY_PROFILE_LEVEL_FULL,
    ___DARK_MEMORY_PROFILE_LEVEL_MAX,
} Dark_Memory_Profile_Level;

typedef struct Dark_Memory_Info
{
    struct
    {
        size_t count;
        size_t usage;
    } current;
    struct
    {
        size_t count;
        size_t usage;
    } total;
    struct
    {
        size_t count;
        size_t usage;
    } peak;
} Dark_Memory_Info;

void dark_memory_profiler_initialise(Dark_Memory_Profile_Level level, bool assert_pointer_is);
void dark_memory_profiler_shutdown(bool print_error_is);

void dark_memory_profiler_print_info_stdout();

Dark_Memory_Info dark_memory_profiler_info_all();
Dark_Memory_Info dark_memory_profiler_info_own();

void* dark_memory_profiler_malloc(size_t size, const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit);
void* dark_memory_profiler_realloc(void* pointer, size_t size, const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit);
void* dark_memory_profiler_calloc(size_t count, size_t size, const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit);
void dark_memory_profiler_free(void* pointer, const char* file, const char* func, int64_t line, const char* date, const char* time, const Dark_Library* library, const char* module, const char* unit);

#endif // !defined(___DARK___MEMPROF_H)
