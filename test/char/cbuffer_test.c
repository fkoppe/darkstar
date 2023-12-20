#include "dark/char/cbuffer.h"
#include <dark/darkstar.h>

void sprint(char* const buffer, const size_t count, const char* const format, ...)
{
    va_list args;
    va_start(args, format);
    const size_t result = dark_cbuffer_vsnprintf(buffer, count, format, args);
    va_end(args);
}

int main()
{
    char some[16] = "merry christmas";
    DARK_TEST_EQ_U(15, dark_cbuffer_lenght(some, 16));

    DARK_TEST_EQ_U(14, dark_cbuffer_snprintf(NULL, 0, "hello %s %i", "world", 11));

    char buffer[14+1]; //additional character \n
    sprint(buffer, 14+1, "hello %s %i", "world", 11);

    DARK_TEST_EQ_S("hello world 11", buffer, 14+1);

    return EXIT_SUCCESS;
}
