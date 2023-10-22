#include <dark/darkstar.h>

int main()
{
    DARK_TEST_UINT(dark_ppow_uint(112, 0) == 1, dark_ppow_uint(112, 0));
    DARK_TEST_UINT(dark_ppow_uint(112, 1) == 112, dark_ppow_uint(112, 1));
    DARK_TEST_UINT(dark_ppow_uint(2, 2) == 4, dark_ppow_uint(2, 2));
    DARK_TEST_UINT(dark_ppow_uint(2, 3) == 8, dark_ppow_uint(2, 3));
    DARK_TEST_UINT(dark_ppow_uint(0, 3) == 0, dark_ppow_uint(0, 3));

    DARK_TEST_INT(dark_ppow_int(-112, 0) == 1, dark_ppow_int(-112, 0));
    DARK_TEST_INT(dark_ppow_int(-112, 1) == -112, dark_ppow_int(-112, 1));
    DARK_TEST_INT(dark_ppow_int(-2, 2) == 4, dark_ppow_int(-2, 2));
    DARK_TEST_INT(dark_ppow_int(-2, 3) == -8, dark_ppow_int(-2, 3));
    DARK_TEST_UINT(dark_ppow_int(0, 3) == 0, dark_ppow_int(0, 3));

    return EXIT_SUCCESS;
}
