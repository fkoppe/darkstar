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

#if !defined(___DARK___WINDOW_H)
#define ___DARK___WINDOW_H

#include <dark/char/cbuffer_view.h>
#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/surface/event_handler.h>

typedef struct Dark_Window Dark_Window;

typedef struct Dark_Window_Settings Dark_Window_Settings;
struct Dark_Window_Settings
{
    Dark_Cbuffer_View title;
    size_t width;
    size_t height;
};

static const Dark_Message DARK_MESSAGE_WINDOW_OPENED_NOT = { NULL, "window not opened", NULL };
static const Dark_Message DARK_MESSAGE_WINDOW_OPENED_ALREADY = { NULL, "window already opened", NULL };

void dark_window_construct(Dark_Allocator* allocator, Dark_Window* window, size_t id, Dark_Window_Settings settings, Dark_Event_Handler* event_handler, Dark_Logger* logger);
void dark_window_destruct(Dark_Window* window);

Dark_Window* dark_window_new(Dark_Allocator* allocator, size_t id, Dark_Window_Settings settings, Dark_Event_Handler* event_handler, Dark_Logger* logger);
void dark_window_delete(Dark_Window* window);

Dark_Window_Settings dark_window_settings_get(Dark_Window* window);
void dark_window_settings_set(Dark_Window* window, Dark_Window_Settings settings);

void dark_window_update(Dark_Window* window);

void dark_window_open_windowed(Dark_Window* window, bool visible_is);
void dark_window_open_fullscreen(Dark_Window* window);
bool dark_window_fullscreen_is(Dark_Window* window);

void dark_window_windowed(Dark_Window* window, bool visible_is);
void dark_window_fullscreen(Dark_Window* window);

void dark_window_close(Dark_Window* window);
bool dark_window_open_is(Dark_Window* window);

void dark_window_resize(Dark_Window* window, size_t width, size_t height);
void dark_window_extend(Dark_Window* window, size_t* width, size_t* height);
void dark_window_framebuffer_extend(Dark_Window* window, size_t* width, size_t* height);

void dark_window_move(Dark_Window* window, size_t x, size_t y);
void dark_window_position(Dark_Window* window);

void dark_window_show(Dark_Window* window);
void dark_window_hide(Dark_Window* window);
bool dark_window_visible_is(Dark_Window* window);

void dark_window_title_set(Dark_Window* window, Dark_Cbuffer_View title);

size_t dark_window_struct_byte(void);

#endif // !defined(___DARK___WINDOW_H)
