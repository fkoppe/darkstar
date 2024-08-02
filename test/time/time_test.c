#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

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
