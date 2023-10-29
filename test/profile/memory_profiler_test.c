#include <dark/darkstar.h>

int main()
{
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);

    void* pointer_1 = malloc(100);
    DARK_TEST(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 100);
    DARK_TEST(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 100);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 100);

    pointer_1 = realloc(pointer_1, 200);
    DARK_TEST(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 200);
    DARK_TEST(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 2);
    DARK_TEST(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 300);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 200);

    void* pointer_2 = calloc(3, 10);

    DARK_TEST(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 2);
    DARK_TEST(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 230);
    DARK_TEST(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 3);
    DARK_TEST(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 330);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 2);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 230);

    free(pointer_1);

    DARK_TEST(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1);
    DARK_TEST(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 30);
    DARK_TEST(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 3);
    DARK_TEST(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 330);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 2);
    DARK_TEST(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 230);

    free(pointer_2);

    DARK_TEST(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 0);
    DARK_TEST(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 0);

    dark_memory_profiler_shutdown(false);

    return EXIT_SUCCESS;
}

