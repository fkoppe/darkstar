#include <dark/darkstar.h>

#undef DARK_LIBRARY
#define DARK_LIBRARY &DARK_INFO_LIBRARY_DARKSTAR

#undef DARK_MODULE
#define DARK_MODULE "vulkan"

#undef DARK_UNIT
#define DARK_UNIT "main"

int main()
{
#if defined(___DARK_DEBUG)
    dark_memory_profiler_initialise(DARK_MEMORY_PROFILE_LEVEL_FULL, true);
#endif // defined(___DARK_DEBUG)

    //----------TEST#1----------
    DARK_TEST("static_log_test")
    {
        Dark_Stream_Setting ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 1024;

        void* const ostream_stdout = dark_ostream_new(ostream_settings);
        dark_ostream_add_stdout(ostream_stdout, NULL);

        const Dark_Log_Format custom = { true, DARK_LOG_THREAD_HEX, true, true, true, true };
        DARK_SLOG_CBUFFER("some_name", custom, DARK_LOG_LEVEL_INFO, ostream_stdout, NULL, 5, "test");
        DARK_SLOG_CSTRING("some_name", custom, DARK_LOG_LEVEL_INFO, ostream_stdout, NULL, "test");
        DARK_SLOG_F("some_name", custom, DARK_LOG_LEVEL_INFO, ostream_stdout, NULL, "test message (%i)", 1234);

        dark_ostream_flush(ostream_stdout);

        dark_ostream_delete(ostream_stdout);
    }
    //--------------------------

    dark_test_end();

#if defined(___DARK_DEBUG)
    DARK_TEST_FALSE(dark_memory_profile_leak_is());

    dark_memory_profiler_shutdown(false);
#endif // defined(___DARK_DEBUG)

    return EXIT_SUCCESS;
}
