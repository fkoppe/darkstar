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

#include "surface_module.h"
#include "window_callback.h"
#include "window_helper.h"

#include <dark/core/core.h>
#include <dark/math/math.h>
#include <dark/surface/surface.h>
#include <dark/surface/window_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "window_callback"

void dark_window_callback_window_move(GLFWwindow* const window_, const int x_, const int y_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_MOVED;
    event.id.window = data->id;
    event.data.position.x = dark_icast_zu(x_);
    event.data.position.y = dark_icast_zu(y_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_resize(GLFWwindow* const window_, const int width_, const int height_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_RESIZED;
    event.id.window = data->id;
    event.data.size.width = dark_icast_zu(width_);
    event.data.size.height = dark_icast_zu(height_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_close(GLFWwindow* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_CLOSED;
    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_refresh(GLFWwindow* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_REFRESHED;
    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_focus(GLFWwindow* const window_, const int focused_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;

    if(GLFW_TRUE == focused_)
    {
        event.type = DARK_EVENT_TYPE_WINDOW_FOCUSED;
    }
    else
    {
        event.type = DARK_EVENT_TYPE_WINDOW_UNFOCUSED;
    }

    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_iconify(GLFWwindow* const window_, const int iconified_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;

    if(GLFW_TRUE == iconified_)
    {
        event.type = DARK_EVENT_TYPE_WINDOW_ICONIFIED;
    }
    else
    {
        event.type = DARK_EVENT_TYPE_WINDOW_UNICONIFIED;
    }

    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_maximize(GLFWwindow* const window_, const int maximized_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;

    if(GLFW_TRUE == maximized_)
    {
        event.type = DARK_EVENT_TYPE_WINDOW_MAXIMIZED;
    }
    else
    {
        event.type = DARK_EVENT_TYPE_WINDOW_UNMAXIMIZED;
    }

    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_window_content_scale(GLFWwindow* const window_, const float xscale_, const float yscale_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_SCALE_CHANGED;
    event.id.window = data->id;
    event.data.scale.x = xscale_;
    event.data.scale.y = yscale_;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_framebuffer_size(GLFWwindow* const window_, const int width_, const int height_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_WINDOW_FRAMEBUFFER_RESIZED;
    event.id.window = data->id;
    event.data.size.width = dark_icast_zu(width_);
    event.data.size.height = dark_icast_zu(height_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_mouse_button(GLFWwindow* const window_, const int button_, const int action_, const int mods_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    //TODO
}

void dark_window_callback_cursor_move(GLFWwindow* const window_, const double x_, const double y_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_CURSOR_MOVED;
    event.id.window = data->id;
    event.data.position.x = dark_icast_zu(x_);
    event.data.position.y = dark_icast_zu(y_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_cursor_enter(GLFWwindow* const window_, const int entered_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Event event;

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    if(GLFW_TRUE == entered_)
    {
        event.type = DARK_EVENT_TYPE_CURSOR_ENTERED;
    }
    else
    {
        event.type = DARK_EVENT_TYPE_CURSOR_LEFT;
    }

    event.id.window = data->id;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_scroll(GLFWwindow* const window_, const double x_, const double y_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_SCROLLED;
    event.id.window = data->id;
    event.data.scroll.x = x_;
    event.data.scroll.y = y_;

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_key(GLFWwindow* const window_, const int key_, const int scancode_, const int action_, const int mods_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;

    switch(action_)
    {
    case GLFW_PRESS:
        event.type = DARK_EVENT_TYPE_KEY_PRESSED;
        break;
    case GLFW_REPEAT:
        event.type = DARK_EVENT_TYPE_KEY_REPEATED;
        break;
    case GLFW_RELEASE:
        event.type = DARK_EVENT_TYPE_KEY_RELEASED;
        break;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }

    event.id.window = data->id;
    event.data.keyboard.key = dark_window_key(key_);
    event.data.keyboard.modifier = dark_window_key_modifier(mods_);
    event.data.keyboard.scancode = dark_icast_i32(scancode_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_char(GLFWwindow* const window_, const unsigned int codepoint_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_CODEPOINT_INPUT,
    event.id.window = data->id;
    event.data.codepoint = dark_ucast_u32(codepoint_);

    dark_event_handler_insert(data->event_handler, event);
}

void dark_window_callback_file_drop(GLFWwindow* const window_, const int count_, const char** const paths_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DARK_ASSERT(count_ > 0, DARK_ERROR_GLFW);

    Dark_Window_Data* const data = glfwGetWindowUserPointer(window_);

    Dark_Event event;
    event.type = DARK_EVENT_TYPE_FILE_DROPPED,
    event.id.window = data->id,
    event.data.file.count = dark_icast_zu(count_),
    event.data.file.paths = paths_,

    dark_event_handler_insert(data->event_handler, event);
}
