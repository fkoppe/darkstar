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

#if !defined(___DARK___EVENT_DATA_H)
#define ___DARK___EVENT_DATA_H

#include <dark/core/std.h>

typedef enum Dark_Mouse_Button Dark_Mouse_Button;
enum Dark_Mouse_Button
{
    ___DARK_MOUSE_BUTTON_MIN,
    DARK_MOUSE_BUTTON_UNKNOWN,
    DARK_MOUSE_BUTTON_LEFT,
    DARK_MOUSE_BUTTON_RIGHT,
    DARK_MOUSE_BUTTON_MIDDLE,
    DARK_MOUSE_BUTTON_EXTRA_1,
    DARK_MOUSE_BUTTON_EXTRA_2,
    DARK_MOUSE_BUTTON_EXTRA_3,
    DARK_MOUSE_BUTTON_EXTRA_4,
    DARK_MOUSE_BUTTON_EXTRA_5,
    ___DARK_MOUSE_BUTTON_MAX,
};

typedef enum Dark_Key_Modifier Dark_Key_Modifier;
enum Dark_Key_Modifier
{
    ___DARK_KEY_MODIFIER_MIN,
    DARK_KEY_MODIFIER_NONE      = 0,
    DARK_KEY_MODIFIER_SHIFT     = 1 << 0,
    DARK_KEY_MODIFIER_CONTROLL  = 1 << 1,
    DARK_KEY_MODIFIER_ALT       = 1 << 2,
    DARK_KEY_MODIFIER_SUPER     = 1 << 3,
    DARK_KEY_MODIFIER_CAPS_LOCK = 1 << 4,
    DARK_KEY_MODIFIER_NUM_LOCK  = 1 << 5,
    ___DARK_KEY_MODIFIER_MAX    = 1 << 6,
};

typedef enum Dark_Key Dark_Key;
enum Dark_Key
{
    ___DARK_KEY_MIN,
    DARK_KEY_SPACE,
    DARK_KEY_APOSTROPHE,
    DARK_KEY_COMMA,
    DARK_KEY_MINUS,
    DARK_KEY_PERIOD,
    DARK_KEY_SLASH,
    DARK_KEY_0,
    DARK_KEY_1,
    DARK_KEY_2,
    DARK_KEY_3,
    DARK_KEY_4,
    DARK_KEY_5,
    DARK_KEY_6,
    DARK_KEY_7,
    DARK_KEY_8,
    DARK_KEY_9,
    DARK_KEY_SEMICOLON,
    DARK_KEY_EQUAL,
    DARK_KEY_A,
    DARK_KEY_B,
    DARK_KEY_C,
    DARK_KEY_D,
    DARK_KEY_E,
    DARK_KEY_F,
    DARK_KEY_G,
    DARK_KEY_H,
    DARK_KEY_I,
    DARK_KEY_J,
    DARK_KEY_K,
    DARK_KEY_L,
    DARK_KEY_M,
    DARK_KEY_N,
    DARK_KEY_O,
    DARK_KEY_P,
    DARK_KEY_Q,
    DARK_KEY_R,
    DARK_KEY_S,
    DARK_KEY_T,
    DARK_KEY_U,
    DARK_KEY_V,
    DARK_KEY_W,
    DARK_KEY_X,
    DARK_KEY_Y,
    DARK_KEY_Z,
    DARK_KEY_LEFT_BRACKET,
    DARK_KEY_BACKSLASH,
    DARK_KEY_RIGHT_BRACKET,
    DARK_KEY_GRAVE_ACCENT,
    DARK_KEY_WORLD_1,
    DARK_KEY_WORLD_2,
    DARK_KEY_ESCAPE,
    DARK_KEY_ENTER,
    DARK_KEY_TAB,
    DARK_KEY_BACKSPACE,
    DARK_KEY_INSERT,
    DARK_KEY_DELETE,
    DARK_KEY_RIGHT,
    DARK_KEY_LEFT,
    DARK_KEY_DOWN,
    DARK_KEY_UP,
    DARK_KEY_PAGE_UP,
    DARK_KEY_PAGE_DOWN,
    DARK_KEY_HOME,
    DARK_KEY_END,
    DARK_KEY_CAPS_LOCK,
    DARK_KEY_SCROLL_LOCK,
    DARK_KEY_NUM_LOCK,
    DARK_KEY_PRINT_SCREEN,
    DARK_KEY_PAUSE,
    DARK_KEY_F1,
    DARK_KEY_F2,
    DARK_KEY_F3,
    DARK_KEY_F4,
    DARK_KEY_F5,
    DARK_KEY_F6,
    DARK_KEY_F7,
    DARK_KEY_F8,
    DARK_KEY_F9,
    DARK_KEY_F10,
    DARK_KEY_F11,
    DARK_KEY_F12,
    DARK_KEY_F13,
    DARK_KEY_F14,
    DARK_KEY_F15,
    DARK_KEY_F16,
    DARK_KEY_F17,
    DARK_KEY_F18,
    DARK_KEY_F19,
    DARK_KEY_F20,
    DARK_KEY_F21,
    DARK_KEY_F22,
    DARK_KEY_F23,
    DARK_KEY_F24,
    DARK_KEY_F25,
    DARK_KEY_KP_0,
    DARK_KEY_KP_1,
    DARK_KEY_KP_2,
    DARK_KEY_KP_3,
    DARK_KEY_KP_4,
    DARK_KEY_KP_5,
    DARK_KEY_KP_6,
    DARK_KEY_KP_7,
    DARK_KEY_KP_8,
    DARK_KEY_KP_9,
    DARK_KEY_KP_DECIMAL,
    DARK_KEY_KP_DIVIDE,
    DARK_KEY_KP_MULTIPLY,
    DARK_KEY_KP_SUBTRACT,
    DARK_KEY_KP_ADD,
    DARK_KEY_KP_ENTER,
    DARK_KEY_KP_EQUAL,
    DARK_KEY_LEFT_SHIFT,
    DARK_KEY_LEFT_CONTROL,
    DARK_KEY_LEFT_ALT,
    DARK_KEY_LEFT_SUPER,
    DARK_KEY_RIGHT_SHIFT,
    DARK_KEY_RIGHT_CONTROL,
    DARK_KEY_RIGHT_ALT,
    DARK_KEY_RIGHT_SUPER,
    DARK_KEY_MENU,
    DARK_KEY_UNKNOWN,
    ___DARK_KEY_MAX,
};

