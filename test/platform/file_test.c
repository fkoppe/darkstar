#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* allocator = dark_os_allocator_new();

    dark_test_initialise();

    DARK_TEST("file_struct_byte")
    {
        DARK_TEST_GT_U(dark_file_struct_byte(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_new/delete")
    {
        Dark_File* const file = dark_file_new(allocator);
        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open/close")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_write")
    {
        char buffer[] = "blablablupp";
        Dark_Array array = { .data = buffer, .size = 12, .element_byte = sizeof(char)};

        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_write(file, array);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_mmap")
    {
        char buffer[] = "blablablupp";

        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        void* mapped = NULL;
        result = dark_file_mmap(file, &mapped);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_NE_P(mapped, NULL);
        DARK_TEST_EQ_S(mapped, buffer, sizeof(buffer));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open_is")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_TRUE(dark_file_open_is(file));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_open_is/byte")
    {
        Dark_File* const file = dark_file_new(allocator);

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        size_t size = 0;
        result = dark_file_byte(file, &size);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);
        DARK_TEST_GT_U(size, 0);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(allocator, file);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_count_max")
    {
        DARK_TEST_NE_U(dark_file_count_max(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("file_modifier_get")
    {
        char modifier[DARK_FILE_MODIFIER_SIZE] = { 0 };
        dark_file_modifier_get(DARK_FILE_MODE_READ, DARK_FILE_FLAG_UPDATE | DARK_FILE_FLAG_BINARY, modifier);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
