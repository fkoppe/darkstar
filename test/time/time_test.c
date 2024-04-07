#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("stopwatch")
    {
        void* stopwatch = dark_stopwatch_new();

        dark_stopwatch_start(stopwatch);

        void* other = dark_stopwatch_new_start();
        while (dark_stopwatch_ms(other) < 1)
        {

        }
        dark_stopwatch_delete(other);

        DARK_TEST_GE_U(dark_stopwatch_delete_ms(stopwatch), 1);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("stamp_hms")
    {
        char buffer[DARK_STAMP_HMS_SIZE];

        dark_stamp_hms(buffer);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("stamp_hms_terminated")
    {
        char buffer[DARK_STAMP_HMS_SIZE_TERMINATED];

        dark_stamp_hms_terminated(buffer);

        dark_cstring_lenght(buffer);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
