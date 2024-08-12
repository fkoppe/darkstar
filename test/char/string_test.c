#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/char/string_struct.h>

void va_construct_helper(Dark_Allocator* const allocator_, Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    dark_string_construct_v(allocator_, string_, dark_growth_standard, format_, args);
    va_end(args);
}

void* va_new_helper(Dark_Allocator* const allocator_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != allocator_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    void* const result = dark_string_new_v(allocator_, dark_growth_standard, format_, args);
    va_end(args);

    return result;
}

void va_push_helper(Dark_String* const string_, const size_t index_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(index_ <= dark_string_size(string_), DARK_ERROR_CONTAINER_INDEX);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    dark_string_push_v(string_, index_, format_, args);
    va_end(args);
}

void va_append_helper(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    dark_string_append_v(string_, format_, args);
    va_end(args);
}

void va_prepend_helper(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    dark_string_prepend_v(string_, format_, args);
    va_end(args);
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("string_construct_va/_destruct")
    {
        Dark_String* const string = dark_malloc(allocator, sizeof(*string));;

        va_construct_helper(allocator, string, "hello %s %i", "world", -11);

        DARK_TEST_EQ_U(dark_string_capacity(string), 15);
        DARK_TEST_EQ_U(dark_string_size(string), 15);

        DARK_TEST_EQ_S(dark_string_cstring(string), "hello world -11", 16);

        dark_string_destruct(string);

        dark_free(allocator, string, sizeof(*string));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_construct")
    {
        Dark_String* const string = dark_malloc(allocator, sizeof(*string));;

        dark_string_construct_f(allocator, string, dark_growth_simple, "%i", 1);
        dark_string_destruct(string);

        dark_string_construct_cstring(allocator, string, dark_growth_simple, "a cstring");
        dark_string_destruct(string);

        const Dark_Cbuffer_View cbuffer_view = dark_cstring_to_cbuffer_view("another");
        dark_string_construct_cbuffer_view(allocator, string, dark_growth_simple, cbuffer_view);
        dark_string_destruct(string);

        dark_string_construct_char(allocator, string, dark_growth_simple, 'x');
        dark_string_destruct(string);

        dark_string_construct_size(allocator, string, dark_growth_simple, 10, 1);
        dark_string_destruct(string);

        dark_string_construct_capacity(allocator, string, dark_growth_simple, 1);
        dark_string_destruct(string);

        dark_string_construct(allocator, string, dark_growth_simple);
        dark_string_destruct(string);

        dark_free(allocator, string, sizeof(*string));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_new_v/_delete")
    {
        Dark_String* const string = va_new_helper(allocator, "hello %s %i", "from", -123);

        DARK_TEST_EQ_S(dark_string_cstring(string), "hello from -123", 16);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_new")
    {
        Dark_String* string;

        string = dark_string_new_f(allocator, dark_growth_exponential, "%f", 0.0000001f);
        dark_string_delete(string);

        string = dark_string_new_cstring(allocator, dark_growth_exponential, "c");
        dark_string_delete(string);

        const Dark_Cbuffer_View cbuffer_view = dark_cstring_to_cbuffer_view("another");
        string = dark_string_new_cbuffer_view(allocator, dark_growth_exponential, cbuffer_view);
        dark_string_delete(string);

        string = dark_string_new_char(allocator, dark_growth_exponential, 'a');
        dark_string_delete(string);

        string = dark_string_new_size(allocator, dark_growth_exponential, 9, 9);
        dark_string_delete(string);

        string = dark_string_new_capacity(allocator, dark_growth_exponential, 1000);
        dark_string_delete(string);

        string = dark_string_new(allocator, dark_growth_exponential);
        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_at/_capacity/_size")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_at(string, 0), 'a');
        DARK_TEST_EQ_I(dark_string_at(string, 1), 'b');
        DARK_TEST_EQ_I(dark_string_at(string, 2), 'c');
        DARK_TEST_EQ_I(dark_string_at(string, 3), 'd');
        DARK_TEST_EQ_I(dark_string_at(string, 4), 'e');

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_front")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_front(string), 'a');

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_back")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_back(string), 'e');

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_cstring")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xyz", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_substring")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_subcstring(string, 0), "xyz", 4);
        DARK_TEST_EQ_S(dark_string_subcstring(string, 1), "yz", 3);
        DARK_TEST_EQ_S(dark_string_subcstring(string, 2), "z", 2);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_cbuffer")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer cbuffer = dark_string_cbuffer(string);

        DARK_TEST_EQ_U(cbuffer.size, 3);
        DARK_TEST_EQ_S(cbuffer.data, "xyz", cbuffer.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_subcbuffer")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer cbuffer = dark_string_subcbuffer(string, 2);

        DARK_TEST_EQ_U(cbuffer.size, 1);
        DARK_TEST_EQ_S(cbuffer.data, "z", cbuffer.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_cbuffer_view")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer_View cbuffer_view = dark_string_cbuffer_view(string);

        DARK_TEST_EQ_U(cbuffer_view.size, 3);
        DARK_TEST_EQ_S(cbuffer_view.data, "xyz", cbuffer_view.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_cbuffer_view_terminated")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer_View cbuffer_view = dark_string_cbuffer_view_terminated(string);

        DARK_TEST_EQ_U(cbuffer_view.size, 4);
        DARK_TEST_EQ_S(cbuffer_view.data, "xyz", cbuffer_view.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_subcbuffer_view")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer_View cbuffer_view = dark_string_subcbuffer_view(string, 1);

        DARK_TEST_EQ_U(cbuffer_view.size, 2);
        DARK_TEST_EQ_S(cbuffer_view.data, "yz", cbuffer_view.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_subcbuffer_view_terminated")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer_View cbuffer_view = dark_string_subcbuffer_view_terminated(string, 1);

        DARK_TEST_EQ_U(cbuffer_view.size, 3);
        DARK_TEST_EQ_S(cbuffer_view.data, "yz", cbuffer_view.size);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        char* destination = dark_string_emplace(string, 0, 5);
        destination[0] = '3';
        destination[1] = '1';
        destination[2] = '2';
        destination[3] = '5';
        destination[4] = '4';

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "31254", 6);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_front")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        char* destination = dark_string_emplace_front(string, 5);
        destination[0] = '3';
        destination[1] = '1';
        destination[2] = '2';
        destination[3] = '5';
        destination[4] = '4';

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "31254", 6);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_back")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        char* destination = dark_string_emplace_back(string, 5);
        destination[0] = '3';
        destination[1] = '1';
        destination[2] = '2';
        destination[3] = '5';
        destination[4] = '4';

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "31254", 6);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_cbuffer")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        const Dark_Cbuffer cbuffer = dark_string_emplace_cbuffer(string, 0, 3);
        dark_digit_write_u(123, 3, cbuffer);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "123", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_cbuffer_front")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        const Dark_Cbuffer cbuffer = dark_string_emplace_cbuffer_front(string, 3);
        dark_digit_write_u(123, 3, cbuffer);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "123", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_cbuffer_back")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        const Dark_Cbuffer cbuffer = dark_string_emplace_cbuffer_back(string, 3);
        dark_digit_write_u(123, 3, cbuffer);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "123", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace(string, 2);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abxc", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_front")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace_front(string);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xabc", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_back")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace_back(string);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abcx", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_cbuffer")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer cbuffer = dark_string_inplace_cbuffer(string, 2);
        *cbuffer.data = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abxc", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_cbuffer_front")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer cbuffer = dark_string_inplace_cbuffer_front(string);
        *cbuffer.data = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xabc", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_cbuffer_back")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        const Dark_Cbuffer cbuffer = dark_string_inplace_cbuffer_back(string);
        *cbuffer.data = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abcx", 5);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_push_v")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        va_push_helper(string, 0, "%i", 1);
        va_push_helper(string, 1, "%i", 2);
        va_push_helper(string, 0, "%i", 3);
        va_push_helper(string, 3, "%i", 4);
        va_push_helper(string, 3, "%i", 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "31254", 6);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_push_f")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_push_f(string, 0, "%i", 1);
        dark_string_push_f(string, 1, "%i", 2);
        dark_string_push_f(string, 0, "%i", 3);
        dark_string_push_f(string, 3, "%i", 4);
        dark_string_push_f(string, 3, "%i", 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "31254", 6);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_push_cstring")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_push_cstring(string, 0, "abc");
        dark_string_push_cstring(string, 1, "XY");
        dark_string_push_cstring(string, 0, "...");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "...aXYbc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_push_cbuffer_view")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_push_cbuffer_view(string, 0, dark_cstring_to_cbuffer_view("abc"));
        dark_string_push_cbuffer_view(string, 1, dark_cstring_to_cbuffer_view("XY"));
        dark_string_push_cbuffer_view(string, 0, dark_cstring_to_cbuffer_view("..."));

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "...aXYbc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_append_v")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        va_append_helper(string, "noo%s", "cap");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "ccnoocap", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_append_f")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_append_f(string, "noo%s", "cap");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "ccnoocap", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_append_cstring")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_append_cstring(string, "hell");
        dark_string_append_cstring(string, "no");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "cchellno", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_append_cbuffer_view")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_append_cbuffer_view(string, dark_cstring_to_cbuffer_view("hell"));
        dark_string_append_cbuffer_view(string, dark_cstring_to_cbuffer_view("no"));

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "cchellno", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_v")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        va_prepend_helper(string, "noo%s", "cap");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "noocapcc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_f")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_prepend_f(string, "noo%s", "cap");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "noocapcc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_cstring")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_prepend_cstring(string, "hell");
        dark_string_prepend_cstring(string, "no");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "nohellcc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_cbuffer_view")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_prepend_cbuffer_view(string, dark_cstring_to_cbuffer_view("hell"));
        dark_string_prepend_cbuffer_view(string, dark_cstring_to_cbuffer_view("no"));

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "nohellcc", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_insert")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert(string, 0, 'a');
        dark_string_insert(string, 0, 'b');
        dark_string_insert(string, 0, 'c');
        dark_string_insert(string, 0, 'd');
        dark_string_insert(string, 0, 'e');

        DARK_TEST_GE_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "edcba", 6);

        dark_string_insert(string, 5, '.');
        dark_string_insert(string, 6, '-');
        dark_string_insert(string, 5, '.');

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cstring(string), "edcba..-", 9);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_insert_front")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 0);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert_back(string, 'a');
        dark_string_insert_back(string, 'b');
        dark_string_insert_back(string, 'x');

        DARK_TEST_GE_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abx", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_insert_back")
    {
        Dark_String* const string = dark_string_new_capacity(allocator, dark_growth_standard, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert_front(string, 'a');
        dark_string_insert_front(string, 'b');
        dark_string_insert_front(string, 'x');

        DARK_TEST_GE_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xba", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_pop")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop(string, 0, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "bcxyz", 6);

        dark_string_pop(string, 1, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "byz", 4);

        dark_string_pop(string, 0, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        DARK_TEST_EQ_S(dark_string_cstring(string), "yz", 3);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_pop_front")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop_front(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xyz", 4);

        dark_string_pop_front(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 1);

        DARK_TEST_EQ_S(dark_string_cstring(string), "z", 2);

        dark_string_pop_front(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_append_cstring(string, "hello");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "hello", 6);

        dark_string_pop_front(string, 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_pop_back")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop_back(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abc", 4);

        dark_string_pop_back(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 1);

        DARK_TEST_EQ_S(dark_string_cstring(string), "a", 2);

        dark_string_pop_back(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_append_cstring(string, "hello");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "hello", 6);

        dark_string_pop_back(string, 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_erase")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "acxyz", 5);

        dark_string_erase(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "acxz", 4);

        dark_string_erase(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "acz", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_erase_front")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "bcxyz", 6);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "cxyz", 5);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "xyz", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_erase_back")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abcxy", 6);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abcx", 5);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cstring(string), "abc", 4);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_reserve/_additional")
    {
        Dark_String* const string = dark_string_new(allocator, dark_growth_standard);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve(string, 100);

        DARK_TEST_GE_U(dark_string_capacity(string), 100);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve(string, 0);

        DARK_TEST_GE_U(dark_string_capacity(string), 100);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve(string, 101);

        DARK_TEST_GE_U(dark_string_capacity(string), 100);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_additional(string, 101);

        DARK_TEST_GE_U(dark_string_capacity(string), 101);
        DARK_TEST_LT_U(dark_string_capacity(string), 202);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_reserve_exact")
    {
        Dark_String* const string = dark_string_new(allocator, dark_growth_standard);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_exact(string, 100);

        DARK_TEST_EQ_U(dark_string_capacity(string), 100);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_exact(string, 0);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_exact(string, 101);

        DARK_TEST_EQ_U(dark_string_capacity(string), 101);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_shrink_to_fit")
    {
        Dark_String* const string = dark_string_new(allocator, dark_growth_standard);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_exact(string, 100);
        dark_string_shrink_to_fit(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_append_cstring(string, "0123456789");
        dark_string_append_cstring(string, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),11);
        DARK_TEST_EQ_U(dark_string_size(string), 11);

        dark_string_shrink_to_fit(string);

        DARK_TEST_EQ_U(dark_string_capacity(string),11);
        DARK_TEST_EQ_U(dark_string_size(string), 11);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_resize")
    {
        Dark_String* const string = dark_string_new(allocator, dark_growth_standard);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_resize(string, 10);

        DARK_TEST_GE_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 10);

        dark_string_resize(string, 5);

        DARK_TEST_GE_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_append_cstring(string, "0123456789");
        dark_string_append_cstring(string, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),16);
        DARK_TEST_EQ_U(dark_string_size(string), 16);

        dark_string_resize(string, 0);

        DARK_TEST_GE_U(dark_string_capacity(string), 16);
        DARK_TEST_EQ_U(dark_string_size(string), 0);
        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_resize_fill")
    {
        Dark_String* const string = dark_string_new(allocator, dark_growth_standard);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_resize_fill(string, 10, 'c');

        DARK_TEST_GE_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 10);

        dark_string_resize_fill(string, 5, 'a');

        DARK_TEST_GE_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_append_cstring(string, "0123456789");
        dark_string_append_cstring(string, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),16);
        DARK_TEST_EQ_U(dark_string_size(string), 16);

        dark_string_resize_fill(string, 0, 'm');

        DARK_TEST_GE_U(dark_string_capacity(string), 16);
        DARK_TEST_EQ_U(dark_string_size(string), 0);
        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_clear")
    {
        Dark_String* const string = dark_string_new_cstring(allocator, dark_growth_standard, "hijkl");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_clear(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 0);;
        DARK_TEST_EQ_S(dark_string_cstring(string), "", 1);

        dark_string_delete(string);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("string_struct_byte")
    {
        DARK_TEST_GT_U(dark_string_struct_byte(), 0);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
