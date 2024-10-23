#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("gcd_u")
    {
        DARK_TEST_EQ_U(dark_gcd_u(0, 0), 0);
        DARK_TEST_EQ_U(dark_gcd_u(1, 0), 1);
        DARK_TEST_EQ_U(dark_gcd_u(0, 1), 1);
        DARK_TEST_EQ_U(dark_gcd_u(1, 1), 1);
        DARK_TEST_EQ_U(dark_gcd_u(1, 2), 1);
        DARK_TEST_EQ_U(dark_gcd_u(9, 6), 3);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("gcd_i")
    {
        DARK_TEST_EQ_U(dark_gcd_i(0, 0), 0);
        DARK_TEST_EQ_U(dark_gcd_i(-1, 0), 1);
        DARK_TEST_EQ_U(dark_gcd_i(0, -1), 1);
        DARK_TEST_EQ_U(dark_gcd_i(-1, -1), 1);
        DARK_TEST_EQ_U(dark_gcd_i(-1, 2), 1);
        DARK_TEST_EQ_U(dark_gcd_i(-9, 6), 3);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("lcd_u")
    {
        DARK_TEST_EQ_U(dark_lcm_u(0, 0), 0);
        DARK_TEST_EQ_U(dark_lcm_u(1, 0), 0);
        DARK_TEST_EQ_U(dark_lcm_u(0, 1), 0);
        DARK_TEST_EQ_U(dark_lcm_u(1, 1), 1);
        DARK_TEST_EQ_U(dark_lcm_u(1, 2), 2);
        DARK_TEST_EQ_U(dark_lcm_u(9, 6), 18);

        DARK_TEST_EQ_U(dark_lcm_u(72, 120), 360);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("lcd_i")
    {
        DARK_TEST_EQ_U(dark_lcm_i(0, 0), 0);
        DARK_TEST_EQ_U(dark_lcm_i(-1, 0), 0);
        DARK_TEST_EQ_U(dark_lcm_i(0, -1), 0);
        DARK_TEST_EQ_U(dark_lcm_i(1, -1), 1);
        DARK_TEST_EQ_U(dark_lcm_i(1, -2), 2);
        DARK_TEST_EQ_U(dark_lcm_i(-9, 6), 18);

        DARK_TEST_EQ_U(dark_lcm_i(-72, -120), 360);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
