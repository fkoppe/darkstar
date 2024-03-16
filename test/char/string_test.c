#include <dark/darkstar.h>

void va_create_helper(void* string_, const char* const format_, ...)
{
    va_list args;
    va_start(args, format_);
    dark_string_create_v(string_, DARK_GROWTH_STANDARD, format_, args);
    va_end(args);
}

void* va_new_helper(const char* const format_, ...)
{
    va_list args;
    va_start(args, format_);
    void* result = dark_string_new_v(DARK_GROWTH_STANDARD, format_, args);
    va_end(args);

    return result;
}

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("string_struct_size")
    {
        DARK_TEST_EQ_U(dark_string_struct_size(), dark_vector_struct_size());
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("string_create_v/_capacity/_size/_cbuffer/_destroy")
    {
        Dark_Vector_Struct string;

        va_create_helper(&string, "hello %s %i", "world", -11);

        DARK_TEST_EQ_U(dark_string_capacity(&string), 15);
        DARK_TEST_EQ_U(dark_string_size(&string), 15);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(&string), "hello world -11", 16);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("string_create_f")
    {
        Dark_Vector_Struct string;

        dark_string_create_f(&string, DARK_GROWTH_STANDARD, "hello %s %i", "world", -123);

        DARK_TEST_EQ_U(dark_string_capacity(&string), 16);
        DARK_TEST_EQ_U(dark_string_size(&string), 16);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(&string), "hello world -123", 17);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("string_create_cbuffer")
    {
        Dark_Vector_Struct string;

        dark_string_create_cbuffer(&string, DARK_GROWTH_STANDARD, 4, "nooo");

        DARK_TEST_EQ_U(dark_string_size(&string), 4);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(&string), "nooo", 5);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#5----------
    DARK_TEST("string_create_char")
    {
        Dark_Vector_Struct string;

        dark_string_create_char(&string, DARK_GROWTH_STANDARD, 'x');

        DARK_TEST_EQ_U(dark_string_size(&string), 1);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(&string), "x", 2);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#6----------
    DARK_TEST("string_create_size/_capacity/_size/_destroy")
    {
        Dark_Vector_Struct string;

        dark_string_create_size(&string, DARK_GROWTH_STANDARD, 10, 2);

        DARK_TEST_EQ_U(dark_string_capacity(&string), 10);
        DARK_TEST_EQ_U(dark_string_size(&string), 2);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#7----------
    DARK_TEST("string_create_capacity")
    {
        Dark_Vector_Struct string;

        dark_string_create_capacity(&string, DARK_GROWTH_STANDARD, 2);

        DARK_TEST_EQ_U(dark_string_capacity(&string), 2);
        DARK_TEST_EQ_U(dark_string_size(&string), 0);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#8----------
    DARK_TEST("string_create_capacity")
    {
        Dark_Vector_Struct string;

        dark_string_create(&string, DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(&string), 0);
        DARK_TEST_EQ_U(dark_string_size(&string), 0);

        dark_string_destroy(&string);
    }
    //--------------------------

    //----------TEST#9----------
    DARK_TEST("string_new_v/_delete")
    {
        void* string = va_new_helper("hello %s %i", "from", -123);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello from -123", 16);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#10----------
    DARK_TEST("string_create_f")
    {
        void* string = dark_string_new_f(DARK_GROWTH_STANDARD, "hello %s %i", "from", -123);

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "hello from -123", 16);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#11----------
    DARK_TEST("string_create_cbuffer")
    {
        void* string = dark_string_new_cbuffer(DARK_GROWTH_STANDARD, 4, "nooo");

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "nooo", 5);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#12----------
    DARK_TEST("string_create_char")
    {
        void* string = dark_string_new_char(DARK_GROWTH_STANDARD, 'x');

        DARK_TEST_EQ_S(dark_string_cbuffer_terminated(string), "x", 2);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#13----------
    DARK_TEST("string_create_size/_destroy")
    {
        void* string = dark_string_new_size(DARK_GROWTH_STANDARD, 10, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 10);
        DARK_TEST_EQ_U(dark_string_size(string), 2);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#14----------
    DARK_TEST("string_create_capacity")
    {
        void* string = dark_string_new_capacity(DARK_GROWTH_STANDARD, 2);

        DARK_TEST_EQ_U(dark_string_capacity(string), 2);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //--------------------------

    //----------TEST#15----------
    DARK_TEST("string_create_capacity")
    {
        void* string = dark_string_new(DARK_GROWTH_STANDARD);

        DARK_TEST_EQ_U(dark_string_capacity(string), 0);
        DARK_TEST_EQ_U(dark_string_size(string), 0);

        dark_string_delete(string);
    }
    //--------------------------

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
