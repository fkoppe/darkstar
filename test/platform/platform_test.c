#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("clock")
    {
        dark_clock_ns();
        dark_clock_ms();
        dark_clock_s();
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("console")
    {
        dark_console_hide();
        dark_console_show();
        dark_console_clear();
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("oserror")
    {
        DARK_TEST_FALSE(dark_oserror_occured_is());

        dark_oserror_occured();

        for(size_t i = ___DARK_OSERROR_MIN + 1; i < ___DARK_OSERROR_MAX; i++)
        {
            dark_oserror_name((Dark_Oserror)i);
        }
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("process")
    {
        dark_process_id();
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
