#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    DARK_TEST_NE_U(dark_file_count_max(), 0);

    void* file_1 = dark_file_new();
    void* file_2 = dark_file_new();

    DARK_TEST(dark_file_open(file_1, "test_file_1", DARK_FILE_MODE_WRITE, DARK_FILE_FLAG_NONE));
    char buffer[] = "blablablupp";
    DARK_TEST(dark_file_write_cbuffer(file_1, buffer));
    DARK_TEST(dark_file_close(file_1));

    DARK_TEST(dark_file_open(file_2, "test_file_1", DARK_FILE_MODE_READ, DARK_FILE_FLAG_NONE));
    const char* mapped = NULL;
    DARK_TEST(dark_file_mmap(file_2, &mapped));
    DARK_TEST_NE_P(mapped, NULL);
    DARK_TEST_EQ_S(mapped, buffer, sizeof(buffer));

    dark_file_delete(file_2);
    dark_file_delete(file_1);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
