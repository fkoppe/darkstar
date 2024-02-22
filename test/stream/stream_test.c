#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    void* mutex = dark_mutex_new();

    Dark_Stream_Setting stream_settings;
    stream_settings.binary = false;
    stream_settings.buffer_size = 10;

    void* stream = dark_ostream_new(stream_settings);

    dark_ostream_add_stdout(stream, NULL);
    dark_ostream_add_file(stream, "output.txt", NULL);

    char buf[] = { "test message larger than buffer" };

    dark_ostream_write(stream, sizeof(buf), buf);

    dark_ostream_flush(stream);

    dark_ostream_delete(stream);

    dark_mutex_delete(mutex);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
