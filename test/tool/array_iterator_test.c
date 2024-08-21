#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/tool/array_iterator_context.h>
#include <dark/tool/iterator_struct.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array_iterator_construct/_destruct")
    {
        Dark_Array_Iterator_Context context;
        Dark_Iterator* const iterator = dark_malloc(allocator, sizeof(*iterator));

        int buffer[12] = {0};
        Dark_Array array = { sizeof(int), 12, buffer };

        dark_array_iterator_construct(allocator, iterator, &context, array);
        dark_array_iterator_destruct(iterator);

        dark_free(allocator, iterator, sizeof(*iterator));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_iterator_new/delete")
    {
        int buffer[12] = {0};
        Dark_Array array = { sizeof(int), 12, buffer };

        Dark_Iterator* iterator = dark_array_iterator_new(allocator, array);

        dark_array_iterator_delete(iterator);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_iterator")
    {
        int buffer[12] = {0};
        Dark_Array array = { sizeof(int), 12, buffer };

        Dark_Iterator* iterator = dark_array_iterator_new(allocator, array);

        size_t i = 0;
        while (!dark_iterator_done(iterator))
        {
            dark_iterator_peek(iterator);
            dark_iterator_next(iterator);

            i++;
        }

        DARK_TEST_EQ_U(12, i);

        dark_iterator_reset(iterator);

        DARK_TEST_EQ_U(dark_iterator_skip(iterator, i), i);
        DARK_TEST_EQ_U(dark_iterator_skip(iterator, 100), 0);

        dark_array_iterator_delete(iterator);
    }
    //--------------------------

        //----------TEST----------
    DARK_TEST("array_iterator_context_byte")
    {
        DARK_TEST_NE_U(dark_array_iterator_context_byte(), 0);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
