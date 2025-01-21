#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
     dark_test_initialise();

    //----------TEST----------
    DARK_TEST("TEST")
    {
        DARK_TEST_TRUE(true);
        DARK_TEST_FALSE(false);

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

        DARK_TEST_EQ_F(-1.0f, 1.0f - 2.0f);
        DARK_TEST_NE_F(2.0f, 1.0f);
        DARK_TEST_LT_F(1.0f, 2.0f);
        DARK_TEST_LE_F(1.0f, 1.0f);
        DARK_TEST_LE_F(1.0f, 2.0f);
        DARK_TEST_GT_F(2.0f, 1.0f);
        DARK_TEST_GE_F(2.0f, 2.0f);
        DARK_TEST_GE_F(2.0f, 1.0f);
        DARK_TEST_EQ_F(2.0f, 2.0f + FLT_EPSILON);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
