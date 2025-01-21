#include <dark/darkstar.h>
#include <dark/darktest.h>

#include "math.h"

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("fmath")
    {
        DARK_TEST_EQ_F(sinf(0.0f), dark_sin_f(0.0f));
        DARK_TEST_EQ_F(cosf(0.0f), dark_cos_f(0.0f));
        DARK_TEST_EQ_F(tanf(0.0f), dark_tan_f(0.0f));
        DARK_TEST_EQ_F(asinf(0.5f), dark_asin_f(0.5f));
        DARK_TEST_EQ_F(acosf(0.5f), dark_acos_f(0.5f));
        DARK_TEST_EQ_F(atanf(1.0f), dark_atan_f(1.0f));

        DARK_TEST_EQ_F(expf(1.0f), dark_exp_f(1.0f));
        DARK_TEST_EQ_F(exp2f(2.0f), dark_exp2_f(2.0f));
        DARK_TEST_EQ_F(logf(10.0f), dark_log_f(10.0f));
        DARK_TEST_EQ_F(log10f(100.0f), dark_log10_f(100.0f));

        DARK_TEST_EQ_F(powf(2.0f, 3.0f), dark_pow_f(2.0f, 3.0f));
        DARK_TEST_EQ_F(sqrtf(16.0f), dark_sqrt_f(16.0f));

        DARK_TEST_EQ_F(fabsf(-5.5f), dark_abs_f(-5.5f));
        DARK_TEST_EQ_F(fmodf(7.5f, 2.0f), dark_mod_f(7.5f, 2.0f));

        DARK_TEST_EQ_F(ceilf(5.4f), dark_ceil_f(5.4f));
        DARK_TEST_EQ_F(floorf(5.4f), dark_floor_f(5.4f));
        DARK_TEST_EQ_F(roundf(5.4f), dark_round_f(5.4f));

        DARK_TEST_TRUE(isnan(NAN));
        DARK_TEST_TRUE(isfinite(3.14f));

        DARK_TEST_FALSE(dark_range_is_f(111.0f, 5.0f, 9.9f));
        DARK_TEST_EQ_F(dark_range_clamp_f(111.0f, 5.0f, 9.9f), 9.9f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("compare_f")
    {
        const float a = 12.1;
        const float b = -12.1;

        DARK_TEST_EQ_U(dark_compare_f(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_f(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_f(&b, &a), -1);
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
