#include <dark/darkstar.h>

int main()
{
    //assert_test
    DARK_ASSERT(0 == 0, DARK_ERROR_UNKNOWN);

    //version_test
    const uint8_t major_max = 255;
    const uint16_t minor_max = 1023;
    const uint8_t stage_max = 3;
    const uint16_t patch_max = 4095;

    uint32_t version =  dark_version_make(major_max, minor_max, stage_max, patch_max);

    DARK_ASSERT(dark_version_major(version) == major_max, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_version_minor(version) == minor_max, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_version_stage(version) == stage_max, DARK_ERROR_UNKNOWN);
    DARK_ASSERT(dark_version_patch(version) == patch_max, DARK_ERROR_UNKNOWN);

    return EXIT_SUCCESS;
}
