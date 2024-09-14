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

#if !defined(___DARK___WINDOW_STRUCT_H)
#define ___DARK___WINDOW_STRUCT_H

#include <dark/core/std.h>
#include <dark/log/logger.h>
#include <dark/memory/allocator.h>
#include <dark/surface/event_handler.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct Dark_Window_Data Dark_Window_Data;
struct Dark_Window_Data
{
    size_t id;
    Dark_Event_Handler* event_handler;
};

struct Dark_Window
{
    Dark_Allocator* allocator;
    Dark_Window_Settings settings;
    bool open_is;
    bool visible_is;
    bool fullscreen_is;
    GLFWwindow* instance;
    size_t monitor_width;
    size_t monitor_height;
    Dark_Window_Data data;
    Dark_Logger* logger;
};

#endif // !defined(___DARK___WINDOW_STRUCT_H)
