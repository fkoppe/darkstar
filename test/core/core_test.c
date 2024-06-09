#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("ASSERT")
    {
        DARK_ASSERT(true, DARK_ERROR_UNKNOWN);
        DARK_ASSERT_CSTRING(true, DARK_ERROR_UNKNOWN, "hello");
        DARK_ASSERT_MESSAGE(true, DARK_ERROR_UNKNOWN, DARK_MESSAGE_ASSERT);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("mem")
    {
        char buffer_1[16] = { 0 };
        char buffer_2[16] = { 0 };

        dark_memset(buffer_1, 'x', 16);
        dark_memcpy(buffer_2, buffer_1, 8);
        DARK_TEST_GE_I(dark_memcmp(buffer_1, buffer_2, 16), 1);
        dark_memmove(buffer_2 + 4, buffer_1 + 4, 8);
        dark_memmove(buffer_2 + 12, buffer_2 + 8, 4);
        DARK_TEST_EQ_I(dark_memcmp(buffer_1, buffer_2, 16), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("sprint")
    {
        char buffer_1[8] = { 0 };
        char buffer_2[8] = { 'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b' };

        dark_snprintf_notterminated(8, buffer_1, "%s%s", "aaaa", "bbbb");
        DARK_TEST_EQ_I(dark_memcmp(buffer_1, buffer_2, 16), 0);

        dark_snprintf_terminated(8, buffer_1, "%s%s", "aaaa", "bbbb");
        DARK_TEST_NE_I(dark_memcmp(buffer_1, buffer_2, 16), 0);
        DARK_TEST_EQ_I(buffer_1[7], '\0');
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

    return DARK_EXIT_SUCCESS;
}
