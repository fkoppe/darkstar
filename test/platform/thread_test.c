#include <dark/darkstar.h>
#include <dark/darktest.h>

void test(int* const integer_)
{
    DARK_ASSERT(NULL != integer_, DARK_ERROR_NULL);

    *integer_ = 42;
}

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    DARK_TEST("thread_struct_byte")
    {
        DARK_TEST_GT_U(dark_thread_struct_byte(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("thread")
    {
        int integer = 0;
        void* thread = dark_thread_new(allocator, (Dark_Thread_Worker)test, &integer);

        DARK_TEST_NE_U(dark_thread_id(thread), dark_thread_current_id());

        dark_thread_join(thread);

        DARK_TEST_EQ_I(integer, 42);

        dark_thread_delete(allocator, thread);

    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
