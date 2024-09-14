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

#include <dark/char/char.h>
#include <dark/core/core.h>>
#include <dark/log/logger.h>
#include <dark/memory/memory.h>
#include <dark/surface/surface.h>
#include <dark/surface/window_struct.h>

#include <limits.h>

#undef DARK_UNIT
#define DARK_UNIT "window"

void dark_window_construct(Dark_Allocator* const allocator_, Dark_Window* const window_, const size_t id_, Dark_Window_Settings const settings_, Dark_Event_Handler* const event_handler_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //id_
    DARK_ASSERT(settings_.title.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);
    //logger_

    window_->allocator = allocator_;
    window_->settings = settings_;
    window_->open_is = false;
    window_->visible_is = false;
    window_->fullscreen_is = false;
    window_->instance = NULL;
    window_->data.id = id_;
    window_->data.event_handler = event_handler_;
    window_->logger = logger_;

    const bool b = glfwInit();
    DARK_ASSERT_CSTRING(b, DARK_ERROR_GLFW, "failed to initialise");
}

void dark_window_destruct(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    glfwTerminate();
}

Dark_Window* dark_window_new(Dark_Allocator* const allocator_, const size_t id_, Dark_Window_Settings const settings_, Dark_Event_Handler* const event_handler_, Dark_Logger* const logger_)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    //id_
    DARK_ASSERT(settings_.title.size > 0, DARK_ERROR_ZERO);
    DARK_ASSERT(NULL != event_handler_, DARK_ERROR_NULL);
    //logger_

    Dark_Window* const window = dark_malloc(allocator_, sizeof(*window));
    DARK_ASSERT(NULL != window, DARK_ERROR_ALLOCATION);

    dark_window_construct(allocator_, window, id_, settings_, event_handler_, logger_);

    return window;
}

void dark_window_delete(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    dark_window_destruct(window_);

    dark_free(window_->allocator, window_, sizeof(*window_));
}

Dark_Window_Settings dark_window_settings_get(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    return window_->settings;
}

void dark_window_settings_set(Dark_Window* const window_, Dark_Window_Settings const settings_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DARK_ASSERT(settings_.title.size > 0, DARK_ERROR_ZERO);

    bool resized = false;

    if(window_->settings.height != settings_.height || window_->settings.width != settings_.width)
    {
        resized = true;
    }

    window_->settings = settings_;

    if(resized)
    {
        DARK_UNIMPLEMENTED;
    }
}

void dark_window_update(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    glfwPollEvents();
}

void dark_window_open_windowed(Dark_Window* const window_, bool const visible_is_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //visible_is_

    DARK_ASSERT_MESSAGE(!window_->open_is, DARK_ERROR_STATE, DARK_MESSAGE_WINDOW_OPENED_ALREADY);

    //TODO
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    window_->instance = glfwCreateWindow(window_->settings.width, window_->settings.height, window_->settings.title.data, NULL, NULL);
    DARK_ASSERT_CSTRING(NULL != window_->instance, DARK_ERROR_GLFW, "failed to open window");

    if (visible_is_)
    {
        glfwShowWindow(window_->instance);
    }
    else
    {
        glfwHideWindow(window_->instance);
    }

    glfwSetWindowUserPointer(window_->instance, &window_->data);

    glfwSetWindowPosCallback(window_->instance, dark_window_callback_window_move);
    glfwSetWindowSizeCallback(window_->instance, dark_window_callback_window_resize);
    glfwSetWindowCloseCallback(window_->instance, dark_window_callback_window_close);
    glfwSetWindowRefreshCallback(window_->instance, dark_window_callback_window_refresh);
    glfwSetWindowFocusCallback(window_->instance, dark_window_callback_window_focus);
    glfwSetWindowIconifyCallback(window_->instance, dark_window_callback_window_iconify);
    glfwSetWindowMaximizeCallback(window_->instance, dark_window_callback_window_maximize);
    glfwSetWindowContentScaleCallback(window_->instance, dark_window_callback_window_content_scale);
    glfwSetFramebufferSizeCallback(window_->instance, dark_window_callback_framebuffer_size);
    glfwSetMouseButtonCallback(window_->instance, dark_window_callback_mouse_button);
    glfwSetCursorPosCallback(window_->instance, dark_window_callback_cursor_move);
    glfwSetCursorEnterCallback(window_->instance, dark_window_callback_cursor_enter);
    glfwSetScrollCallback(window_->instance, dark_window_callback_scroll);
    glfwSetKeyCallback(window_->instance, dark_window_callback_key);
    glfwSetCharCallback(window_->instance, dark_window_callback_char);
    glfwSetDropCallback(window_->instance, dark_window_callback_file_drop);

    window_->open_is = true;
    window_->visible_is = visible_is_;
    window_->fullscreen_is = false;

    DARK_IDLOG_CSTRING(window_->logger, window_->data.id, DARK_LOG_LEVEL_NOTE, "open windowed");
}

