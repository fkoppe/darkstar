#include <dark/darkstar.h>

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    Dark_Mutex* mutex = dark_mutex_new();

    char buf[] = { "test message larger than buffer" };

    Dark_Stream_Setting stream_settings;
    stream_settings.binary_is = false;
    stream_settings.force_size_is = false;
    stream_settings.buffer_size = 10;

    Dark_Stream* stream = dark_ostream_new(stream_settings);

    dark_ostream_add_stdout(stream, NULL);
    dark_ostream_add_file(stream, "output.txt", NULL);

    dark_ostream_write(stream, sizeof(buf), buf);

    dark_ostream_flush(stream);
    dark_ostream_delete(stream);

    Dark_Stream_Setting stream2_settings;
    stream2_settings.binary_is = false;
    stream2_settings.force_size_is = true;
    stream2_settings.buffer_size = 10;

    Dark_Stream* stream2 = dark_ostream_new(stream2_settings);

    dark_ostream_add_stdout(stream2, NULL);
    dark_ostream_add_file(stream2, "output.txt", NULL);

    dark_ostream_write(stream2, sizeof(buf), buf);

    dark_ostream_flush(stream2);
    dark_ostream_delete(stream2);

    dark_mutex_delete(mutex);

#if defined(___DARK_DEBUG)
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.count - dark_memory_profiler_info_own().current.count);
    DARK_TEST_EQ_U(0, dark_memory_profiler_info_all().current.usage - dark_memory_profiler_info_own().current.usage);

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
