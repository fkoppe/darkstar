#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("vec_2f_create/_x/_y")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(-1.0f, 1.0f);
        DARK_TEST_EQ_F(dark_vec_2f_x(vec), -1.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(vec), 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_zero")
    {
        Dark_Vec_2f vec = dark_vec_2f_zero();
        DARK_TEST_EQ_F(dark_vec_2f_x(vec), 0.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(vec), 0.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_add")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        Dark_Vec_2f result = dark_vec_2f_add(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_2f_x(result), 4.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(result), 6.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_sub")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(5.0f, 6.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        Dark_Vec_2f result = dark_vec_2f_sub(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_2f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(result), 2.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_mult")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f result = dark_vec_2f_mult(vec, 2.0f);

        DARK_TEST_EQ_F(dark_vec_2f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(result), 4.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_div")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(4.0f, 8.0f);
        Dark_Vec_2f result = dark_vec_2f_div(vec, 2.0f);

        DARK_TEST_EQ_F(dark_vec_2f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(result), 4.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_normalize")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(3.0f, 4.0f);
        Dark_Vec_2f normalized = dark_vec_2f_normalize(vec);

        float length = dark_vec_2f_lenght_f(normalized);
        DARK_TEST_EQ_F(length, 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_perpendicular")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f perp = dark_vec_2f_perpendicular(vec);

        DARK_TEST_EQ_F(dark_vec_2f_x(perp), -2.0f);
        DARK_TEST_EQ_F(dark_vec_2f_y(perp), 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_dot_f")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        float result = dark_vec_2f_dot_f(vec1, vec2);

        DARK_TEST_EQ_F(result, 11.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_cross_f")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        float result = dark_vec_2f_cross(vec1, vec2);

        DARK_TEST_EQ_F(result, -2.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_angle_f")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 0.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(0.0f, 1.0f);
        float result = dark_vec_2f_angle_f(vec1, vec2);

        DARK_TEST_EQ_F(result, DARK_PI_DIV_2);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_lenght_f")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(3.0f, 4.0f);
        float length = dark_vec_2f_lenght_f(vec);

        DARK_TEST_EQ_F(length, 5.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_dot_d")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        double result = dark_vec_2f_dot_d(vec1, vec2);

        DARK_TEST_EQ_D(result, 11.0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_cross_d")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 2.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(3.0f, 4.0f);
        double result = dark_vec_2f_cross(vec1, vec2);

        DARK_TEST_EQ_D(result, -2.0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_angle_f")
    {
        Dark_Vec_2f vec1 = dark_vec_2f_create(1.0f, 0.0f);
        Dark_Vec_2f vec2 = dark_vec_2f_create(0.0f, 1.0f);
        float result = dark_vec_2f_angle_d(vec1, vec2);

        DARK_TEST_EQ_F(result, DARK_PI_DIV_2);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_2f_lenght_d")
    {
        Dark_Vec_2f vec = dark_vec_2f_create(3.0f, 4.0f);
        double length = dark_vec_2f_lenght_d(vec);

        DARK_TEST_EQ_D(length, 5.0);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
