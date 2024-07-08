#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("mutex_new/delete")
    {
        Dark_Mutex* const mutex = dark_mutex_new(allocator);
        dark_mutex_delete(allocator, mutex);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("mutex_lock/unlock")
    {
        Dark_Mutex* const mutex = dark_mutex_new(allocator);

        dark_mutex_lock(mutex);

        DARK_TEST_TRUE(dark_mutex_trylock(mutex));

        dark_mutex_unlock(mutex);

        dark_mutex_delete(allocator, mutex);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("mutex_trylock")
    {
        Dark_Mutex* const mutex = dark_mutex_new(allocator);

        dark_mutex_lock(mutex);
        dark_mutex_unlock(mutex);

        DARK_TEST_TRUE(dark_mutex_trylock(mutex));
        dark_mutex_unlock(mutex);

        dark_mutex_delete(allocator, mutex);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
