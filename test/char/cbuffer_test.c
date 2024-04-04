#include <dark/darkstar.h>

void va_helper(const size_t count_, char* const destination_, const char* const format_, ...)
{
    DARK_ASSERT((0 == count_) || (NULL != destination_), DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    const size_t result = dark_cbuffer_vsnprintf(count_, destination_, format_, args);
    va_end(args);
}

int main()
{
    //----------TEST#1----------
    DARK_TEST("cbuffer_terminated_is")
    {
        char cbuffer[16] = "merry christmas";

        size_t lenght = 0;
        DARK_TEST_TRUE(dark_cbuffer_terminated_is(16, cbuffer, &lenght));

        //16 - 1 because of '\0' not being counted for lenght
        DARK_TEST_EQ_U(lenght, 16 - 1);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("cbuffer_snprintf")
    {
        //14 + 1 for '\0'
        char cbuffer[14 + 1] = { 0 };
        cbuffer[14] = '\0';

        DARK_TEST_EQ_U(14, dark_cbuffer_snprintf(0, NULL, "hello %s %i", "world", 11));
        dark_cbuffer_snprintf(14 + 1, cbuffer, "hello %s %i", "world", 11);

        DARK_TEST_EQ_S(cbuffer, "hello world 11", 15);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("cbuffer_vsnprintf")
    {
        //14 + 1 for '\0'
        char cbuffer[14+1] = { 0 };
        cbuffer[14] = '\0';

        va_helper(14+1, cbuffer, "hello %s %i", "world", 11);

        DARK_TEST_EQ_S(cbuffer, "hello world 11", 15);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("cbuffer_snprintf negative")
    {
        //14 + 1 for '\0'
        char cbuffer[2 + 1] = {0};
        cbuffer[2] = '\0';

        DARK_TEST_EQ_U(2, dark_cbuffer_snprintf(0, NULL, "%i", -1));
        dark_cbuffer_snprintf(2 + 1, cbuffer, "%i", -1);

        DARK_TEST_EQ_S(cbuffer, "-1", 3);
    }
    //--------------------------

    //----------TEST#5----------
    DARK_TEST("cbuffer_compare")
    {
        DARK_TEST_EQ_U(0, dark_cbuffer_compare("abcd", "abcd", 4));
        DARK_TEST_NE_U(0, dark_cbuffer_compare("abcdy", "abcdx", 5));
    }
    //--------------------------

    dark_test_end();

    return EXIT_SUCCESS;
}
