#include <dark/darkstar.h>

void va_create_helper(Dark_String* const string_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != string_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    dark_string_create_v(string_, DARK_GROWTH_STANDARD, format_, args);
    va_end(args);
}

void* va_new_helper(const char* const format_, ...)
{
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args;
    va_start(args, format_);
    void* const result = dark_string_new_v(DARK_GROWTH_STANDARD, format_, args);
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
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST----------
    DARK_TEST("string_struct_size")
    {
        DARK_TEST_EQ_U(dark_string_struct_size(), dark_vector_struct_size());
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_v/_capacity/_size/_cbuffer/_destroy")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        va_create_helper(string, "hello %s %i", "world", -11);

        DARK_TEST_EQ_U(dark_string_capacity(string), 15);
        DARK_TEST_EQ_U(dark_string_size(string), 15);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello world -11", 16);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_f")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create_f(string, DARK_GROWTH_STANDARD, "hello %s %i", "world", -123);

        DARK_TEST_EQ_U(dark_string_capacity(string), 16);
        DARK_TEST_EQ_U(dark_string_size(string), 16);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello world -123", 17);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_cbuffer")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create_cbuffer(string, DARK_GROWTH_STANDARD, 4, "nooo");

        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "nooo", 5);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_char")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create_char(string, DARK_GROWTH_STANDARD, 'x');

        DARK_TEST_EQ_U(dark_string_size(string), 1);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "x", 2);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_size/_capacity/_size/_destroy")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create_size(string, DARK_GROWTH_STANDARD, 10, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_capacity")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create_capacity(string, DARK_GROWTH_STANDARD, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_capacity")
    {
        Dark_Vector_Struct vector_struct;
        Dark_String* const string = (Dark_String*)&vector_struct;

        dark_string_create(string, DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_destroy(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_new_v/_delete")
    {
        Dark_String* const string = va_new_helper("hello %s %i", "from", -123);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello from -123", 16);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_f")
    {
        Dark_String* const string = dark_string_new_f(DARK_GROWTH_STANDARD, "hello %s %i", "from", -123);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello from -123", 16);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_cbuffer")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 4, "nooo");

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "nooo", 5);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_char")
    {
        Dark_String* const string = dark_string_new_char(DARK_GROWTH_STANDARD, 'x');

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "x", 2);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_size/_destroy")
    {
        Dark_String* const string = dark_string_new_size(DARK_GROWTH_STANDARD, 10, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_capacity")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_create_capacity")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_at")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 5, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_at(string, 0), 'a');
        DARK_TEST_EQ_I(dark_string_at(string, 1), 'b');
        DARK_TEST_EQ_I(dark_string_at(string, 2), 'c');
        DARK_TEST_EQ_I(dark_string_at(string, 3), 'd');
        DARK_TEST_EQ_I(dark_string_at(string, 4), 'e');

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_front")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 5, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_front(string), 'a');

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_back")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 5, "abcde");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_I(dark_string_back(string), 'e');

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_substring")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 3, "xyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_substring_terminated(string, 0), "xyz", 4);
        DARK_TEST_EQ_S(dark_string_substring_terminated(string, 1), "yz", 3);
        DARK_TEST_EQ_S(dark_string_substring_terminated(string, 2), "z", 2);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_emplace")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

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

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "31254", 6);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_front")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

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

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "31254", 6);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_emplace_back")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

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

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "31254", 6);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_inplace")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 3, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace(string, 2);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abxc", 5);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_front")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 3, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace_front(string);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "xabc", 5);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_inplace_back")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 3, "abc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        char* destination = dark_string_inplace_back(string);
        *destination = 'x';

        DARK_TEST_GE_U(dark_string_capacity(string), 4);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abcx", 5);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_push_v")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        va_push_helper(string, 0, "%i", 1);
        va_push_helper(string, 1, "%i", 2);
        va_push_helper(string, 0, "%i", 3);
        va_push_helper(string, 3, "%i", 4);
        va_push_helper(string, 3, "%i", 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "31254", 6);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_push_f")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_push_f(string, 0, "%i", 1);
        dark_string_push_f(string, 1, "%i", 2);
        dark_string_push_f(string, 0, "%i", 3);
        dark_string_push_f(string, 3, "%i", 4);
        dark_string_push_f(string, 3, "%i", 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "31254", 6);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_push_cbuffer")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 7);

        DARK_TEST_EQ_U(dark_string_capacity(string), 7);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_push_cbuffer(string, 0, 3, "abc");
        dark_string_push_cbuffer(string, 1, 2, "XY");
        dark_string_push_cbuffer(string, 0, 3, "...");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "...aXYbc", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_append_v")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        va_append_helper(string, "noo%s", "cap");

        DARK_TEST_EQ_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "ccnoocap", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_append_f")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_append_f(string, "noo%s", "cap");

        DARK_TEST_EQ_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "ccnoocap", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_append_cbuffer")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_append_cbuffer(string, 4, "hell");
        dark_string_append_cbuffer(string, 2, "no");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "cchellno", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_v")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        va_prepend_helper(string, "noo%s", "cap");

        DARK_TEST_EQ_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "noocapcc", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_f")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_prepend_f(string, "noo%s", "cap");

        DARK_TEST_EQ_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "noocapcc", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_prepend_cbuffer")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 2, "cc");

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_prepend_cbuffer(string, 4, "hell");
        dark_string_prepend_cbuffer(string, 2, "no");

        DARK_TEST_GE_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "nohellcc", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_insert")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert(string, 0, 'a');
        dark_string_insert(string, 0, 'b');
        dark_string_insert(string, 0, 'c');
        dark_string_insert(string, 0, 'd');
        dark_string_insert(string, 0, 'e');

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "edcba", 6);

        dark_string_insert(string, 5, '.');
        dark_string_insert(string, 6, '-');
        dark_string_insert(string, 5, '.');

        DARK_TEST_EQ_U(dark_string_capacity(string), 8);
        DARK_TEST_EQ_U(dark_string_size(string), 8);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "edcba..-", 9);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_insert_front")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 0);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert_back(string, 'a');
        dark_string_insert_back(string, 'b');
        dark_string_insert_back(string, 'x');

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abx", 4);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_insert_back")
    {
        Dark_String* const string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_insert_front(string, 'a');
        dark_string_insert_front(string, 'b');
        dark_string_insert_front(string, 'x');

        DARK_TEST_EQ_U(dark_string_capacity(string), 3);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "xba", 4);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_pop")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop(string, 0, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "bcxyz", 6);

        dark_string_pop(string, 1, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "byz", 4);

        dark_string_pop(string, 0, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "yz", 3);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_pop_front")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop_front(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "xyz", 4);

        dark_string_pop_front(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 1);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "z", 2);

        dark_string_pop_front(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_append_cbuffer(string, 5, "hello");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello", 6);

        dark_string_pop_front(string, 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_pop_back")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_pop_back(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abc", 4);

        dark_string_pop_back(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 1);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "a", 2);

        dark_string_pop_back(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_append_cbuffer(string, 5, "hello");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello", 6);

        dark_string_pop_back(string, 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_erase")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase(string, 1);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "acxyz", 5);

        dark_string_erase(string, 3);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "acxz", 4);

        dark_string_erase(string, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "acz", 4);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_erase_front")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "bcxyz", 6);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "cxyz", 5);

        dark_string_erase_front(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "xyz", 4);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_erase_back")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 6, "abcxyz");

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 6);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abcxy", 6);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abcx", 5);

        dark_string_erase_back(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 6);
        DARK_TEST_EQ_U(dark_string_size(string), 3);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "abc", 4);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_reserve/_additional")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve(string, 100);

        DARK_TEST_EQ_U(dark_string_capacity(string), 100);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve(string, 0);

        DARK_TEST_EQ_U(dark_string_capacity(string), 100);
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
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_reserve_exact")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

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
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_shrink_to_fit")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_reserve_exact(string, 100);
        dark_string_shrink_to_fit(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_append_cbuffer(string, 10, "0123456789");
        dark_string_append_cbuffer(string, 1, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),11);
        DARK_TEST_EQ_U(dark_string_size(string), 11);

        dark_string_shrink_to_fit(string);

        DARK_TEST_EQ_U(dark_string_capacity(string),11);
        DARK_TEST_EQ_U(dark_string_size(string), 11);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_resize")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_resize(string, 10);

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 10);

        dark_string_resize(string, 5);

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_append_cbuffer(string, 10, "0123456789");
        dark_string_append_cbuffer(string, 1, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),16);
        DARK_TEST_EQ_U(dark_string_size(string), 16);

        dark_string_resize(string, 0);

        DARK_TEST_GE_U(dark_string_capacity(string), 16);
        DARK_TEST_EQ_U(dark_string_size(string), 0);
        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_resize_fill")
    {
        Dark_String* const string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_resize_fill(string, 10, 'c');

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 10);

        dark_string_resize_fill(string, 5, 'a');

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_append_cbuffer(string, 10, "0123456789");
        dark_string_append_cbuffer(string, 1, "X");

        DARK_TEST_GE_U(dark_string_capacity(string),16);
        DARK_TEST_EQ_U(dark_string_size(string), 16);

        dark_string_resize_fill(string, 0, 'm');

        DARK_TEST_GE_U(dark_string_capacity(string), 16);
        DARK_TEST_EQ_U(dark_string_size(string), 0);
        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("string_clear")
    {
        Dark_String* const string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 5, "hijkl");

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 5);

        dark_string_clear(string);

        DARK_TEST_EQ_U(dark_string_capacity(string), 5);
        DARK_TEST_EQ_U(dark_string_size(string), 0);;
        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "", 1);

        dark_string_delete(string);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