typedef enum Dark_Event_Type Dark_Event_Type;
enum Dark_Event_Type
{
    ___DARK_EVENT_TYPE_MIN,
    DARK_EVENT_TYPE_NONE,
    DARK_EVENT_TYPE_WINDOW_MOVED,
    DARK_EVENT_TYPE_WINDOW_RESIZED,
    DARK_EVENT_TYPE_WINDOW_CLOSED,
    DARK_EVENT_TYPE_WINDOW_REFRESHED,
    DARK_EVENT_TYPE_WINDOW_FOCUSED,
    DARK_EVENT_TYPE_WINDOW_UNFOCUSED,
    DARK_EVENT_TYPE_WINDOW_ICONIFIED,
    DARK_EVENT_TYPE_WINDOW_UNICONIFIED,
    DARK_EVENT_TYPE_WINDOW_MAXIMIZED,
    DARK_EVENT_TYPE_WINDOW_UNMAXIMIZED,
    DARK_EVENT_TYPE_WINDOW_SCALE_CHANGED,
    DARK_EVENT_TYPE_WINDOW_FRAMEBUFFER_RESIZED,
    DARK_EVENT_TYPE_BUTTON_PRESSED,
    DARK_EVENT_TYPE_BUTTON_RELEASED,
    DARK_EVENT_TYPE_CURSOR_MOVED,
    DARK_EVENT_TYPE_CURSOR_ENTERED,
    DARK_EVENT_TYPE_CURSOR_LEFT,
    DARK_EVENT_TYPE_SCROLLED,
    DARK_EVENT_TYPE_KEY_PRESSED,
    DARK_EVENT_TYPE_KEY_REPEATED,
    DARK_EVENT_TYPE_KEY_RELEASED,
    DARK_EVENT_TYPE_CODEPOINT_INPUT,
    DARK_EVENT_TYPE_FILE_DROPPED,
    //DARK_EVENT_TYPE_MONITOR_CONNECTED = -1, //TODO
    //DARK_EVENT_TYPE_MONITOR_DISCONNECTED = -1,
    //DARK_EVENT_TYPE_JOYSTICK_CONNECTED = -1,
    //DARK_EVENT_TYPE_JOYSTICK_DISCONNECTED = -1,
    DARK_EVENT_TYPE_UNKNOWN,
    ___DARK_EVENT_TYPE_MAX,
};

typedef struct Dark_Event Dark_Event;
struct Dark_Event
{
    Dark_Event_Type type;
    union
    {
        size_t window;
    } id;
    union
    {
        struct
        {
            size_t x;
            size_t y;
        } position;
        struct
        {
            size_t width;
            size_t height;
        } size;
        struct
        {
            double x;
            double y;
        } scroll;
        struct
        {
            Dark_Key key;
            Dark_Key_Modifier modifier;
            int32_t scancode;
        } keyboard;
        struct
        {
            Dark_Mouse_Button button;
            Dark_Key_Modifier modifier;
        } mouse;
        uint32_t codepoint;
        struct
        {
            const char** paths;
            size_t count;
        } file;
        struct
        {
            float x;
            float y;
        } scale;
    } data;
};

#endif // !defined(___DARK___EVENT_DATA_H)
