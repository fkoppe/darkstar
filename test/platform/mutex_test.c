#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("mutex_create/destroy")
    {
        void* mutex = malloc(dark_file_struct_size());
        DARK_ASSERT(NULL != mutex, DARK_ERROR_ALLOCATION);

        dark_file_create(mutex);
        dark_file_destroy(mutex);

        free(mutex);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("mutex_new/delete")
    {
        void* const mutex = dark_mutex_new();
        dark_mutex_delete(mutex);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("mutex_lock/unlock")
    {
        void* const mutex = dark_mutex_new();

        dark_mutex_lock(mutex);

        //This would be undefined behavior
        //DARK_TEST(!dark_mutex_trylock(mutex));

        dark_mutex_unlock(mutex);

        dark_mutex_delete(mutex);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("mutex_trylock")
    {
        void* const mutex = dark_mutex_new();

        dark_mutex_lock(mutex);
        dark_mutex_unlock(mutex);

        DARK_TEST(dark_mutex_trylock(mutex));
        dark_mutex_unlock(mutex);

        dark_mutex_delete(mutex);
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
