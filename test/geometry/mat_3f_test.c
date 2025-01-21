#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    DARK_TEST("mat_3f_create/_get/_compare")
    {
        Dark_Vec_3f col1 = dark_vec_3f_create(1.0f, 0.0f, 0.0f);
        Dark_Vec_3f col2 = dark_vec_3f_create(0.0f, 1.0f, 0.0f);
        Dark_Vec_3f col3 = dark_vec_3f_create(0.0f, 0.0f, 1.0f);
        Dark_Mat_3f mat = dark_mat_3f_create(col1, col2, col3);

        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 0, 0), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 1, 1), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 2, 2), 1.0f);

        DARK_TEST_TRUE(dark_mat_3f_compare(&mat, &mat) == 0);
    }

    DARK_TEST("mat_3f_identity")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 0, 0), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 1, 1), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 2, 2), 1.0f);
    }

    DARK_TEST("mat_3f_zero")
    {
        Dark_Mat_3f mat = dark_mat_3f_zero();
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 0, 0), 0.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 1, 1), 0.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 2, 2), 0.0f);
    }

    DARK_TEST("mat_3f_set")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        mat = dark_mat_3f_set(mat, 0, 1, 2.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(mat, 0, 1), 2.0f);
    }

    DARK_TEST("mat_3f_add")
    {
        Dark_Mat_3f mat1 = dark_mat_3f_identity();
        Dark_Mat_3f mat2 = dark_mat_3f_identity();
        Dark_Mat_3f result = dark_mat_3f_add(mat1, mat2);

        DARK_TEST_EQ_F(dark_mat_3f_get(result, 0, 0), 2.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 1, 1), 2.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 2, 2), 2.0f);
    }

    DARK_TEST("mat_3f_sub")
    {
        Dark_Mat_3f mat1 = dark_mat_3f_identity();
        Dark_Mat_3f mat2 = dark_mat_3f_identity();
        Dark_Mat_3f result = dark_mat_3f_sub(mat1, mat2);

        DARK_TEST_EQ_F(dark_mat_3f_get(result, 0, 0), 0.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 1, 1), 0.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 2, 2), 0.0f);
    }

    DARK_TEST("mat_3f_mult_scalar")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        Dark_Mat_3f result = dark_mat_3f_mult(mat, 2.0f);

        DARK_TEST_EQ_F(dark_mat_3f_get(result, 0, 0), 2.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 1, 1), 2.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 2, 2), 2.0f);
    }

    DARK_TEST("mat_3f_mult_vec")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        Dark_Vec_3f vec = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f result = dark_mat_3f_mult_vec(mat, vec);

        DARK_TEST_EQ_F(dark_vec_3f_x(result), 1.0f);
        DARK_TEST_EQ_F(dark_vec_3f_y(result), 2.0f);
        DARK_TEST_EQ_F(dark_vec_3f_z(result), 3.0f);
    }

    DARK_TEST("mat_3f_mult_mat")
    {
        Dark_Mat_3f mat1 = dark_mat_3f_identity();
        Dark_Mat_3f mat2 = dark_mat_3f_identity();
        Dark_Mat_3f result = dark_mat_3f_mult_mat(mat1, mat2);

        DARK_TEST_EQ_F(dark_mat_3f_get(result, 0, 0), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 1, 1), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 2, 2), 1.0f);
    }

    DARK_TEST("mat_3f_transpose")
    {
        Dark_Vec_3f col1 = dark_vec_3f_create(1.0f, 2.0f, 3.0f);
        Dark_Vec_3f col2 = dark_vec_3f_create(4.0f, 5.0f, 6.0f);
        Dark_Vec_3f col3 = dark_vec_3f_create(7.0f, 8.0f, 9.0f);

        Dark_Mat_3f mat = dark_mat_3f_create(col1, col2, col3);

        Dark_Vec_3f row1 = dark_mat_3f_row(mat, 0);
        Dark_Vec_3f row2 = dark_mat_3f_row(mat, 1);
        Dark_Vec_3f row3 = dark_mat_3f_row(mat, 2);

        Dark_Mat_3f mat_t = dark_mat_3f_create(row1, row2, row3);

        Dark_Mat_3f result = dark_mat_3f_transpose(mat);

        DARK_TEST_EQ_I(0, dark_mat_3f_compare(&mat_t, &result));
        DARK_TEST_EQ_I(0, dark_mat_3f_compare(&mat_t, &result));
    }

    DARK_TEST("mat_3f_determinant")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        float determinant = dark_mat_3f_determinant(mat);

        DARK_TEST_EQ_F(determinant, 1.0f);
    }

    DARK_TEST("mat_3f_invert_is")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        bool invertible = dark_mat_3f_invert_is(mat);

        DARK_TEST_TRUE(invertible);
    }

    DARK_TEST("mat_3f_invert")
    {
        Dark_Mat_3f mat = dark_mat_3f_identity();
        Dark_Mat_3f result = dark_mat_3f_invert(mat);

        DARK_TEST_EQ_F(dark_mat_3f_get(result, 0, 0), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 1, 1), 1.0f);
        DARK_TEST_EQ_F(dark_mat_3f_get(result, 2, 2), 1.0f);
    }

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
