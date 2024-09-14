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
#include "window_helper.h"

#include <dark/core/core.h>
#include <dark/surface/surface.h>
#include <dark/surface/window_struct.h>

#undef DARK_UNIT
#define DARK_UNIT "window_helper"

Dark_Key_Modifier dark_window_key_modifier(const int modifier_)
{
    switch(modifier_)
    {
    case 0:
        return DARK_KEY_MODIFIER_NONE;
    case GLFW_MOD_SHIFT:
        return DARK_KEY_MODIFIER_SHIFT;
    case GLFW_MOD_CONTROL:
        return DARK_KEY_MODIFIER_CONTROLL;
    case GLFW_MOD_ALT:
        return DARK_KEY_MODIFIER_ALT;
    case GLFW_MOD_SUPER:
        return DARK_KEY_MODIFIER_SUPER;
    case GLFW_MOD_CAPS_LOCK:
        return DARK_KEY_MODIFIER_CAPS_LOCK;
    case GLFW_MOD_NUM_LOCK:
        return DARK_KEY_MODIFIER_NUM_LOCK;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }
}

Dark_Key dark_window_key(const int key_)
{
    switch(key_)
    {
    case GLFW_KEY_SPACE:
        return DARK_KEY_SPACE;
    case GLFW_KEY_APOSTROPHE:
        return DARK_KEY_APOSTROPHE;
    case GLFW_KEY_COMMA:
        return DARK_KEY_COMMA;
    case GLFW_KEY_MINUS:
        return DARK_KEY_MINUS;
    case GLFW_KEY_PERIOD:
        return DARK_KEY_PERIOD;
    case GLFW_KEY_SLASH:
        return DARK_KEY_SLASH;
    case GLFW_KEY_0:
        return DARK_KEY_0;
    case GLFW_KEY_1:
        return DARK_KEY_1;
    case GLFW_KEY_2:
        return DARK_KEY_2;
    case GLFW_KEY_3:
        return DARK_KEY_3;
    case GLFW_KEY_4:
        return DARK_KEY_4;
    case GLFW_KEY_5:
        return DARK_KEY_5;
    case GLFW_KEY_6:
        return DARK_KEY_6;
    case GLFW_KEY_7:
        return DARK_KEY_7;
    case GLFW_KEY_8:
        return DARK_KEY_8;
    case GLFW_KEY_9:
        return DARK_KEY_9;
    case GLFW_KEY_SEMICOLON:
        return DARK_KEY_SEMICOLON;
    case GLFW_KEY_EQUAL:
        return DARK_KEY_EQUAL;
    case GLFW_KEY_A:
        return DARK_KEY_A;
    case GLFW_KEY_B:
        return DARK_KEY_B;
    case GLFW_KEY_C:
        return DARK_KEY_C;
    case GLFW_KEY_D:
        return DARK_KEY_D;
    case GLFW_KEY_E:
        return DARK_KEY_E;
    case GLFW_KEY_F:
        return DARK_KEY_F;
    case GLFW_KEY_G:
        return DARK_KEY_G;
    case GLFW_KEY_H:
        return DARK_KEY_H;
    case GLFW_KEY_I:
        return DARK_KEY_I;
    case GLFW_KEY_J:
        return DARK_KEY_J;
    case GLFW_KEY_K:
        return DARK_KEY_K;
    case GLFW_KEY_L:
        return DARK_KEY_L;
    case GLFW_KEY_M:
        return DARK_KEY_M;
    case GLFW_KEY_N:
        return DARK_KEY_N;
    case GLFW_KEY_O:
        return DARK_KEY_O;
    case GLFW_KEY_P:
        return DARK_KEY_P;
    case GLFW_KEY_Q:
        return DARK_KEY_Q;
    case GLFW_KEY_R:
        return DARK_KEY_R;
    case GLFW_KEY_S:
        return DARK_KEY_S;
    case GLFW_KEY_T:
        return DARK_KEY_T;
    case GLFW_KEY_U:
        return DARK_KEY_U;
    case GLFW_KEY_V:
        return DARK_KEY_V;
    case GLFW_KEY_W:
        return DARK_KEY_W;
    case GLFW_KEY_X:
        return DARK_KEY_X;
    case GLFW_KEY_Y:
        return DARK_KEY_Y;
    case GLFW_KEY_Z:
        return DARK_KEY_Z;
    case GLFW_KEY_LEFT_BRACKET:
        return DARK_KEY_LEFT_BRACKET;
    case GLFW_KEY_BACKSLASH:
        return DARK_KEY_BACKSLASH;
    case GLFW_KEY_RIGHT_BRACKET:
        return DARK_KEY_RIGHT_BRACKET;
    case GLFW_KEY_GRAVE_ACCENT:
        return DARK_KEY_GRAVE_ACCENT;
    case GLFW_KEY_WORLD_1:
        return DARK_KEY_WORLD_1;
    case GLFW_KEY_WORLD_2:
        return DARK_KEY_WORLD_2;
    case GLFW_KEY_ESCAPE:
        return DARK_KEY_ESCAPE;
    case GLFW_KEY_ENTER:
        return DARK_KEY_ENTER;
    case GLFW_KEY_TAB:
        return DARK_KEY_TAB;
    case GLFW_KEY_BACKSPACE:
        return DARK_KEY_BACKSPACE;
    case GLFW_KEY_INSERT:
        return DARK_KEY_INSERT;
    case GLFW_KEY_DELETE:
        return DARK_KEY_DELETE;
    case GLFW_KEY_RIGHT:
        return DARK_KEY_RIGHT;
    case GLFW_KEY_LEFT:
        return DARK_KEY_LEFT;
    case GLFW_KEY_DOWN:
        return DARK_KEY_DOWN;
    case GLFW_KEY_UP:
        return DARK_KEY_UP;
    case GLFW_KEY_PAGE_UP:
        return DARK_KEY_PAGE_UP;
    case GLFW_KEY_PAGE_DOWN:
        return DARK_KEY_PAGE_DOWN;
    case GLFW_KEY_HOME:
        return DARK_KEY_HOME;
    case GLFW_KEY_END:
        return DARK_KEY_END;
    case GLFW_KEY_CAPS_LOCK:
        return DARK_KEY_CAPS_LOCK;
    case GLFW_KEY_SCROLL_LOCK:
        return DARK_KEY_SCROLL_LOCK;
    case GLFW_KEY_NUM_LOCK:
        return DARK_KEY_NUM_LOCK;
    case GLFW_KEY_PRINT_SCREEN:
        return DARK_KEY_PRINT_SCREEN;
    case GLFW_KEY_PAUSE:
        return DARK_KEY_PAUSE;
    case GLFW_KEY_F1:
        return DARK_KEY_F1;
    case GLFW_KEY_F2:
        return DARK_KEY_F2;
    case GLFW_KEY_F3:
        return DARK_KEY_F3;
    case GLFW_KEY_F4:
        return DARK_KEY_F4;
    case GLFW_KEY_F5:
        return DARK_KEY_F5;
    case GLFW_KEY_F6:
        return DARK_KEY_F6;
    case GLFW_KEY_F7:
        return DARK_KEY_F7;
    case GLFW_KEY_F8:
        return DARK_KEY_F8;
    case GLFW_KEY_F9:
        return DARK_KEY_F9;
    case GLFW_KEY_F10:
        return DARK_KEY_F10;
    case GLFW_KEY_F11:
        return DARK_KEY_F11;
    case GLFW_KEY_F12:
        return DARK_KEY_F12;
    case GLFW_KEY_F13:
        return DARK_KEY_F13;
    case GLFW_KEY_F14:
        return DARK_KEY_F14;
    case GLFW_KEY_F15:
        return DARK_KEY_F15;
    case GLFW_KEY_F16:
        return DARK_KEY_F16;
    case GLFW_KEY_F17:
        return DARK_KEY_F17;
    case GLFW_KEY_F18:
        return DARK_KEY_F18;
    case GLFW_KEY_F19:
        return DARK_KEY_F19;
    case GLFW_KEY_F20:
        return DARK_KEY_F20;
    case GLFW_KEY_F21:
        return DARK_KEY_F21;
    case GLFW_KEY_F22:
        return DARK_KEY_F22;
    case GLFW_KEY_F23:
        return DARK_KEY_F23;
    case GLFW_KEY_F24:
        return DARK_KEY_F24;
    case GLFW_KEY_F25:
        return DARK_KEY_F25;
    case GLFW_KEY_KP_0:
        return DARK_KEY_KP_0;
    case GLFW_KEY_KP_1:
        return DARK_KEY_KP_1;
    case GLFW_KEY_KP_2:
        return DARK_KEY_KP_2;
    case GLFW_KEY_KP_3:
        return DARK_KEY_KP_3;
    case GLFW_KEY_KP_4:
        return DARK_KEY_KP_4;
    case GLFW_KEY_KP_5:
        return DARK_KEY_KP_5;
    case GLFW_KEY_KP_6:
        return DARK_KEY_KP_6;
    case GLFW_KEY_KP_7:
        return DARK_KEY_KP_7;
    case GLFW_KEY_KP_8:
        return DARK_KEY_KP_8;
    case GLFW_KEY_KP_9:
        return DARK_KEY_KP_9;
    case GLFW_KEY_KP_DECIMAL:
        return DARK_KEY_KP_DECIMAL;
    case GLFW_KEY_KP_DIVIDE:
        return DARK_KEY_KP_DIVIDE;
    case GLFW_KEY_KP_MULTIPLY:
        return DARK_KEY_KP_MULTIPLY;
    case GLFW_KEY_KP_SUBTRACT:
        return DARK_KEY_KP_SUBTRACT;
    case GLFW_KEY_KP_ADD:
        return DARK_KEY_KP_ADD;
    case GLFW_KEY_KP_ENTER:
        return DARK_KEY_KP_ENTER;
    case GLFW_KEY_KP_EQUAL:
        return DARK_KEY_KP_EQUAL;
    case GLFW_KEY_LEFT_SHIFT:
        return DARK_KEY_LEFT_SHIFT;
    case GLFW_KEY_LEFT_CONTROL:
        return DARK_KEY_LEFT_CONTROL;
    case GLFW_KEY_LEFT_ALT:
        return DARK_KEY_LEFT_ALT;
    case GLFW_KEY_LEFT_SUPER:
        return DARK_KEY_LEFT_SUPER;
    case GLFW_KEY_RIGHT_SHIFT:
        return DARK_KEY_RIGHT_SHIFT;
    case GLFW_KEY_RIGHT_CONTROL:
        return DARK_KEY_RIGHT_CONTROL;
    case GLFW_KEY_RIGHT_ALT:
        return DARK_KEY_RIGHT_ALT;
    case GLFW_KEY_RIGHT_SUPER:
        return DARK_KEY_RIGHT_SUPER;
    case GLFW_KEY_MENU:
        return DARK_KEY_MENU;
    case GLFW_KEY_UNKNOWN:
        return DARK_KEY_UNKNOWN;
    default:
        DARK_ABORT_ERROR(DARK_ERROR_SWITCH);
    }
}
