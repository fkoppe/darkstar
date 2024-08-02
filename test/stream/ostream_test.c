#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();
    Dark_Mutex* mutex = dark_mutex_new(allocator);

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("ostream_new/delete")
    {
        Dark_Ostream_Settings ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 0;

        Dark_Ostream* const ostream = dark_ostream_new(allocator, ostream_settings);

        dark_ostream_delete(ostream);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_add_file/_stdout/_stderr")
    {
        Dark_Ostream_Settings ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 10;

        Dark_Ostream* const ostream = dark_ostream_new(allocator, ostream_settings);

        dark_ostream_add_stdout(ostream, mutex);
        dark_ostream_add_stderr(ostream, NULL);
        dark_ostream_add_file(ostream, "output.txt", NULL);

        dark_ostream_delete(ostream);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_flush_unbuffered")
    {
        const char buffer[] = { "test message larger than buffer" };
        const Dark_Buffer_View view = { sizeof(buffer), buffer };

        Dark_Ostream_Settings ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 10;

        Dark_Ostream* const ostream = dark_ostream_new(allocator, ostream_settings);

        dark_ostream_add_stdout(ostream, mutex);
        dark_ostream_add_stderr(ostream, NULL);
        dark_ostream_add_file(ostream, "output.txt", NULL);

        dark_ostream_flush_unbuffered(ostream, view);

        dark_ostream_delete(ostream);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_write/flush")
    {
        const char buffer[] = { "test message larger than buffer" };
        const Dark_Buffer_View view = { sizeof(buffer), buffer };


        Dark_Ostream_Settings ostream_settings;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 10;

        Dark_Ostream* const ostream = dark_ostream_new(allocator, ostream_settings);

        dark_ostream_add_stdout(ostream, mutex);
        dark_ostream_add_stderr(ostream, NULL);
        dark_ostream_add_file(ostream, "output.txt", NULL);

        dark_ostream_write(ostream, view);
        dark_ostream_flush(ostream);

        dark_ostream_delete(ostream);
    }
    //--------------------------

    dark_test_shutdown();

    dark_mutex_delete(mutex);
    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
