#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("growth_simple")
    {
        DARK_TEST_EQ_U(dark_growth_simple(0, 0), 0);
        DARK_TEST_EQ_U(dark_growth_simple(1, 0), 0);
        DARK_TEST_EQ_U(dark_growth_simple(1, 1), 0);
        DARK_TEST_EQ_U(dark_growth_simple(10, 20), 10);
        DARK_TEST_EQ_U(dark_growth_simple(100, 101), 1);
        DARK_TEST_EQ_U(dark_growth_simple(10, 5), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("growth_standard")
    {
        DARK_TEST_EQ_U(dark_growth_standard(0, 0), 0);
        DARK_TEST_EQ_U(dark_growth_standard(1, 0), 0);
        DARK_TEST_EQ_U(dark_growth_standard(1, 1), 0);
        DARK_TEST_EQ_U(dark_growth_standard(10, 20), 12);
        DARK_TEST_EQ_U(dark_growth_standard(100, 101), 50);
        DARK_TEST_EQ_U(dark_growth_standard(10, 5), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("growth_exponential")
    {
        DARK_TEST_EQ_U(dark_growth_exponential(0, 0), 0);
        DARK_TEST_EQ_U(dark_growth_exponential(1, 0), 0);
        DARK_TEST_EQ_U(dark_growth_exponential(1, 1), 0);
        DARK_TEST_EQ_U(dark_growth_exponential(10, 20),10);
        DARK_TEST_EQ_U(dark_growth_exponential(100, 101), 100);
        DARK_TEST_EQ_U(dark_growth_exponential(10, 5), 0);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
