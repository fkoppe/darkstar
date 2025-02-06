#include <dark/darkstar.h>
#include <dark/darktest.h>

void foreach_helper(int32_t* element, int32_t* constext)
{
    *constext += *element;
}

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array_to")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array = { sizeof(int32_t), 5, buffer};

        dark_array_to_view(array);
        dark_array_to_buffer(array);
        dark_array_to_buffer_view(array);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_ITERATOR")
    {
        int buffer[12] = {0};
        Dark_Array array = { sizeof(int), 12, buffer };

        Dark_Iterator* iterator = dark_iterator_new(allocator);

        dark_array_iterator(array, iterator);

        size_t i = 0;
        while (!dark_iterator_next_is(iterator))
        {
            dark_iterator_peek(iterator);
            dark_iterator_next(iterator);

            i++;
        }

        DARK_TEST_EQ_U(12, i);

        dark_iterator_reset(iterator);

        DARK_TEST_EQ_U(dark_iterator_skip(iterator, i), i);
        DARK_TEST_EQ_U(dark_iterator_skip(iterator, 100), 0);

        dark_iterator_delete(iterator);
    }
    //--------------------------

        //----------TEST----------
    DARK_TEST("array_iterator_context_byte")
    {
        DARK_TEST_NE_U(dark_array_iterator_context_byte(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_foreach")
    {
        int32_t buffer[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array = { sizeof(int32_t), 5, buffer};

        int32_t sum = 0;
        dark_array_foreach(array, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 10);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_compare")
    {
        int32_t buffer_1[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array_1 = { sizeof(int32_t), 5, buffer_1};

        int32_t buffer_2[5] = { 0, 1, 2, 3, 4 };
        Dark_Array array_2 = { sizeof(int32_t), 5, buffer_2};

        int32_t buffer_3[5] = { 0, 1, 2, 99, 4 };
        Dark_Array array_3 = { sizeof(int32_t), 5, buffer_3};

        DARK_TEST_NE_U(0, dark_array_compare(&array_1, &array_3));
        DARK_TEST_EQ_U(0, dark_array_compare(&array_1, &array_2));
        DARK_TEST_NE_U(0, dark_array_compare(&array_2, &array_3));
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
