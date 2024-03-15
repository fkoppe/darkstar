#include <dark/darkstar.h>

void va_helper(char* const buffer, const size_t count, const char* const format, ...)
{
    va_list args;
    va_start(args, format);
    const size_t result = dark_cbuffer_vsnprintf(buffer, count, format, args);
    va_end(args);
}

int main()
{
    //----------TEST#1----------
    DARK_TEST("cbuffer_terminated_is")
    {
        char cbuffer[16] = "merry christmas";

        size_t lenght = 0;
        DARK_TEST(dark_cbuffer_terminated_is(16, cbuffer, &lenght));

        //16 - 1 because of '\0' not being counted for lenght
        DARK_TEST_EQ_U(lenght, 16 - 1);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("cbuffer_snprintf")
    {
        //14 + 1 for '\0'
        char cbuffer[14 + 1] = {0};
        cbuffer[14] = '\0';

        DARK_TEST_EQ_U(14, dark_cbuffer_snprintf(cbuffer, 0, "hello %s %i", "world", 11));

        DARK_TEST_EQ_S(cbuffer, "hello world 11", 15);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("cbuffer_vsnprintf")
    {
        //14 + 1 for '\0'
        char cbuffer[14+1];
        cbuffer[14] = '\0';

        va_helper(cbuffer, 14+1, "hello %s %i", "world", 11);

        DARK_TEST_EQ_S(cbuffer, "hello world 11", 15);
    }
    //--------------------------

    return EXIT_SUCCESS;
}
