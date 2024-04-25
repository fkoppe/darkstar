#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST----------
    DARK_TEST("stopwatch")
    {
        Dark_Stopwatch* stopwatch = dark_stopwatch_new();

        dark_stopwatch_start(stopwatch);

        Dark_Stopwatch* other = dark_stopwatch_new_start();
        while (dark_stopwatch_ms(other) < 1)
        {

        }
        dark_stopwatch_delete(other);

        DARK_TEST_GE_U(dark_stopwatch_delete_ms(stopwatch), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stamp_hms")
    {
        char buffer[DARK_STAMP_HMS_SIZE];

        dark_stamp_hms(buffer);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stamp_hms_terminated")
    {
        char buffer[DARK_STAMP_HMS_SIZE_TERMINATED];

        dark_stamp_hms_terminated(buffer);

        dark_cstring_lenght(buffer);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
