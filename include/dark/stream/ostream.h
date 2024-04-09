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

#if !defined(___DARK___OSTREAM_H)
#define ___DARK___OSTREAM_H

#include <dark/core/essential.h>
#include <dark/platform/mutex.h>
#include <dark/stream/stream_data.h>

typedef struct Dark_Ostream Dark_Ostream;

size_t dark_ostream_struct_size(void);

Dark_Ostream* dark_ostream_new(Dark_Stream_Setting settings);
void dark_ostream_delete(Dark_Ostream* ostream);

void dark_ostream_write(Dark_Ostream* ostream, size_t byte, const void* data);

void dark_ostream_flush(Dark_Ostream* ostream);
void dark_ostream_flush_unbuffered(Dark_Ostream* ostream, size_t byte, const void* data);

void dark_ostream_add_file(Dark_Ostream* ostream, const char* path, Dark_Mutex* mutex);
void dark_ostream_add_stdout(Dark_Ostream* ostream, Dark_Mutex* mutex);
void dark_ostream_add_sterr(Dark_Ostream* ostream, Dark_Mutex* mutex);

#endif // !defined(___DARK___OSTREAM_H)
