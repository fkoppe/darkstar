#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("file_create/destroy")
    {
        void* const file = malloc(dark_file_struct_size());
        DARK_ASSERT(NULL != file, DARK_ERROR_ALLOCATION);

        dark_file_create(file);
        dark_file_destroy(file);

        free(file);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("file_new/delete")
    {
        void* const file = dark_file_new();
        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("file_open/close")
    {
        void* const file = dark_file_new();

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("file_write")
    {
        char buffer[] = "blablablupp";

        void* const file = dark_file_new();

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_write(file, sizeof(char), sizeof(buffer), buffer);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#5----------
    DARK_TEST("file_mmap")
    {
        char buffer[] = "blablablupp";

        void* const file = dark_file_new();

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        const char* mapped = NULL;
        result = dark_file_mmap(file, &mapped);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_NE_P(mapped, NULL);
        DARK_TEST_EQ_S(mapped, buffer, sizeof(buffer));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#6----------
    DARK_TEST("file_open_is")
    {
        void* const file = dark_file_new();

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        DARK_TEST_TRUE(dark_file_open_is(file));

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#7----------
    DARK_TEST("file_open_is")
    {
        void* const file = dark_file_new();

        Dark_Oserror result = dark_file_open(file, "test_file", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        size_t size = 0;
        result = dark_file_size_get(file, &size);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);
        DARK_TEST_GT_U(size, 0);

        result = dark_file_close(file);
        DARK_TEST_TRUE(DARK_OSERROR_NONE == result);

        dark_file_delete(file);
    }
    //--------------------------

    //----------TEST#8----------
    DARK_TEST("file_count_max")
    {
        DARK_TEST_NE_U(dark_file_count_max(), 0);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
