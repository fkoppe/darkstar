#include <dark/darkstar.h>

int main()
{
    #if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
    #endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("array_struct_size")
    {
        DARK_TEST_GT_U(dark_array_struct_size(), 0);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("array_create_size/_capacity/_size/_destroy")
    {
        Dark_Array_Struct array_struct;
        Dark_Array* const array = (Dark_Array*)&array_struct;

        dark_array_create_size(array, sizeof(int), 10, 10);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 10);

        dark_array_destroy(array);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("array_create_capacity")
    {
        Dark_Array_Struct array_struct;
        Dark_Array* const array = (Dark_Array*)&array_struct;

        dark_array_create_capacity(array, sizeof(int), 10);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_destroy(array);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("array_create")
    {
        Dark_Array_Struct array_struct;
        Dark_Array* const array = (Dark_Array*)&array_struct;

        dark_array_create(array, sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_destroy(array);
    }
    //--------------------------

    //----------TEST#5----------
    DARK_TEST("array_new_size/_delete")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 10, 10);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 10);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#6----------
    DARK_TEST("array_new_capacity")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 10);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#7----------
    DARK_TEST("array_new")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#8----------
    DARK_TEST("array_at/ARRAY_AT")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 5);

        *(int*)dark_array_at(array, 0) = 22;
        *(int*)dark_array_at(array, 1) = 33;
        *(int*)dark_array_at(array, 2) = 44;
        *(int*)dark_array_at(array, 3) = 55;
        *(int*)dark_array_at(array, 4) = 66;

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 22);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 33);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 44);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 55);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 4, int), 66);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#9----------
    DARK_TEST("array_front/ARRAY_FRONT")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 5);

        *(int*)dark_array_at(array, 0) = 22;
        *(int*)dark_array_at(array, 1) = 33;
        *(int*)dark_array_at(array, 2) = 44;
        *(int*)dark_array_at(array, 3) = 55;
        *(int*)dark_array_at(array, 4) = 66;

        DARK_TEST_EQ_U(DARK_ARRAY_FRONT(array, int), 22);

        *(int*)dark_array_front(array) = 42;

        DARK_TEST_EQ_U(DARK_ARRAY_FRONT(array, int), 42);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#10----------
    DARK_TEST("array_back/ARRAY_BACK")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 5);

        *(int*)dark_array_at(array, 0) = 22;
        *(int*)dark_array_at(array, 1) = 33;
        *(int*)dark_array_at(array, 2) = 44;
        *(int*)dark_array_at(array, 3) = 55;
        *(int*)dark_array_at(array, 4) = 66;

        DARK_TEST_EQ_U(DARK_ARRAY_BACK(array, int), 66);

        *(int*)dark_array_back(array) = 42;

        DARK_TEST_EQ_U(DARK_ARRAY_BACK(array, int), 42);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#11----------
    DARK_TEST("array_data/ARRAY_DATA")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 5);

        *(int*)dark_array_at(array, 0) = 22;
        *(int*)dark_array_at(array, 1) = 33;
        *(int*)dark_array_at(array, 2) = 44;
        *(int*)dark_array_at(array, 3) = 55;
        *(int*)dark_array_at(array, 4) = 66;

        DARK_TEST_EQ_U(*DARK_ARRAY_DATA(array, int), 22);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#12----------
    DARK_TEST("array_emplace")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace(array, 0, 1) = 100;

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 100);

        *(int*)dark_array_emplace(array, 0, 1) = 101;

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 101);

        *(int*)dark_array_emplace(array, 0, 1) = 99;

        DARK_TEST_EQ_U(DARK_ARRAY_FRONT(array, int), 99);
        DARK_TEST_EQ_U(DARK_ARRAY_BACK(array, int), 100);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#13----------
    DARK_TEST("array_emplace_front_c")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        int* pos_1 = dark_array_emplace_front_c(array, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 33);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 35);

        int* pos_2 = dark_array_emplace_front_c(array, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_array_capacity(array), 6);
        DARK_TEST_EQ_U(dark_array_size(array), 6);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 1);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 2);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 3);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 4);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 4, int), 33);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 5, int), 35);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#14----------
    DARK_TEST("array_emplace_front")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_front(array) = 705;

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 705);

        *(int*)dark_array_emplace_front(array) = 1;

        DARK_TEST_GE_U(dark_array_capacity(array), 2);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 1);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 705);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#15----------
    DARK_TEST("array_emplace_back_c")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        int* pos_1 = dark_array_emplace_back_c(array, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 33);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 35);

        int* pos_2 = dark_array_emplace_back_c(array, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_array_capacity(array), 6);
        DARK_TEST_EQ_U(dark_array_size(array), 6);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 33);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 35);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 1);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 2);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 4, int), 3);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 5, int), 4);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#16----------
    DARK_TEST("array_emplace_back")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 705;

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 705);

        *(int*)dark_array_emplace_back(array) = 1;

        DARK_TEST_GE_U(dark_array_capacity(array), 2);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 705);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 1);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#17----------
    DARK_TEST("array_push")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_push(array, 0, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);

        dark_array_push(array, 1, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 666666);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 666666);

        DARK_TEST_GE_U(dark_array_capacity(array), 4);
        DARK_TEST_EQ_U(dark_array_size(array), 4);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#18----------
    DARK_TEST("array_insert")
    {
        int a = 333;
        int b  = 666666;

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_insert(array, 0, &a);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);

        dark_array_insert(array, 0, &b);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 333);

        DARK_TEST_GE_U(dark_array_capacity(array), 2);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#19----------
    DARK_TEST("array_push_front_c")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_push_front_c(array, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);

        dark_array_push_front_c(array, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 666666);

        DARK_TEST_GE_U(dark_array_capacity(array), 4);
        DARK_TEST_EQ_U(dark_array_size(array), 4);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#20----------
    DARK_TEST("array_push_front")
    {
        int a = 333;
        int b  = 666666;

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_push_front(array, &a);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);

        dark_array_push_front(array, &b);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 333);

        DARK_TEST_GE_U(dark_array_capacity(array), 2);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#21----------
    DARK_TEST("array_push_back_c")
    {
        int buffer[2] = { 333, 666666 };

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_push_back_c(array, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);

        dark_array_push_back_c(array, 2, buffer);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 666666);

        DARK_TEST_GE_U(dark_array_capacity(array), 4);
        DARK_TEST_EQ_U(dark_array_size(array), 4);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#22----------
    DARK_TEST("array_push_back")
    {
        int a = 333;
        int b  = 666666;

        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_push_back(array, &a);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);

        dark_array_push_back(array, &b);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 333);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 666666);

        DARK_TEST_GE_U(dark_array_capacity(array), 2);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#23----------
    DARK_TEST("array_pop")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_pop(array, 1, 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 10);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 6);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 999);

        DARK_TEST_GE_U(dark_array_capacity(array), 3);
        DARK_TEST_EQ_U(dark_array_size(array), 3);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#24----------
    DARK_TEST("array_erase")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_erase(array, 0);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 20);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 55);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 6);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 3, int), 999);

        dark_array_erase(array, 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 20);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 55);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 2, int), 999);

        dark_array_erase(array, 1);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 20);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 999);

        dark_array_erase(array, 0);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 999);

        dark_array_erase(array, 0);

        DARK_TEST_GE_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#25----------
    DARK_TEST("array_pop_front_c")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_pop_front_c(array, 3);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 6);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 999);

        dark_array_pop_front_c(array, 2);

        DARK_TEST_GE_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#26----------
    DARK_TEST("array_pop_front")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_pop_front(array);
        dark_array_pop_front(array);
        dark_array_pop_front(array);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 6);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 999);

        dark_array_pop_front(array);
        dark_array_pop_front(array);

        DARK_TEST_GE_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#27----------
    DARK_TEST("array_pop_back_c")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_pop_back_c(array, 3);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 10);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 20);

        dark_array_pop_front_c(array, 2);

        DARK_TEST_GE_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#28----------
    DARK_TEST("array_pop_back")
    {
        Dark_Array* const array = dark_array_new_capacity(sizeof(int), 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        *(int*)dark_array_emplace_back(array) = 10;
        *(int*)dark_array_emplace_back(array) = 20;
        *(int*)dark_array_emplace_back(array) = 55;
        *(int*)dark_array_emplace_back(array) = 6;
        *(int*)dark_array_emplace_back(array) = 999;

        dark_array_pop_back(array);
        dark_array_pop_back(array);
        dark_array_pop_back(array);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 2);

        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 0, int), 10);
        DARK_TEST_EQ_U(DARK_ARRAY_AT(array, 1, int), 20);

        dark_array_pop_back(array);
        dark_array_pop_back(array);

        DARK_TEST_GE_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#29----------
    DARK_TEST("array_reserve_exact")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_reserve_exact(array, 100);

        DARK_TEST_EQ_U(dark_array_capacity(array), 100);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_reserve_exact(array, 0);

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_reserve_exact(array, 101);

        DARK_TEST_EQ_U(dark_array_capacity(array), 101);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#30----------
    DARK_TEST("array_shrink_to_fit")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_reserve_exact(array, 100);
        dark_array_shrink_to_fit(array);

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#31----------
    DARK_TEST("array_resize")
    {
        Dark_Array* const array = dark_array_new(sizeof(int));

        DARK_TEST_EQ_U(dark_array_capacity(array), 0);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_resize(array, 10);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 10);

        dark_array_resize(array, 5);

        DARK_TEST_EQ_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 5);

        dark_array_resize(array, 0);

        DARK_TEST_GE_U(dark_array_capacity(array), 10);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    //----------TEST#32----------
    DARK_TEST("array_clear")
    {
        Dark_Array* const array = dark_array_new_size(sizeof(int), 5, 4);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 4);

        dark_array_clear(array);

        DARK_TEST_EQ_U(dark_array_capacity(array), 5);
        DARK_TEST_EQ_U(dark_array_size(array), 0);

        dark_array_delete(array);
    }
    //--------------------------

    dark_test_end();

    #if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
    #endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
