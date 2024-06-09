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

#if !defined(___DARK___MESSAGE_H)
#define ___DARK___MESSAGE_H

#include <dark/core/std.h>
#include <dark/core/so.h>

#define DARK_MESSAGE_DEPTH_MAX 4

typedef struct Dark_Message Dark_Message;
struct Dark_Message
{
    const Dark_Message* parent;
    const char* data;
    bool prefix_is;
};

static const Dark_Message DARK_MESSAGE_NONE = { NULL, NULL, false };

void dark_message_print(Dark_So so, Dark_Message message);

#endif // !defined(___DARK___MESSAGE_H)
