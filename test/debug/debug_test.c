#include <dark/darkstar.h>

int main()
{
    Dark_Allocator* os_allocator = dark_os_allocator_new();

    //----------TEST----------
    DARK_TEST("DEBUG_MEMORY")
    {
        DARK_DEBUG_MEMORY_INITIALISE;

        int64_t* integer = dark_malloc(os_allocator, sizeof(int64_t));

        integer = dark_realloc(os_allocator, integer, sizeof(int64_t), 2*sizeof(int64_t));

        dark_free(os_allocator, integer, 2*sizeof(int64_t));

        DARK_DEBUG_MEMORY_SHUTDOWN;
    }
    //--------------------------

#if defined(___DARK_DEBUG)
    //----------TEST----------
    DARK_TEST("DEBUG_PRINT")
    {
        DARK_DEBUG_PRINT("hello");
        DARK_DEBUG_PRINTF("w%srld", "o");
    }
    //--------------------------
#endif // defined(___DARK_DEBUG)

    dark_test_end();

    dark_os_allocator_delete(os_allocator);

    return DARK_EXIT_SUCCESS;
}
