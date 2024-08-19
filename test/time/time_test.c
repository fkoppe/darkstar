#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/time/stopwatch_struct.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("duration")
    {
        DARK_TEST_EQ_U(DARK_DURATION_S_TO_MS(1), 1000);
        DARK_TEST_EQ_U(DARK_DURATION_S_TO_NS(1), 1000000000);

        DARK_TEST_EQ_U(DARK_DURATION_MS_TO_S(1), 0);
        DARK_TEST_EQ_U(DARK_DURATION_MS_TO_S(1000), 1);
        DARK_TEST_EQ_U(DARK_DURATION_MS_TO_NS(1), 1000000);

        DARK_TEST_EQ_U(DARK_DURATION_NS_TO_S(1), 0);
        DARK_TEST_EQ_U(DARK_DURATION_NS_TO_S(1000000000), 1);
        DARK_TEST_EQ_U(DARK_DURATION_NS_TO_MS(1), 0);
        DARK_TEST_EQ_U(DARK_DURATION_NS_TO_MS(1000000), 1);

        DARK_TEST_EQ_U(dark_duration_s_to_ms(1), 1000);
        DARK_TEST_EQ_U(dark_duration_s_to_ns(1), 1000000000);

        DARK_TEST_EQ_U(dark_duration_ms_to_s(1), 0);
        DARK_TEST_EQ_U(dark_duration_ms_to_s(1000), 1);
        DARK_TEST_EQ_U(dark_duration_ms_to_ns(1), 1000000);

        DARK_TEST_EQ_U(dark_duration_ns_to_s(1), 0);
        DARK_TEST_EQ_U(dark_duration_ns_to_s(1000000000), 1);
        DARK_TEST_EQ_U(dark_duration_ns_to_ms(1), 0);
        DARK_TEST_EQ_U(dark_duration_ns_to_ms(1000000), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stopwatch_construct/_destruct")
    {
        Dark_Stopwatch* const stopwatch = dark_malloc(allocator, sizeof(*stopwatch));;

        dark_stopwatch_construct(allocator, stopwatch);
        dark_stopwatch_destruct(stopwatch);

        dark_free(allocator, stopwatch, sizeof(*stopwatch));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stopwatch")
    {
        Dark_Stopwatch* stopwatch = dark_stopwatch_new(allocator);

        dark_stopwatch_start(stopwatch);

        dark_stopwatch_reset(stopwatch);
        dark_stopwatch_reset_ns(stopwatch);
        dark_stopwatch_reset_ms(stopwatch);
        dark_stopwatch_reset_s(stopwatch);

        DARK_TEST_FALSE(dark_stopwatch_running_is(stopwatch));

        dark_stopwatch_restart(stopwatch);
        dark_stopwatch_restart_ns(stopwatch);
        dark_stopwatch_restart_ms(stopwatch);
        dark_stopwatch_restart_s(stopwatch);

        DARK_TEST_TRUE(dark_stopwatch_running_is(stopwatch));

        dark_stopwatch_ns(stopwatch);
        dark_stopwatch_ms(stopwatch);
        dark_stopwatch_s(stopwatch);

        Dark_Stopwatch* other = dark_stopwatch_new_start(allocator);
        while (dark_stopwatch_ms(other) < 1)
        {

        }

        dark_stopwatch_delete(other);

        DARK_TEST_GE_U(dark_stopwatch_delete_ms(stopwatch), 1);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stopwatch_struct_byte")
    {
        DARK_TEST_GT_U(dark_stopwatch_struct_byte(), 0);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stamp_hms")
    {
        char buffer[DARK_STAMP_HMS_SIZE];
        const Dark_Cbuffer cbuffer = { DARK_STAMP_HMS_SIZE, buffer };

        dark_stamp_hms_write(cbuffer);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("stamp_hms_terminated")
    {
        char buffer[DARK_STAMP_HMS_SIZE_TERMINATED];
        const Dark_Cbuffer cbuffer = { DARK_STAMP_HMS_SIZE, buffer };

        dark_stamp_hms_write_terminated(cbuffer);

        dark_cstring_lenght(cbuffer.data);
    }
    //--------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
