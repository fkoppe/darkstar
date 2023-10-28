#include "dark/core/macro.h"
#include <dark/darkstar.h>

int main()
{
    //test test
    DARK_TEST(NULL == NULL);

    //assert_test
    DARK_ASSERT(0 == 0, DARK_ERROR_UNKNOWN);

    //min_max test
    DARK_TEST(DARK_MAX(10, 1) == 10);
    DARK_TEST(DARK_MIN(10, 1) == 1);

    //version_test
    const uint8_t major_max = 255;
    const uint16_t minor_max = 1023;
    const uint8_t stage_max = 3;
    const uint16_t patch_max = 4095;

    uint32_t version =  dark_version_make(major_max, minor_max, stage_max, patch_max);

    DARK_TEST_UINT(dark_version_major(version) == major_max, dark_version_major(version));
    DARK_TEST_UINT(dark_version_minor(version) == minor_max, dark_version_major(version));
    DARK_TEST_UINT(dark_version_stage(version) == stage_max, dark_version_major(version));
    DARK_TEST_UINT(dark_version_patch(version) == patch_max, dark_version_major(version));

    return EXIT_SUCCESS;
}
