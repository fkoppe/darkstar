#include <dark/darkstar.h>

int main()
{
    //test test
    DARK_TEST(true);
    DARK_TEST_EQ_U(1, 1);
    DARK_TEST_NE_U(2, 1);
    DARK_TEST_LT_U(1, 2);
    DARK_TEST_LE_U(1, 1);
    DARK_TEST_LE_U(1, 2);
    DARK_TEST_GT_U(2, 1);
    DARK_TEST_GE_U(2, 2);
    DARK_TEST_GE_U(2, 1);

    DARK_TEST_EQ_I(-1, 2-3);
    DARK_TEST_NE_I(2, 1);
    DARK_TEST_LT_I(1, 2);
    DARK_TEST_LE_I(1, 1);
    DARK_TEST_LE_I(1, 2);
    DARK_TEST_GT_I(2, 1);
    DARK_TEST_GE_I(2, 2);
    DARK_TEST_GE_I(2, 1);

    //assert_test
    DARK_ASSERT(0 == 0, DARK_ERROR_UNKNOWN);

    //min_max test
    DARK_TEST_EQ_U(DARK_MAX(10, 1), 10);
    DARK_TEST_EQ_U(DARK_MIN(10, 1), 1);

    //version_test
    const uint8_t major_max = 255;
    const uint16_t minor_max = 1023;
    const uint8_t stage_max = 3;
    const uint16_t patch_max = 4095;

    uint32_t version =  dark_version_make(major_max, minor_max, stage_max, patch_max);

    DARK_TEST_EQ_U(major_max, dark_version_major(version));
    DARK_TEST_EQ_U(minor_max, dark_version_minor(version));
    DARK_TEST_EQ_U(stage_max, dark_version_stage(version));
    DARK_TEST_EQ_U(patch_max, dark_version_patch(version));

    return EXIT_SUCCESS;
}
