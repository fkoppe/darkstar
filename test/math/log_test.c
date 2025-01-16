#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("mult_u8")
    {
        DARK_TEST_EQ_U(dark_mult_u8(0, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u8(UINT8_MAX, 0), 0);
        DARK_TEST_EQ_U(dark_mult_u8(0, UINT8_MAX), 0);

        DARK_TEST_EQ_U(dark_mult_u8(UINT8_MAX, 1), UINT8_MAX);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
