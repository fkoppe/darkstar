#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array_iterator_context_size")
    {
        DARK_TEST_NE_U(dark_array_iterator_context_size(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_iterator_new/delete")
    {
        int buffer[12] = {0};
        Dark_Array array = { buffer, 12, sizeof(int) };

        Dark_Iterator* iterator = dark_array_iterator_new(allocator, &array);

        dark_array_iterator_delete(allocator, iterator);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
