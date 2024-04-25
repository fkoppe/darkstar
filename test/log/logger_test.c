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

    //----------TEST----------
    DARK_TEST("logger_test")
    {
        Dark_Stream_Setting ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 1024;

        Dark_Ostream* const ostream_stdout = dark_ostream_new(ostream_settings);
        dark_ostream_add_stdout(ostream_stdout, NULL);

        const Dark_Log_Format custom = { true, DARK_LOG_THREAD_HEX, true, true, true, true };

        Dark_Logger_Settings logger_settings;
        logger_settings.color = NULL;
        logger_settings.log_is = true;
        logger_settings.update_is = false;
        logger_settings.level_min = DARK_LOG_LEVEL_COMMENT;
        logger_settings.format = custom;

        Dark_Logger* const logger = dark_logger_new(logger_settings, ostream_stdout, NULL);

        DARK_LOG(logger, DARK_LOG_LEVEL_INFO, 5, "test");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_INFO, "test");
        DARK_LOG_F(logger, DARK_LOG_LEVEL_INFO, "test message (%i)", 1234);

        DARK_NLOG(logger, "name", DARK_LOG_LEVEL_INFO, 5, "test");
        DARK_NLOG_CSTRING(logger, "name", DARK_LOG_LEVEL_INFO, "test");
        DARK_NLOG_F(logger, "name", DARK_LOG_LEVEL_INFO, "test message (%i)", 1234);

        dark_logger_delete(logger);

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
