#include <dark/darkstar.h>
#include <dark/test.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("range_is_u")
    {
       DARK_TEST_FALSE(dark_range_is_u(150, 2, 10));
       DARK_TEST_TRUE(dark_range_is_u(150, 150, 150));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("range_is_i")
    {
        DARK_TEST_FALSE(dark_range_is_i(-150, -2, 10));
        DARK_TEST_TRUE(dark_range_is_i(-150, -150, -150));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("clamp_u")
    {
       DARK_TEST_EQ_U(dark_range_clamp_u(150, 2, 10), 10);
       DARK_TEST_EQ_U(dark_range_clamp_u(150, 150, 150), 150);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("clamp_i")
    {
        DARK_TEST_EQ_I(dark_range_clamp_i(-150, -2, 10), -2);
        DARK_TEST_EQ_I(dark_range_clamp_i(-150, -150, -150), -150);
    }
    //--------------------------

    dark_test_shutdown();

    return dark_test_return();
}
