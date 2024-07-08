#include <dark/darkstar.h>
#include <dark/darktest.h>

static int buffer;

void* allocate_helper(void* context, void* address, size_t byte_old, size_t byte_new)
{
    if(0 == byte_new)
    {
        return NULL;
    }
    else
    {
        return &buffer;
    }
}

static const Dark_Allocator_Struct custom_allocator_struct = { allocate_helper, allocate_helper, NULL };
static Dark_Allocator* const custom_allocator = (Dark_Allocator*)&custom_allocator_struct;

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("malloc/free")
    {
        char* data = dark_malloc(custom_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_free(custom_allocator, data, 5);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("balloc/bfree")
    {
        uint64_t* data = dark_balloc(custom_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_bfree(custom_allocator, data, sizeof(uint64_t), 5);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("realloc")
    {
        char* data = dark_malloc(custom_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_realloc(custom_allocator, data, 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_free(custom_allocator, data, 6);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("brealloc")
    {
        uint64_t* data = dark_balloc(custom_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_brealloc(custom_allocator, data, sizeof(uint64_t), 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_bfree(custom_allocator, data, sizeof(uint64_t), 6);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("calloc")
    {
        char* data = dark_calloc(custom_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_free(custom_allocator, data, 5);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("bcalloc")
    {
        int64_t* data = dark_bcalloc(custom_allocator, sizeof(int64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_bfree(custom_allocator, data, sizeof(int64_t), 5);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("recalloc")
    {
        char* data = dark_malloc(custom_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_recalloc(custom_allocator, data, 5, 10);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_free(custom_allocator, data, 10);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("brecalloc")
    {
        uint64_t* data = dark_balloc(custom_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_brecalloc(custom_allocator, data, sizeof(uint64_t), 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        dark_bfree(custom_allocator, data, sizeof(uint64_t), 6);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
