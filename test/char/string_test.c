#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    char cbuffer[] = "moin";

    void* string1 = dark_string_new_f(DARK_GROWTH_STANDARD, "%i.%i", 3, 1415);
    void* string2 = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, cbuffer, 4);
    void* string3 = dark_string_new_char(DARK_GROWTH_STANDARD, 'x');
    void* string4 = dark_string_new_size(DARK_GROWTH_STANDARD, 10, 0);

    DARK_TEST_EQ_S("3.1415", dark_string_cbuffer(string1), 7);
    DARK_TEST_EQ_S("moin", dark_string_cbuffer(string2), 5);
    DARK_TEST_EQ_S("x", dark_string_cbuffer(string3), 2);
    DARK_TEST_EQ_S("", dark_string_cbuffer(string4), 1);

    dark_string_append_f(string1, " abcdefg");
    dark_string_append_f(string2, "%s%f", "hahaha", 0.02f);
    dark_string_push_f(string3, 0, "1");
    dark_string_push_f(string3, 2, "wlan");
    dark_string_push_f(string4, 0, "");

    DARK_TEST_EQ_S("3.1415 abcdefg", dark_string_cbuffer(string1), 7+8);
    DARK_TEST_EQ_S("moinhahaha0.02", dark_string_cbuffer(string2), 14);
    DARK_TEST_EQ_S("1xwlan", dark_string_cbuffer(string3), 7);
    DARK_TEST_EQ_S("", dark_string_cbuffer(string4), 1);

    dark_string_push_cbuffer(string1, 2, "nope", 4);
    dark_string_prepend_f(string2, "%i", 22);
    DARK_TEST_EQ_S("3.nope1415 abcdefg", dark_string_cbuffer(string1), 7+8+4);
    DARK_TEST_EQ_S("22moinhahaha0.02", dark_string_cbuffer(string2), 14+2);

    dark_string_pop_front(string1);
    DARK_TEST_EQ_S(".nope1415 abcdefg", dark_string_cbuffer(string1), 7+8+3);

    dark_string_pop_back(string1);
    DARK_TEST_EQ_S(".nope1415 abcdef", dark_string_cbuffer(string1), 7+8+2);

    dark_string_delete(string1);
    dark_string_delete(string2);
    dark_string_delete(string3);
    dark_string_delete(string4);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
