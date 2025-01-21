#include <dark/darkstar.h>
#include <dark/darktest.h>

#include "math.h"

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("dmath")
    {
        DARK_TEST_EQ_F(sin(0.0), dark_sin_d(0.0));
        DARK_TEST_EQ_F(cos(0.0), dark_cos_d(0.0));
        DARK_TEST_EQ_F(tan(0.0), dark_tan_d(0.0));
        DARK_TEST_EQ_F(asin(0.5), dark_asin_d(0.5));
        DARK_TEST_EQ_F(acos(0.5), dark_acos_d(0.5));
        DARK_TEST_EQ_F(atan(1.0), dark_atan_d(1.0));

        DARK_TEST_EQ_F(exp(1.0), dark_exp_d(1.0));
        DARK_TEST_EQ_F(exp2(2.0), dark_exp2_d(2.0));
        DARK_TEST_EQ_F(log(10.0), dark_log_d(10.0));
        DARK_TEST_EQ_F(log10(100.0), dark_log10_d(100.0));

        DARK_TEST_EQ_F(pow(2.0, 3.0), dark_pow_d(2.0, 3.0));
        DARK_TEST_EQ_F(sqrt(16.0), dark_sqrt_d(16.0));

        DARK_TEST_EQ_F(fabs(-5.5), dark_abs_d(-5.5));
        DARK_TEST_EQ_F(fmod(7.5, 2.0), dark_mod_d(7.5, 2.0));

        DARK_TEST_EQ_F(ceil(5.4), dark_ceil_d(5.4));
        DARK_TEST_EQ_F(floor(5.4), dark_dloor_d(5.4));
        DARK_TEST_EQ_F(round(5.4), dark_round_d(5.4));

        DARK_TEST_TRUE(isnan(NAN));
        DARK_TEST_TRUE(isfinite(3.14));

        DARK_TEST_FALSE(dark_range_is_d(111.0, 5.0, 9.9));
        DARK_TEST_EQ_F(dark_range_clamp_d(111.0, 5.0, 9.9), 9.9);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("compare_d")
    {
        const double a = 12.1;
        const double b = -12.1;

        DARK_TEST_EQ_U(dark_compare_d(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_d(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_d(&b, &a), -1);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
