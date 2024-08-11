#include <dark/darkstar.h>
#include <dark/darktest.h>

void foreach_helper(int32_t* element, int32_t* context)
{
    *context += *element;
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("vector_new_size/_delete/_capacity/_size")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 10, 10);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 10);
        DARK_TEST_EQ_U(dark_vector_size(vector), 10);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_new_capacity")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 10);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 10);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_new")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_at/VECTOR_AT")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        *(int*)dark_vector_at(vector, 0) = 22;
        *(int*)dark_vector_at(vector, 1) = 33;
        *(int*)dark_vector_at(vector, 2) = 44;
        *(int*)dark_vector_at(vector, 3) = 55;
        *(int*)dark_vector_at(vector, 4) = 66;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 22);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 33);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 44);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 55);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 4, int), 66);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_front/VECTOR_FRONT")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        *(int*)dark_vector_at(vector, 0) = 22;
        *(int*)dark_vector_at(vector, 1) = 33;
        *(int*)dark_vector_at(vector, 2) = 44;
        *(int*)dark_vector_at(vector, 3) = 55;
        *(int*)dark_vector_at(vector, 4) = 66;

        DARK_TEST_EQ_U(DARK_VECTOR_FRONT(vector, int), 22);

        *(int*)dark_vector_front(vector) = 42;

        DARK_TEST_EQ_U(DARK_VECTOR_FRONT(vector, int), 42);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_back/VECTOR_BACK")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        *(int*)dark_vector_at(vector, 0) = 22;
        *(int*)dark_vector_at(vector, 1) = 33;
        *(int*)dark_vector_at(vector, 2) = 44;
        *(int*)dark_vector_at(vector, 3) = 55;
        *(int*)dark_vector_at(vector, 4) = 66;

        DARK_TEST_EQ_U(DARK_VECTOR_BACK(vector, int), 66);

        *(int*)dark_vector_back(vector) = 42;

        DARK_TEST_EQ_U(DARK_VECTOR_BACK(vector, int), 42);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------ra
    DARK_TEST("vector_data/VECTOR_DATA")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        *(int*)dark_vector_at(vector, 0) = 22;
        *(int*)dark_vector_at(vector, 1) = 33;
        *(int*)dark_vector_at(vector, 2) = 44;
        *(int*)dark_vector_at(vector, 3) = 55;
        *(int*)dark_vector_at(vector, 4) = 66;

        DARK_TEST_EQ_U(*DARK_VECTOR_DATA(vector, int), 22);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_array")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        const Dark_Array array = dark_vector_array(vector);

        DARK_TEST_EQ_U(array.size, 5);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_array_view")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        const Dark_Array_View array_view = dark_vector_array_view(vector);

        DARK_TEST_EQ_U(array_view.size, 5);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_buffer")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        const Dark_Buffer buffer = dark_vector_buffer(vector);

        DARK_TEST_EQ_U(buffer.byte, 5 * sizeof(int));

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_buffer_view")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        const Dark_Buffer_View buffer_view = dark_vector_buffer_view(vector);

        DARK_TEST_EQ_U(buffer_view.byte, 5 * sizeof(int));

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_emplace(vector, 0, 1) = 100;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 100);

        *(int*)dark_vector_emplace(vector, 0, 1) = 101;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 101);

        *(int*)dark_vector_emplace(vector, 0, 1) = 99;

        DARK_TEST_EQ_U(DARK_VECTOR_FRONT(vector, int), 99);
        DARK_TEST_EQ_U(DARK_VECTOR_BACK(vector, int), 100);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace_front")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        int* pos_1 = dark_vector_emplace_front(vector, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 33);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 35);

        int* pos_2 = dark_vector_emplace_front(vector, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_vector_capacity(vector), 6);
        DARK_TEST_EQ_U(dark_vector_size(vector), 6);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 1);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 2);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 3);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 4);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 4, int), 33);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 5, int), 35);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace_back")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        int* pos_1 = dark_vector_emplace_back(vector, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 33);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 35);

        int* pos_2 = dark_vector_emplace_back(vector, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_vector_capacity(vector), 6);
        DARK_TEST_EQ_U(dark_vector_size(vector), 6);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 33);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 35);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 1);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 2);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 4, int), 3);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 5, int), 4);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace_array")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        const Dark_Array array = dark_vector_emplace_array(vector, 0, 10);

        DARK_TEST_EQ_U(array.size, 10);

        DARK_VECTOR_AT(vector, 9, int) = 42;

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace_array_front")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        const Dark_Array array = dark_vector_emplace_array_front(vector, 10);

        DARK_TEST_EQ_U(array.size, 10);

        DARK_VECTOR_AT(vector, 9, int) = 42;

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_emplace_array_back")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        const Dark_Array array = dark_vector_emplace_array_back(vector, 10);

        DARK_TEST_EQ_U(array.size, 10);

        DARK_VECTOR_AT(vector, 9, int) = 42;

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_inplace")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace(vector, 0) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *(int*)dark_vector_inplace(vector, 0) = 7;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 705);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_inplace_front")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_front(vector) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *(int*)dark_vector_inplace_front(vector) = 1;

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 1);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 705);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_inplace_back")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *(int*)dark_vector_inplace_back(vector) = 1;

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 1);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_inplace_array")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *((int*)(dark_vector_inplace_array(vector, 0).data)) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *((int*)(dark_vector_inplace_array(vector, 0).data)) = 7;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 705);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_inplace_array_front")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *((int*)(dark_vector_inplace_array_front(vector).data)) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *((int*)(dark_vector_inplace_array_front(vector).data)) = 7;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 7);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 705);

        dark_vector_delete(vector);
    }
    //--------------------------

