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

#if !defined(___DARK___BOX_H)
#define ___DARK___BOX_H

#include <dark/core/essential.h>
#include <dark/memory/allocator.h>

#define DARK_BOX_AT(box, index, type) \
(*(type*)dark_box_at((box), (index)))

#define DARK_BOX_FRONT(box, type) \
(*(type*)dark_box_front((box)))

#define DARK_BOX_BACK(box, type) \
(*(type*)dark_box_back((box)))

#define DARK_BOX_DATA(box, type) \
((type*)dark_box_data((box)))

typedef struct Dark_Box Dark_Box;

typedef struct Dark_Box_Struct
{
    Dark_Allocator* allocator;
    size_t element_size;
    size_t size;
    char* data;
} Dark_Box_Struct;

size_t dark_box_struct_size(void);

void dark_box_construct_size(Dark_Box* box, size_t element_size, size_t size, Dark_Allocator* allocator);
void dark_box_construct(Dark_Box* box, size_t element_size, Dark_Allocator* allocator);
void dark_box_destruct(Dark_Box* box);

Dark_Box* dark_box_new_size(size_t element_size, size_t size, Dark_Allocator* allocator, Dark_Allocator* struct_allocator);
Dark_Box* dark_box_new(size_t element_size, Dark_Allocator* allocator, Dark_Allocator* struct_allocator);
void dark_box_delete(Dark_Box* box, Dark_Allocator* struct_allocator);

void* dark_box_at(Dark_Box* box, size_t index);
void* dark_box_front(Dark_Box* box);
void* dark_box_back(Dark_Box* box);
void* dark_box_data(Dark_Box* box);

size_t dark_box_size(Dark_Box* box);
void dark_box_resize(Dark_Box* box, size_t size);
void dark_box_clear(Dark_Box* box);
size_t dark_box_element_size(Dark_Box* box);

void* dark_box_emplace(Dark_Box* box, size_t index, size_t count);
void* dark_box_emplace_front(Dark_Box* box, size_t count);
void* dark_box_emplace_back(Dark_Box* box, size_t count);
void* dark_box_inplace(Dark_Box* box, size_t index);
void* dark_box_inplace_front(Dark_Box* box);
void* dark_box_inplace_back(Dark_Box* box);

void dark_box_push(Dark_Box* box, size_t index, size_t count, const void* source);
void dark_box_push_front(Dark_Box* box, size_t count, const void* source);
void dark_box_push_back(Dark_Box* box, size_t count, const void* source);
void dark_box_insert(Dark_Box* box, size_t index, const void* element);
void dark_box_insert_front(Dark_Box* box, const void* element);
void dark_box_insert_back(Dark_Box* box, const void* element);

void dark_box_pop(Dark_Box* box, size_t index, size_t count);
void dark_box_pop_front(Dark_Box* box, size_t count);
void dark_box_pop_back(Dark_Box* box, size_t count);
void dark_box_erase(Dark_Box* box, size_t index);
void dark_box_erase_front(Dark_Box* box);
void dark_box_erase_back(Dark_Box* box);

void* dark_box_desplace(Dark_Box* box, size_t index, size_t count);
void* dark_box_displace(Dark_Box* box, size_t index);

void dark_box_replace(Dark_Box* box, size_t index, size_t count, const void* source);
void dark_box_resert(Dark_Box* box, size_t index, const void* element);

void dark_box_remove(Dark_Box* box, size_t index, size_t count);
void dark_box_cut(Dark_Box* box, size_t index);

#endif // !defined(___DARK___BOX_H)
