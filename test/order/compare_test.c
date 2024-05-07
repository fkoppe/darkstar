#include <dark/darkstar.h>

int main()
{
    //----------TEST----------
    DARK_TEST("compare_i8")
    {
        const int8_t a = 12;
        const int8_t b = -12;

        DARK_TEST_EQ_I(dark_compare_i8(&b, &b), 0);

        DARK_TEST_EQ_I(dark_compare_i8(&a, &b), 1);
        DARK_TEST_EQ_I(dark_compare_i8(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_i16")
    {
        const int16_t a = 12;
        const int16_t b = -12;

        DARK_TEST_EQ_I(dark_compare_i16(&b, &b), 0);

        DARK_TEST_EQ_I(dark_compare_i16(&a, &b), 1);
        DARK_TEST_EQ_I(dark_compare_i16(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_i32")
    {
        const int32_t a = 12;
        const int32_t b = -12;

        DARK_TEST_EQ_I(dark_compare_i32(&b, &b), 0);

        DARK_TEST_EQ_I(dark_compare_i32(&a, &b), 1);
        DARK_TEST_EQ_I(dark_compare_i32(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_i64")
    {
        const int64_t a = 12;
        const int64_t b = -12;

        DARK_TEST_EQ_I(dark_compare_i64(&b, &b), 0);

        DARK_TEST_EQ_I(dark_compare_i64(&a, &b), 1);
        DARK_TEST_EQ_I(dark_compare_i64(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_u8")
    {
        const uint8_t a = 12;
        const uint8_t b = 7;

        DARK_TEST_EQ_U(dark_compare_u8(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_u8(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_u8(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_u16")
    {
        const uint16_t a = 12;
        const uint16_t b = 7;

        DARK_TEST_EQ_U(dark_compare_u16(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_u16(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_u16(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_u32")
    {
        const uint32_t a = 12;
        const uint32_t b = 7;

        DARK_TEST_EQ_U(dark_compare_u32(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_u32(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_u32(&b, &a), -1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("compare_u64")
    {
        const uint64_t a = 1255555;
        const uint64_t b = 7;

        DARK_TEST_EQ_U(dark_compare_u64(&b, &b), 0);

        DARK_TEST_EQ_U(dark_compare_u64(&a, &b), 1);
        DARK_TEST_EQ_U(dark_compare_u64(&b, &a), -1);
    }
    //--------------------------

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

    dark_test_end();

    return DARK_EXIT_SUCCESS;
}
