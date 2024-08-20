#include "dark/char/cbuffer_view.h"
#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/stream/ostream_struct.h>

void va_helper(Dark_Logger* const logger_, const char* const format_, ...)
{
    DARK_ASSERT(NULL != logger_, DARK_ERROR_NULL);
    DARK_ASSERT(NULL != format_, DARK_ERROR_NULL);

    va_list args1;
    va_list args2;
    va_list args3;

    va_start(args1, format_);

    va_copy(args2, args1);
    va_copy(args3, args1);

    DARK_LOG_V(logger, DARK_LOG_LEVEL_TRACE, format_, args1);
    va_end(args1);

    va_start(args2, format_);
    DARK_PLOG_V(logger, DARK_LOG_LEVEL_TRACE, format_, args2);
    va_end(args2);

    va_start(args3, format_);
    DARK_DLOG_V(logger, DARK_LOG_LEVEL_TRACE, format_, args3);
    va_end(args3);
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();
    Dark_Mutex* mutex = dark_mutex_new(allocator);

    Dark_Ostream_Settings ostream_settings;
    ostream_settings.binary_is = false;
    ostream_settings.force_size_is = false;
    ostream_settings.buffer_size = 0;
    ostream_settings.auto_flush_ns = 0;

    Dark_Ostream* const ostream = dark_malloc(allocator, sizeof(*ostream));

    dark_ostream_construct_file(allocator, ostream, ostream_settings, "log.txt", NULL);

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("logger")
    {
        Dark_Logger_Settings logger_settings;
        logger_settings.name = "test_logger";
        logger_settings.color = "";
        logger_settings.log_is = true;
        logger_settings.update_is = true;

        Dark_Logger* const logger = dark_logger_new(allocator, logger_settings);

        Dark_Logger_Ostream_Settings logger_ostream_settings;
        logger_ostream_settings.color_is = true;
        logger_ostream_settings.level_min = DARK_LOG_LEVEL_TRACE;
        logger_ostream_settings.format.timestamp_is = true;
        logger_ostream_settings.format.thread = DARK_LOGGER_THREAD_HEX;
        logger_ostream_settings.format.name_is = true;
        logger_ostream_settings.format.module_is = true;
        logger_ostream_settings.format.unit_is = true;

        dark_logger_ostream_add(logger, logger_ostream_settings, ostream, NULL);

        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_TRACE, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_COMMENT, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_DEBUG, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_NOTE, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_INFO, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_NOTICE, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_WARN, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_ERROR, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_CRITICAL, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_ALERT, "a test log message of some sort");
        DARK_LOG_CSTRING(logger, DARK_LOG_LEVEL_EMERGENCY, "a test log message of some sort");

        const Dark_Cbuffer_View view = dark_cstring_to_cbuffer_view("another log message");

        DARK_LOG_CBUFFER_VIEW(logger, DARK_LOG_LEVEL_TRACE, view);
        DARK_LOG_F(logger, DARK_LOG_LEVEL_TRACE, "%i", -1);

        DARK_PLOG_CSTRING(logger, DARK_LOG_LEVEL_TRACE, "hello");
        DARK_PLOG_CBUFFER_VIEW(logger, DARK_LOG_LEVEL_TRACE, view);
        DARK_PLOG_F(logger, DARK_LOG_LEVEL_TRACE, "%i", -1);

        DARK_DLOG_CSTRING(logger, DARK_LOG_LEVEL_TRACE, "hello2");
        DARK_DLOG_CBUFFER_VIEW(logger, DARK_LOG_LEVEL_TRACE, view);
        DARK_DLOG_F(logger, DARK_LOG_LEVEL_TRACE, "%i", -1);

        va_helper(logger, "%i", -111);

        dark_logger_update(logger);
        dark_logger_stamp_recent_make(logger);

        dark_logger_delete(logger);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("logger_struct_byte")
    {
        DARK_TEST_GT_U(dark_logger_struct_byte(), 0);
    }
    //--------------------------

    dark_test_shutdown();

    dark_ostream_destruct(ostream);

    dark_mutex_delete(mutex);
    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
