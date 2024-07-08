#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* os_allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("DEBUG_MEMORY")
    {
        int64_t* integer = dark_malloc(os_allocator, sizeof(int64_t));

        integer = dark_realloc(os_allocator, integer, sizeof(int64_t), 2*sizeof(int64_t));

        dark_free(os_allocator, integer, 2*sizeof(int64_t));
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(os_allocator);

    return DARK_EXIT_SUCCESS;
}
