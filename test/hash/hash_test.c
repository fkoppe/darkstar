#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("djb2_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_djb2_32(array_view_1);
        hash_2 = dark_hash_djb2_32(array_view_1);
        hash_3 = dark_hash_djb2_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1_32(array_view_1);
        hash_2 = dark_hash_fnv1_32(array_view_1);
        hash_3 = dark_hash_fnv1_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1a_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1a_32(array_view_1);
        hash_2 = dark_hash_fnv1a_32(array_view_1);
        hash_3 = dark_hash_fnv1a_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1_64")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1_64(array_view_1);
        hash_2 = dark_hash_fnv1_64(array_view_1);
        hash_3 = dark_hash_fnv1_64(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("fnv1a_64")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_fnv1a_64(array_view_1);
        hash_2 = dark_hash_fnv1a_64(array_view_1);
        hash_3 = dark_hash_fnv1a_64(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2_32(array_view_1);
        hash_2 = dark_hash_murmur2_32(array_view_1);
        hash_3 = dark_hash_murmur2_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_32(array_view_1);
        hash_2 = dark_hash_murmur2a_32(array_view_1);
        hash_3 = dark_hash_murmur2a_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_64")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_64(array_view_1);
        hash_2 = dark_hash_murmur2a_64(array_view_1);
        hash_3 = dark_hash_murmur2a_64(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur3_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur3_32(array_view_1);
        hash_2 = dark_hash_murmur3_32(array_view_1);
        hash_3 = dark_hash_murmur3_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2_seed_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2_seed_32(array_view_1, 0);
        hash_2 = dark_hash_murmur2_seed_32(array_view_1, 0);
        hash_3 = dark_hash_murmur2_seed_32(array_view_2, 0);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_seed_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_seed_32(array_view_1, 0);
        hash_2 = dark_hash_murmur2a_seed_32(array_view_1, 0);
        hash_3 = dark_hash_murmur2a_seed_32(array_view_2, 0);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur2a_seed_64")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur2a_seed_64(array_view_1, 0);
        hash_2 = dark_hash_murmur2a_seed_64(array_view_1, 0);
        hash_3 = dark_hash_murmur2a_seed_64(array_view_2, 0);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("murmur3_seed_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_murmur3_seed_32(array_view_1, 0);
        hash_2 = dark_hash_murmur3_seed_32(array_view_1, 0);
        hash_3 = dark_hash_murmur3_seed_32(array_view_2, 0);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("superfast_32")
    {
        int buf[7] = { 1, 2, 3, 4, 5, 6, 7 };
        Dark_Buffer_View array_view_1 = { 7, buf };
        Dark_Buffer_View array_view_2 = { 6, buf };

        uint64_t hash_1 = 0;
        uint64_t hash_2 = 0;
        uint64_t hash_3 = 0;

        hash_1 = dark_hash_superfast_32(array_view_1);
        hash_2 = dark_hash_superfast_32(array_view_1);
        hash_3 = dark_hash_superfast_32(array_view_2);
        DARK_TEST_EQ_U(hash_1, hash_2);
        DARK_TEST_NE_U(hash_2, hash_3);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
