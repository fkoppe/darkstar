#include <dark/darkstar.h>

int main()
{
    DARK_DEBUG_MEMORY_INITIALISE;

    Dark_Allocator* os_allocator = dark_os_allocator_new();

    //----------TEST----------
    DARK_TEST("box_struct_size")
    {
        DARK_TEST_GT_U(dark_box_struct_size(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_create_size/_destroy")
    {
        Dark_Box_Struct box_struct;
        Dark_Box* const box = (Dark_Box*)&box_struct;

        dark_box_create_size(box, sizeof(int), 10, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 10);

        dark_box_destroy(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_create")
    {
        Dark_Box_Struct box_struct;
        Dark_Box* const box = (Dark_Box*)&box_struct;

        dark_box_create(box, sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_destroy(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_new_size/_delete")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 10, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 10);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_new")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_at/BOX_AT")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 5, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 5);

        *(int*)dark_box_at(box, 0) = 22;
        *(int*)dark_box_at(box, 1) = 33;
        *(int*)dark_box_at(box, 2) = 44;
        *(int*)dark_box_at(box, 3) = 55;
        *(int*)dark_box_at(box, 4) = 66;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 22);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 33);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 44);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 55);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 4, int), 66);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_front/BOX_FRONT")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 5, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 5);

        *(int*)dark_box_at(box, 0) = 22;
        *(int*)dark_box_at(box, 1) = 33;
        *(int*)dark_box_at(box, 2) = 44;
        *(int*)dark_box_at(box, 3) = 55;
        *(int*)dark_box_at(box, 4) = 66;

        DARK_TEST_EQ_U(DARK_BOX_FRONT(box, int), 22);

        *(int*)dark_box_front(box) = 42;

        DARK_TEST_EQ_U(DARK_BOX_FRONT(box, int), 42);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_back/BOX_BACK")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 5, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 5);

        *(int*)dark_box_at(box, 0) = 22;
        *(int*)dark_box_at(box, 1) = 33;
        *(int*)dark_box_at(box, 2) = 44;
        *(int*)dark_box_at(box, 3) = 55;
        *(int*)dark_box_at(box, 4) = 66;

        DARK_TEST_EQ_U(DARK_BOX_BACK(box, int), 66);

        *(int*)dark_box_back(box) = 42;

        DARK_TEST_EQ_U(DARK_BOX_BACK(box, int), 42);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_data/BOX_DATA")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 5, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 5);

        *(int*)dark_box_at(box, 0) = 22;
        *(int*)dark_box_at(box, 1) = 33;
        *(int*)dark_box_at(box, 2) = 44;
        *(int*)dark_box_at(box, 3) = 55;
        *(int*)dark_box_at(box, 4) = 66;

        DARK_TEST_EQ_U(*DARK_BOX_DATA(box, int), 22);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_emplace")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_emplace(box, 0, 1) = 100;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 100);

        *(int*)dark_box_emplace(box, 0, 1) = 101;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 101);

        *(int*)dark_box_emplace(box, 0, 1) = 99;

        DARK_TEST_EQ_U(DARK_BOX_FRONT(box, int), 99);
        DARK_TEST_EQ_U(DARK_BOX_BACK(box, int), 100);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_emplace_front")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        int* pos_1 = dark_box_emplace_front(box, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 33);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 35);

        int* pos_2 = dark_box_emplace_front(box, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_EQ_U(dark_box_size(box), 6);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 1);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 2);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 3);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 4);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 4, int), 33);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 5, int), 35);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_emplace_back")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        int* pos_1 = dark_box_emplace_back(box, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 33);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 35);

        int* pos_2 = dark_box_emplace_back(box, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_EQ_U(dark_box_size(box), 6);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 33);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 35);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 1);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 2);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 4, int), 3);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 5, int), 4);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_inplace")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace(box, 0) = 705;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 705);

        *(int*)dark_box_inplace(box, 0) = 7;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 7);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 7);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 705);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_inplace_front")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_front(box) = 705;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 705);

        *(int*)dark_box_inplace_front(box) = 1;

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 1);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 705);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_inplace_back")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 705;

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 705);

        *(int*)dark_box_inplace_back(box) = 1;

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 705);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 1);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_push")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_push(box, 0, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);

        dark_box_push(box, 1, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 666666);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 666666);

        DARK_TEST_EQ_U(dark_box_size(box), 4);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_push_front")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_push_front(box, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);

        dark_box_push_front(box, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 666666);

        DARK_TEST_EQ_U(dark_box_size(box), 4);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_push_back")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_push_back(box, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);

        dark_box_push_back(box, 2, buffer);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 666666);

        DARK_TEST_EQ_U(dark_box_size(box), 4);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_insert")
    {
        int a = 333;
        int b  = 666666;

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_insert(box, 0, &a);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);

        dark_box_insert(box, 0, &b);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 333);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_insert_front")
    {
        int a = 333;
        int b  = 666666;

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_insert_front(box, &a);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);

        dark_box_insert_front(box, &b);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 333);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_insert_back")
    {
        int a = 333;
        int b  = 666666;

        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_insert_back(box, &a);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);

        dark_box_insert_back(box, &b);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 333);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 666666);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_pop")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_pop(box, 1, 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 10);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 6);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 999);

        DARK_TEST_EQ_U(dark_box_size(box), 3);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_pop_front")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_pop_front(box, 3);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 6);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 999);

        dark_box_pop_front(box, 2);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_pop_back")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_pop_back(box, 3);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 10);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 20);

        dark_box_pop_back(box, 2);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_erase")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_erase(box, 0);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 20);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 55);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 6);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 3, int), 999);

        dark_box_erase(box, 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 20);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 55);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 2, int), 999);

        dark_box_erase(box, 1);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 20);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 999);

        dark_box_erase(box, 0);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 999);

        dark_box_erase(box, 0);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_erase_front")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_erase_front(box);
        dark_box_erase_front(box);
        dark_box_erase_front(box);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 6);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 999);

        dark_box_erase_front(box);
        dark_box_erase_front(box);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_erase_back")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        *(int*)dark_box_inplace_back(box) = 10;
        *(int*)dark_box_inplace_back(box) = 20;
        *(int*)dark_box_inplace_back(box) = 55;
        *(int*)dark_box_inplace_back(box) = 6;
        *(int*)dark_box_inplace_back(box) = 999;

        dark_box_erase_back(box);
        dark_box_erase_back(box);
        dark_box_erase_back(box);

        DARK_TEST_EQ_U(dark_box_size(box), 2);

        DARK_TEST_EQ_U(DARK_BOX_AT(box, 0, int), 10);
        DARK_TEST_EQ_U(DARK_BOX_AT(box, 1, int), 20);

        dark_box_erase_back(box);
        dark_box_erase_back(box);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_resize")
    {
        Dark_Box* const box = dark_box_new(sizeof(int), os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_resize(box, 10);

        DARK_TEST_EQ_U(dark_box_size(box), 10);

        dark_box_resize(box, 5);

        DARK_TEST_EQ_U(dark_box_size(box), 5);

        dark_box_resize(box, 0);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("box_clear")
    {
        Dark_Box* const box = dark_box_new_size(sizeof(int), 4, os_allocator);

        DARK_TEST_EQ_U(dark_box_size(box), 4);

        dark_box_clear(box);

        DARK_TEST_EQ_U(dark_box_size(box), 0);

        dark_box_delete(box);
    }
    //--------------------------

    dark_test_end();

    dark_os_allocator_delete(os_allocator);

    DARK_DEBUG_MEMORY_SHUTDOWN;

    return DARK_EXIT_SUCCESS;
}