void dark_window_open_fullscreen(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(!window_->open_is, DARK_ERROR_STATE, DARK_MESSAGE_WINDOW_OPENED_ALREADY);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    GLFWmonitor* const primary = glfwGetPrimaryMonitor();
    DARK_ASSERT_CSTRING(NULL != primary, DARK_ERROR_RUNTIME, "no monitor connected");

    window_->instance = glfwCreateWindow(window_->settings.width, window_->settings.height, window_->settings.title.data, primary, NULL);
    DARK_ASSERT_CSTRING(NULL != window_->instance, DARK_ERROR_GLFW, "failed to open window");

    glfwSetWindowUserPointer(window_->instance, &window_->data);

    glfwSetWindowPosCallback(window_->instance, dark_window_callback_window_move);
    glfwSetWindowSizeCallback(window_->instance, dark_window_callback_window_resize);
    glfwSetWindowCloseCallback(window_->instance, dark_window_callback_window_close);
    glfwSetWindowRefreshCallback(window_->instance, dark_window_callback_window_refresh);
    glfwSetWindowFocusCallback(window_->instance, dark_window_callback_window_focus);
    glfwSetWindowIconifyCallback(window_->instance, dark_window_callback_window_iconify);
    glfwSetWindowMaximizeCallback(window_->instance, dark_window_callback_window_maximize);
    glfwSetWindowContentScaleCallback(window_->instance, dark_window_callback_window_content_scale);
    glfwSetFramebufferSizeCallback(window_->instance, dark_window_callback_framebuffer_size);
    glfwSetMouseButtonCallback(window_->instance, dark_window_callback_mouse_button);
    glfwSetCursorPosCallback(window_->instance, dark_window_callback_cursor_move);
    glfwSetCursorEnterCallback(window_->instance, dark_window_callback_cursor_enter);
    glfwSetScrollCallback(window_->instance, dark_window_callback_scroll);
    glfwSetKeyCallback(window_->instance, dark_window_callback_key);
    glfwSetCharCallback(window_->instance, dark_window_callback_char);
    glfwSetDropCallback(window_->instance, dark_window_callback_file_drop);

    window_->open_is = true;
    window_->visible_is = true;
    window_->fullscreen_is = true;

    DARK_IDLOG_CSTRING(window_->logger, window_->data.id, DARK_LOG_LEVEL_NOTE, "open fullscreen");
}

bool dark_window_fullscreen_is(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    return window_->fullscreen_is;
}

void dark_window_windowed(Dark_Window* const window_, bool const visible_is_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DARK_MESSAGE_WINDOW_OPENED_NOT);
    DARK_ASSERT_CSTRING(window_->fullscreen_is, DARK_ERROR_STATE, "is already windowed");

    glfwRestoreWindow(window_->instance);
    glfwSetWindowMonitor(window_->instance, NULL, 0, 0, window_->settings.width, window_->settings.height, 0);

    DARK_IDLOG_CSTRING(window_->logger, window_->data.id, DARK_LOG_LEVEL_NOTE, "windowed");

    window_->visible_is = visible_is_;
    window_->fullscreen_is = false;
}

void dark_window_fullscreen(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT_MESSAGE(window_->open_is, DARK_ERROR_STATE, DARK_MESSAGE_WINDOW_OPENED_NOT);
    DARK_ASSERT_CSTRING(!window_->fullscreen_is, DARK_ERROR_STATE, "is already fullscreened");

    GLFWmonitor* const primary = glfwGetPrimaryMonitor();
    DARK_ASSERT_CSTRING(NULL != primary, DARK_ERROR_RUNTIME, "no monitor connected");

    const GLFWvidmode* const mode = glfwGetVideoMode(primary);

    glfwSetWindowMonitor(window_->instance, primary, 0, 0,  window_->settings.width, window_->settings.height, mode->refreshRate);

    window_->visible_is = true;
    window_->fullscreen_is = true;

    DARK_IDLOG_CSTRING(window_->logger, window_->data.id, DARK_LOG_LEVEL_NOTE, "fullscreen");
}

void dark_window_close(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    glfwDestroyWindow(window_->instance);

    DARK_IDLOG_CSTRING(window_->logger, window_->data.id, DARK_LOG_LEVEL_NOTE, "close");

    window_->open_is = false;
}

bool dark_window_open_is(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    return window_->open_is;
}

void dark_window_resize(Dark_Window* const window_, const size_t width_, const size_t height_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    //width_
    //height_

    glfwSetWindowSize(window_->instance, DARK_MIN(width_, INT_MAX), DARK_MIN(height_, INT_MAX));
}

void dark_window_extend(Dark_Window* const window_, size_t* const width_, size_t* const height_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_window_framebuffer_extend(Dark_Window* const window_, size_t* const width_, size_t* const height_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_window_move(Dark_Window* const window_, size_t const x_, size_t const y_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_window_position(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_UNIMPLEMENTED;
}

void dark_window_show(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(!window_->fullscreen_is, DARK_ERROR_STATE);

    glfwShowWindow(window_->instance);
}

void dark_window_hide(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    DARK_ASSERT(!window_->fullscreen_is, DARK_ERROR_STATE);

    glfwHideWindow(window_->instance);
}

bool dark_window_visible_is(Dark_Window* const window_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);

    return window_->visible_is;
}

void dark_window_title_set(Dark_Window* const window_, Dark_Cbuffer_View const title_)
{
    DARK_ASSERT(NULL != window_, DARK_ERROR_NULL);
    DARK_ASSERT(title_.size > 0, DARK_ERROR_ZERO);

    window_->settings.title = title_;

    if(window_->open_is)
    {
        glfwSetWindowTitle(window_->instance, title_.data);
    }
}

size_t dark_window_struct_byte(void)
{
    return sizeof(Dark_Window);
}
