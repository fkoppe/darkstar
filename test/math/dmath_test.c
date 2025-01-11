#include <dark/darkstar.h>
#include <dark/darktest.h>

#include "math.h"

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("dmath")
    {
        DARK_TEST_EQ_F(sin(0.0f), dark_sin_d(0.0f));
        DARK_TEST_EQ_F(cos(0.0f), dark_cos_d(0.0f));
        DARK_TEST_EQ_F(tan(0.0f), dark_tan_d(0.0f));
        DARK_TEST_EQ_F(asin(0.5f), dark_asin_d(0.5f));
        DARK_TEST_EQ_F(acos(0.5f), dark_acos_d(0.5f));
        DARK_TEST_EQ_F(atan(1.0f), dark_atan_d(1.0f));

        DARK_TEST_EQ_F(exp(1.0f), dark_exp_d(1.0f));
        DARK_TEST_EQ_F(exp2(2.0f), dark_exp2_d(2.0f));
        DARK_TEST_EQ_F(log(10.0f), dark_log_d(10.0f));
        DARK_TEST_EQ_F(log10(100.0f), dark_log10_d(100.0f));

        DARK_TEST_EQ_F(pow(2.0f, 3.0f), dark_pow_d(2.0f, 3.0f));
        DARK_TEST_EQ_F(sqrt(16.0f), dark_sqrt_d(16.0f));

        DARK_TEST_EQ_F(fabs(-5.5f), dark_abs_d(-5.5f));
        DARK_TEST_EQ_F(fmod(7.5f, 2.0f), dark_mod_d(7.5f, 2.0f));

        DARK_TEST_EQ_F(ceil(5.4f), dark_ceil_d(5.4f));
        DARK_TEST_EQ_F(floor(5.4f), dark_dloor_d(5.4f));
        DARK_TEST_EQ_F(round(5.4f), dark_round_d(5.4f));

        DARK_TEST_TRUE(isnan(NAN));
        DARK_TEST_TRUE(isfinite(3.14f));
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
