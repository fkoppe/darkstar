#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* mutex = dark_mutex_new();

    dark_mutex_lock(mutex);

    //This is undefined behavior that cant be protected against
    //DARK_TEST(!dark_mutex_trylock(mutex));

    dark_mutex_unlock(mutex);
    DARK_TEST(dark_mutex_trylock(mutex));
    dark_mutex_unlock(mutex);

    dark_mutex_delete(mutex);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
