#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("djb2_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_djb2_32(7, arr);
        hash_2 = dark_hash_djb2_32(7, arr);
        hash_3 = dark_hash_djb2_32(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1_32(7, arr);
        hash_2 = dark_hash_fnv1_32(7, arr);
        hash_3 = dark_hash_fnv1_32(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1a_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1a_32(7, arr);
        hash_2 = dark_hash_fnv1a_32(7, arr);
        hash_3 = dark_hash_fnv1a_32(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1_64")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1_64(7, arr);
        hash_2 = dark_hash_fnv1_64(7, arr);
        hash_3 = dark_hash_fnv1_64(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint64_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint64_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1a_64")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1a_64(7, arr);
        hash_2 = dark_hash_fnv1a_64(7, arr);
        hash_3 = dark_hash_fnv1a_64(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint64_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint64_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2_32(7, arr, 0);
        hash_2 = dark_hash_murmur2_32(7, arr, 0);
        hash_3 = dark_hash_murmur2_32(6, arr, 0);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_32(7, arr, 0);
        hash_2 = dark_hash_murmur2a_32(7, arr, 0);
        hash_3 = dark_hash_murmur2a_32(6, arr, 0);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_64")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_64(7, arr, 0);
        hash_2 = dark_hash_murmur2a_64(7, arr, 0);
        hash_3 = dark_hash_murmur2a_64(6, arr, 0);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint64_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint64_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur3_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur3_32(7, arr, 0);
        hash_2 = dark_hash_murmur3_32(7, arr, 0);
        hash_3 = dark_hash_murmur3_32(6, arr, 0);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("superfast_32")
    {
        int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_superfast_32(7, arr);
        hash_2 = dark_hash_superfast_32(7, arr);
        hash_3 = dark_hash_superfast_32(6, arr);
        DARK_TEST_EQ_M(&hash_1, &hash_2, sizeof(uint32_t));
        DARK_TEST_NE_M(&hash_2, &hash_3, sizeof(uint32_t));
    }
    //--------------------------

    dark_test_end();

    return EXIT_SUCCESS;
}
