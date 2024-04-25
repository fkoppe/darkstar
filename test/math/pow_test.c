#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("ppow_u")
    {
        DARK_TEST_EQ_U(1, dark_ppow_u(112, 0));
        DARK_TEST_EQ_U(112, dark_ppow_u(112, 1));
        DARK_TEST_EQ_U(4, dark_ppow_u(2, 2));
        DARK_TEST_EQ_U(8, dark_ppow_u(2, 3));
        DARK_TEST_EQ_U(0, dark_ppow_u(0, 3));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ppow_i")
    {
        DARK_TEST_EQ_I(1, dark_ppow_i(-112, 0));
        DARK_TEST_EQ_I(-112, dark_ppow_i(-112, 1));
        DARK_TEST_EQ_I(4, dark_ppow_i(-2, 2));
        DARK_TEST_EQ_I(-8, dark_ppow_i(-2, 3));
        DARK_TEST_EQ_U(0, dark_ppow_i(0, 3));
    }
    //--------------------------

    dark_test_end();

    return EXIT_SUCCESS;
}
