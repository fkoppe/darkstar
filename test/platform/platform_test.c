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

    dark_clock_ns();

    dark_process_id();
    dark_thread_id_current();

    int integer = 0;
    void* thread = dark_thread_new(test, &integer);

    DARK_TEST_NE_U(dark_thread_id(thread), dark_thread_id_current());

    dark_thread_join(thread);

    DARK_TEST_EQ_I(integer, 42);

    dark_thread_delete(thread);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