//----------TEST----------
    DARK_TEST("vector_inplace_array_back")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *((int*)(dark_vector_inplace_array_back(vector).data)) = 705;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);

        *((int*)(dark_vector_inplace_array_back(vector).data)) = 7;

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 7);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 705);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 7);

        dark_vector_delete(vector);
    }
//--------------------------

    //----------TEST----------
    DARK_TEST("vector_push")
    {
        int buffer[2] = { 333, 666666 };
        const Dark_Array array = { sizeof(int), 2, buffer };

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_push(vector, 0, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);

        dark_vector_push(vector, 1, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 666666);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 666666);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 4);
        DARK_TEST_EQ_U(dark_vector_size(vector), 4);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_push_front")
    {
        int buffer[2] = { 333, 666666 };
        const Dark_Array array = { sizeof(int), 2, buffer };

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_push_front(vector, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);

        dark_vector_push_front(vector, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 666666);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 4);
        DARK_TEST_EQ_U(dark_vector_size(vector), 4);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_push_back")
    {
        int buffer[2] = { 333, 666666 };
        const Dark_Array array = { sizeof(int), 2, buffer };

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_push_back(vector, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);

        dark_vector_push_back(vector, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 666666);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 4);
        DARK_TEST_EQ_U(dark_vector_size(vector), 4);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_insert")
    {
        int a = 333;
        int b  = 666666;

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_insert(vector, 0, &a);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);

        dark_vector_insert(vector, 0, &b);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 333);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_insert_front")
    {
        int a = 333;
        int b  = 666666;

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_insert_front(vector, &a);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);

        dark_vector_insert_front(vector, &b);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 666666);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 333);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_insert_back")
    {
        int a = 333;
        int b  = 666666;

        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_insert_back(vector, &a);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);

        dark_vector_insert_back(vector, &b);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 333);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 666666);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 2);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_pop")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_pop(vector, 1, 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 10);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 6);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 999);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 3);
        DARK_TEST_EQ_U(dark_vector_size(vector), 3);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_pop_front")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_pop_front(vector, 3);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 6);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 999);

        dark_vector_pop_front(vector, 2);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_pop_back")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_pop_back(vector, 3);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 10);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 20);

        dark_vector_pop_back(vector, 2);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_erase")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_erase(vector, 0);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 20);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 55);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 6);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 3, int), 999);

        dark_vector_erase(vector, 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 20);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 55);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 2, int), 999);

        dark_vector_erase(vector, 1);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 20);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 999);

        dark_vector_erase(vector, 0);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 999);

        dark_vector_erase(vector, 0);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_erase_front")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_erase_front(vector);
        dark_vector_erase_front(vector);
        dark_vector_erase_front(vector);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 6);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 999);

        dark_vector_erase_front(vector);
        dark_vector_erase_front(vector);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_erase_back")
    {
        Dark_Vector* const vector = dark_vector_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        *(int*)dark_vector_inplace_back(vector) = 10;
        *(int*)dark_vector_inplace_back(vector) = 20;
        *(int*)dark_vector_inplace_back(vector) = 55;
        *(int*)dark_vector_inplace_back(vector) = 6;
        *(int*)dark_vector_inplace_back(vector) = 999;

        dark_vector_erase_back(vector);
        dark_vector_erase_back(vector);
        dark_vector_erase_back(vector);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 2);

        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 0, int), 10);
        DARK_TEST_EQ_U(DARK_VECTOR_AT(vector, 1, int), 20);

        dark_vector_erase_back(vector);
        dark_vector_erase_back(vector);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_reserve/_additional")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve(vector, 100);

        const size_t capacity = dark_vector_capacity(vector);
        DARK_TEST_GE_U(capacity, 100);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve(vector, 0);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), capacity);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve(vector, 101);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 101);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve_additional(vector, 101);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 202);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_reserve_exact")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve_exact(vector, 100);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 100);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve_exact(vector, 0);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve_exact(vector, 101);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 101);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_shrink_to_fit")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_reserve_exact(vector, 100);
        dark_vector_shrink_to_fit(vector);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_resize")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 0);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_resize(vector, 10);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 10);
        DARK_TEST_EQ_U(dark_vector_size(vector), 10);

        dark_vector_resize(vector, 5);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 10);
        DARK_TEST_EQ_U(dark_vector_size(vector), 5);

        dark_vector_resize(vector, 0);

        DARK_TEST_GE_U(dark_vector_capacity(vector), 10);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_clear")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 4);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 4);

        dark_vector_clear(vector);

        DARK_TEST_EQ_U(dark_vector_capacity(vector), 5);
        DARK_TEST_EQ_U(dark_vector_size(vector), 0);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_element_byte")
    {
        Dark_Vector* const vector = dark_vector_new_size(allocator, dark_growth_standard, sizeof(int), 5, 4);

        DARK_TEST_EQ_U(dark_vector_element_byte(vector), sizeof(int));

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_foreach")
    {
        Dark_Vector* const vector = dark_vector_new(allocator, dark_growth_standard, sizeof(int32_t));

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_vector_push_back(vector, dark_array_to_view(array));

        int32_t sum = 0;
        dark_vector_foreach(vector, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 444);

        dark_vector_delete(vector);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("vector_struct_byte")
    {
        DARK_TEST_GT_U(dark_vector_struct_byte(), 0);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
