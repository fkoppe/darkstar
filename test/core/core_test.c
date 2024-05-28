#include <dark/darkstar.h>
#include <dark/test.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("ASSERT")
    {
        DARK_ASSERT(0 == 0, DARK_ERROR_UNKNOWN);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("MIN/MAX")
    {
        DARK_TEST_EQ_U(DARK_MAX(10, 1), 10);
        DARK_TEST_EQ_U(DARK_MIN(10, 1), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("version")
    {
        const uint8_t major_max = 255;
        const uint16_t minor_max = 1023;
        const uint8_t stage_max = 3;
        const uint16_t patch_max = 4095;

        const uint32_t version =  dark_version_make(major_max, minor_max, stage_max, patch_max);

        DARK_TEST_EQ_U(major_max, dark_version_major(version));
        DARK_TEST_EQ_U(minor_max, dark_version_minor(version));
        DARK_TEST_EQ_U(stage_max, dark_version_stage(version));
        DARK_TEST_EQ_U(patch_max, dark_version_patch(version));
    }
    //--------------------------

    dark_test_shutdown();

    return dark_test_return();
}
