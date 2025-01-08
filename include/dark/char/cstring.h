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

#if !defined(___DARK___CSTRING_H)
#define ___DARK___CSTRING_H

#include <dark/char/cbuffer_view.h>
#include <dark/core/std.h>
#include <dark/tool/array_view.h>
#include <dark/tool/buffer_view.h>

#define DARK_CSTRING_LENGHT_MAX 256

#if defined(___DARK_DEBUG)
#define DARK_CSTRING_ASSERT_INTEGRITY(cstring) \
DARK_ASSERT_CSTRING(NULL != cstring, DARK_ERROR_NULL, "cstring was null");\
for(size_t i = 0; i <= DARK_CSTRING_LENGHT_MAX; i++) \
{ \
    if('\0' == cstring[i])\
    { \
        i = DARK_CSTRING_LENGHT_MAX + 1; \
    } \
    if(i == DARK_CSTRING_LENGHT_MAX) \
    { \
        DARK_EXIT_CSTRING(-1, DARK_ERROR_RUNTIME, "cstring lost integrity"); \
    } \
} DARK_INSTRUCTION

#define DARK_CSTRING_ASSERT_CONTENT(cstring) \
for(size_t i = 0; i <= DARK_CSTRING_LENGHT_MAX; i++) \
{ \
    if('\0' == cstring[i])\
    { \
        DARK_ASSERT_CSTRING(0 != i, DARK_ERROR_RUNTIME, "cstring was empty"); \
        i = DARK_CSTRING_LENGHT_MAX + 1; \
    } \
    if(i == DARK_CSTRING_LENGHT_MAX) \
    { \
        DARK_EXIT_CSTRING(-1, DARK_ERROR_RUNTIME, "cstring lost integrity"); \
    } \
} DARK_INSTRUCTION

#else
#define DARK_CSTRING_ASSERT_INTEGRITY(cstring)
#define DARK_CSTRING_ASSERT_CONTENT(cstring)
#endif // defined(___DARK_DEBUG)

size_t dark_cstring_lenght(const char* cstring);

Dark_Cbuffer_View dark_cstring_to_cbuffer_view(const char* cstring);
Dark_Cbuffer_View dark_cstring_to_cbuffer_view_terminated(const char* cstring);

Dark_Array_View dark_cstring_to_array_view(const char* cstring);
Dark_Array_View dark_cstring_to_array_view_terminated(const char* cstring);

Dark_Buffer_View dark_cstring_to_buffer_view(const char* cstring);
Dark_Buffer_View dark_cstring_to_buffer_view_terminated(const char* cstring);

int8_t dark_cstring_compare(const char* a, const char* b);

#endif // !defined(___DARK___CSTRING_H)
