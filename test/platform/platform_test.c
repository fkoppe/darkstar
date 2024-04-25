#include <dark/darkstar.h>

void test(int* const integer_)
{
    DARK_ASSERT(NULL != integer_, DARK_ERROR_NULL);

    *integer_ = 42;

    return;
}

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST----------
    DARK_TEST("console_show/_hide")
    {
        dark_console_hide();
        dark_console_show();
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("clock")
    {
        dark_clock_ns();
        dark_clock_ms();
        dark_clock_s();
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("process")
    {
        dark_process_id();
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("thread")
    {
        dark_thread_id_current();

        int integer = 0;
        void* thread = dark_thread_new(test, &integer);

        DARK_TEST_NE_U(dark_thread_id(thread), dark_thread_id_current());

        dark_thread_join(thread);

        DARK_TEST_EQ_I(integer, 42);

        dark_thread_delete(thread);

    }
    //--------------------------

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
