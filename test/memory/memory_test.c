#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("ALLOCATOR_NATIVE/malloc/free")
    {
        char* data = dark_malloc(DARK_ALLOCATOR_NATIVE, 5);
        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

        data[0] = 'a';
        data[1] = 'b';
        data[2] = 'c';
        data[3] = 'd';
        data[4] = 'e';

        dark_free(DARK_ALLOCATOR_NATIVE, data, 5);
    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("balloc/bfree")
//    {
//        uint64_t* data = dark_balloc(DARK_ALLOCATOR_NATIVE, sizeof(uint64_t), 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        data[0] = 1;
//        data[1] = 2;
//        data[2] = 3;
//        data[3] = 4;
//        data[4] = 5;

//        dark_bfree(DARK_ALLOCATOR_NATIVE, data, sizeof(uint64_t), 5);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("realloc")
//    {
//        char* data = dark_malloc(DARK_ALLOCATOR_NATIVE, 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        dark_realloc(DARK_ALLOCATOR_NATIVE, data, 5, 6);

//        data[0] = 'a';
//        data[1] = 'b';
//        data[2] = 'c';
//        data[3] = 'd';
//        data[4] = 'e';

//        data[5] = 'x';

//        dark_free(DARK_ALLOCATOR_NATIVE, data, 6);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("brealloc")
//    {
//        uint64_t* data = dark_balloc(DARK_ALLOCATOR_NATIVE, sizeof(uint64_t), 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        data = dark_brealloc(DARK_ALLOCATOR_NATIVE, data, sizeof(uint64_t), 5, 6);

//        data[0] = 1;
//        data[1] = 2;
//        data[2] = 3;
//        data[3] = 4;
//        data[4] = 5;

//        data[5] = 'x';

//        dark_bfree(DARK_ALLOCATOR_NATIVE, data, sizeof(uint64_t), 6);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("calloc")
//    {
//        char* data = dark_calloc(DARK_ALLOCATOR_NATIVE, 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        DARK_TEST_EQ_I(data[0], 0);
//        DARK_TEST_EQ_I(data[1], 0);
//        DARK_TEST_EQ_I(data[2], 0);
//        DARK_TEST_EQ_I(data[3], 0);
//        DARK_TEST_EQ_I(data[4], 0);

//        dark_free(DARK_ALLOCATOR_NATIVE, data, 5);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("bcalloc")
//    {
//        int64_t* data = dark_bcalloc(DARK_ALLOCATOR_NATIVE, sizeof(int64_t), 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        DARK_TEST_EQ_I(data[0], 0);
//        DARK_TEST_EQ_I(data[1], 0);
//        DARK_TEST_EQ_I(data[2], 0);
//        DARK_TEST_EQ_I(data[3], 0);
//        DARK_TEST_EQ_I(data[4], 0);

//        dark_bfree(DARK_ALLOCATOR_NATIVE, data, sizeof(int64_t), 5);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("recalloc")
//    {
//        char* data = dark_malloc(DARK_ALLOCATOR_NATIVE, 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        data = dark_recalloc(DARK_ALLOCATOR_NATIVE, data, 5, 10);

//        DARK_TEST_EQ_I(data[5], 0);
//        DARK_TEST_EQ_I(data[6], 0);
//        DARK_TEST_EQ_I(data[7], 0);
//        DARK_TEST_EQ_I(data[8], 0);
//        DARK_TEST_EQ_I(data[9], 0);

//        dark_free(DARK_ALLOCATOR_NATIVE, data, 5);
//    }
    //--------------------------

    //----------TEST----------
//    DARK_TEST("brecalloc")
//    {
//        uint64_t* data = dark_balloc(DARK_ALLOCATOR_NATIVE, sizeof(uint64_t), 5);
//        DARK_ASSERT(NULL != data, DARK_ERROR_ALLOCATION);

//        data = dark_brecalloc(DARK_ALLOCATOR_NATIVE, data, sizeof(uint64_t), 5, 6);

//        data[5] = 0;

//        dark_bfree(DARK_ALLOCATOR_NATIVE, data, sizeof(uint64_t), 6);
//    }
    //--------------------------

    dark_test_end();

    return DARK_EXIT_SUCCESS;
}
