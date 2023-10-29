#include <dark/darkstar.h>

int main()
{

#if defined(___DARK_DEBUG)

    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);

    void* pointer_1 = malloc(100);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1, dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 100, dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 1, dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 100, dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 1, dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 100, dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage);

    pointer_1 = realloc(pointer_1, 200);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1, dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 200, dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 2, dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 300, dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 1, dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 200, dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage);

    void* pointer_2 = calloc(3, 10);

    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 2, dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 230, dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 3, dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 330, dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 2, dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 230, dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage);

    free(pointer_1);

    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 1, dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 30, dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count == 3, dark_memory_profiler_info_all_get().total.count - dark_memory_profiler_info_own_get().total.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage == 330, dark_memory_profiler_info_all_get().total.usage - dark_memory_profiler_info_own_get().total.usage);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count == 2, dark_memory_profiler_info_all_get().peak.count - dark_memory_profiler_info_own_get().peak.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage == 230, dark_memory_profiler_info_all_get().peak.usage - dark_memory_profiler_info_own_get().peak.usage);

    free(pointer_2);

    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count == 0, dark_memory_profiler_info_all_get().current.count - dark_memory_profiler_info_own_get().current.count);
    DARK_TEST_UINT(dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage == 0, dark_memory_profiler_info_all_get().current.usage - dark_memory_profiler_info_own_get().current.usage);

    dark_memory_profiler_shutdown(false);

#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}

