#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("vec_3f_create/_x/_y/_z")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(-1.0f, 1.0f, 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_x(vec), -1.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(vec), 1.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(vec), 2.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_zero")
    {
        Dark_Vec_3f vec = dark_vec_3f_zero();
        DARK_TEST_EQ_F(dark_vec_3f_x(vec), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(vec), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(vec), 0.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_add")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(4.0f, 5.0f, 6.0f);
        Dark_Vec_3f result = dark_vec_3f_add(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 5.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 7.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 9.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_sub")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(5.0f, 6.0f, 7.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(3.0f, 4.0f, 5.0f);
        Dark_Vec_3f result = dark_vec_3f_sub(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 2.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_mult")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f result = dark_vec_3f_mult(vec, 2.0f);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 4.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 6.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_div")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(4.0f, 8.0f, 12.0f);
        Dark_Vec_3f result = dark_vec_3f_div(vec, 2.0f);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 4.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 6.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_normalize")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(3.0f, 4.0f, 12.0f);
        Dark_Vec_3f normalized = dark_vec_3f_normalize(vec);

        float length = dark_vec_3f_lenght_f(normalized);
        DARK_TEST_EQ_F(length, 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_perpendicular")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f perp = dark_vec_3f_perpendicular(vec);

        DARK_TEST_EQ_F(dark_vec_3f_angle_f(vec, perp), DARK_PI_DIV_2);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_dot_f")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(4.0f, 5.0f, 6.0f);
        float result = dark_vec_3f_dot_f(vec1, vec2);

        DARK_TEST_EQ_F(result, 32.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_cross_f")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(0.0f, 1.0f, 0.0f);
        Dark_Vec_3f result = dark_vec_3f_cross(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_angle_f")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(0.0f, 1.0f, 0.0f);
        float result = dark_vec_3f_angle_f(vec1, vec2);

        DARK_TEST_EQ_F(result, DARK_PI_DIV_2);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_lenght_f")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(3.0f, 4.0f, 12.0f);
        float length = dark_vec_3f_lenght_f(vec);

        DARK_TEST_EQ_F(length, 13.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_dot_d")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(4.0f, 5.0f, 6.0f);
        double result = dark_vec_3f_dot_d(vec1, vec2);

        DARK_TEST_EQ_D(result, 32.0);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_cross_d")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(0.0f, 1.0f, 0.0f);
        Dark_Vec_3f result = dark_vec_3f_cross(vec1, vec2);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 0.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 1.0f);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_angle_d")
    {
        Dark_Vec_3f vec1 = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f vec2 = dark_vec_3f_create(0.0f, 1.0f, 0.0f);
        float result = dark_vec_3f_angle_d(vec1, vec2);

        DARK_TEST_EQ_D(result, DARK_PI_DIV_2);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("vec_3f_lenght_d")
    {
        Dark_Vec_3f vec = dark_vec_3f_create(3.0f, 4.0f, 12.0f);
        double length = dark_vec_3f_lenght_d(vec);

        DARK_TEST_EQ_D(length, 13.0);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
