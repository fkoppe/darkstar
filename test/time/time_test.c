#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* stopwatch = dark_stopwatch_new_start();
    void* watch_2 = dark_stopwatch_new();

    dark_stopwatch_start(watch_2);

    while(dark_stopwatch_ns(watch_2) / DARK_GIGA < 1)
    {
        continue;
    }

    DARK_TEST_GE_U(dark_stopwatch_restart_ns(watch_2) / DARK_GIGA, 1);

    while(dark_stopwatch_ns(watch_2) / DARK_GIGA < 1)
    {
        continue;
    }

    dark_stopwatch_reset(watch_2);
    DARK_TEST_EQ_U(dark_stopwatch_ns(watch_2), 0);

    dark_stopwatch_delete(watch_2);
    DARK_TEST_GE_U(dark_stopwatch_delete_ns(stopwatch) / DARK_GIGA, 2);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
