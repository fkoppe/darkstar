#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST----------
    DARK_TEST("mutex_new/delete")
    {
        Dark_Mutex* const mutex = dark_mutex_new();
        dark_mutex_delete(mutex);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("mutex_lock/unlock")
    {
        Dark_Mutex* const mutex = dark_mutex_new();

        dark_mutex_lock(mutex);

        //This would be undefined behavior
        //DARK_TEST_TRUE(!dark_mutex_trylock(mutex));

        dark_mutex_unlock(mutex);

        dark_mutex_delete(mutex);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("mutex_trylock")
    {
        Dark_Mutex* const mutex = dark_mutex_new();

        dark_mutex_lock(mutex);
        dark_mutex_unlock(mutex);

        DARK_TEST_TRUE(dark_mutex_trylock(mutex));
        dark_mutex_unlock(mutex);

        dark_mutex_delete(mutex);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
