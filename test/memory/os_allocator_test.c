#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("os_allocator_context_size")
    {
        DARK_TEST_GT_U(dark_os_allocator_context_size(), 0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("os_allocator_new/delete")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();
        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: malloc/free")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        char* data = dark_malloc(os_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 'a';
        data[1] = 'b';
        data[2] = 'c';
        data[3] = 'd';
        data[4] = 'e';

        dark_free(os_allocator, data, 5);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: balloc/bfree")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        uint64_t* data = dark_balloc(os_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;

        dark_bfree(os_allocator, data, sizeof(uint64_t), 5);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: realloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        char* data = dark_malloc(os_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_realloc(os_allocator, data, 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 'a';
        data[1] = 'b';
        data[2] = 'c';
        data[3] = 'd';
        data[4] = 'e';

        data[5] = 'x';

        dark_free(os_allocator, data, 6);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: brealloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        uint64_t* data = dark_balloc(os_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_brealloc(os_allocator, data, sizeof(uint64_t), 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;

        data[5] = 'x';

        dark_bfree(os_allocator, data, sizeof(uint64_t), 6);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: calloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        char* data = dark_calloc(os_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        DARK_TEST_EQ_I(data[0], 0);
        DARK_TEST_EQ_I(data[1], 0);
        DARK_TEST_EQ_I(data[2], 0);
        DARK_TEST_EQ_I(data[3], 0);
        DARK_TEST_EQ_I(data[4], 0);

        dark_free(os_allocator, data, 5);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: bcalloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        int64_t* data = dark_bcalloc(os_allocator, sizeof(int64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        DARK_TEST_EQ_I(data[0], 0);
        DARK_TEST_EQ_I(data[1], 0);
        DARK_TEST_EQ_I(data[2], 0);
        DARK_TEST_EQ_I(data[3], 0);
        DARK_TEST_EQ_I(data[4], 0);

        dark_bfree(os_allocator, data, sizeof(int64_t), 5);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: recalloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        char* data = dark_calloc(os_allocator, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_recalloc(os_allocator, data, 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 'a';
        data[1] = 'b';
        data[2] = 'c';
        data[3] = 'd';
        data[4] = 'e';

        data[5] = 'x';

        dark_free(os_allocator, data, 6);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("OS: brecalloc")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        uint64_t* data = dark_bcalloc(os_allocator, sizeof(uint64_t), 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data = dark_brecalloc(os_allocator, data, sizeof(uint64_t), 5, 6);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;

        data[5] = 'x';

        dark_bfree(os_allocator, data, sizeof(uint64_t), 6);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("os_allocator_info")
    {
        Dark_Allocator* os_allocator = dark_os_allocator_new();

        Dark_Allocator_Info info = dark_os_allocator_info(os_allocator);

        DARK_TEST_EQ_U(info.count, 1);
        DARK_TEST_GT_U(info.usage, 0);

        dark_os_allocator_delete(os_allocator);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
