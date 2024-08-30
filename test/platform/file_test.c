#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/platform/file_struct.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("file_construct/_destruct")
    {
        Dark_File* const file = dark_malloc(allocator, sizeof(*file));;

        dark_file_construct(allocator, file);
        dark_file_destruct(file);

        dark_free(allocator, file, sizeof(*file));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("file_new/_delete")
    {
        Dark_File* const file = dark_file_new(allocator);
        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open/_close")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file"), DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_write/_read")
    {
        char buffer[] = "blablablupp";
        Dark_Cbuffer_View cbuffer_view = { 12, buffer };

        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file.txt"), DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_write(file, cbuffer_view);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

                result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        char read[12];
        Dark_Cbuffer cbuffer_read = { 12, read };

        result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file.txt"), DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_read(file, cbuffer_read);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        const Dark_Cbuffer_View v = dark_cbuffer_to_view(cbuffer_read);

        DARK_TEST_EQ_I(dark_cbuffer_view_compare(&cbuffer_view, &v), 0);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_binary_read/_write")
    {
        char buffer[] = "blablablupp";
        const Dark_Array_View array_view = { sizeof(char), 12, buffer };

        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file_binary"), DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_BINARY);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_write_binary(file, array_view);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file_binary"), DARK_FILE_MODE_READ, DARK_FILE_FLAG_BINARY);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        char read[12];
        Dark_Array array_read = { sizeof(char), 12, read };

        size_t read_count = 0;
        result = dark_file_read_binary(file, array_read, &read_count);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_EQ_U(read_count, 12);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        const Dark_Array_View av = dark_array_to_view(array_read);

        DARK_TEST_EQ_I(dark_array_view_compare(&array_view, &av), 0);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_mmap")
    {
        char buffer[] = "blablablupp";
        Dark_Cbuffer_View cbuffer_view = { 12, buffer };

        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file"), DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_write(file, cbuffer_view);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

                result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file"), DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        void* mapped = NULL;
        result = dark_file_mmap(file, &mapped);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_NE_P(mapped, NULL);
        DARK_TEST_EQ_S(mapped, buffer, sizeof(buffer));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open_is")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file"), DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_TRUE(dark_file_open_is(file));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open_is/byte")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, dark_cstring_to_cbuffer_view("test_file"), DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        size_t size = 0;
        result = dark_file_byte(file, &size);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);
        DARK_TEST_GT_U(size, 0);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

         DARK_TEST("file_struct_byte")
    {
        DARK_TEST_GT_U(dark_file_struct_byte(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_count_max")
    {
        DARK_TEST_NE_U(dark_file_count_max(), 0);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
