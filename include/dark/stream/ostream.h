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
#include <dark/stream/stream_data.h>

void* dark_ostream_new(Dark_Stream_Setting settings);
void dark_ostream_delete(void* ostream);

void dark_ostream_write(void* ostream, size_t byte, const void* data);

void dark_ostream_flush(void* ostream);

void dark_ostream_add_file(void* ostream, const char* path, void* mutex);
void dark_ostream_add_stdout(void* ostream, void* mutex);
void dark_ostream_add_sterr(void* ostream, void* mutex);

#endif // !defined(___DARK___OSTREAM_H)
