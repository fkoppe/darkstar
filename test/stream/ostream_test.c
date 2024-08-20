#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/stream/ostream_struct.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();
    Dark_Mutex* mutex = dark_mutex_new(allocator);

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("ostream_construct/destruct")
    {
        Dark_Ostream_Settings ostream_settings;
        ostream_settings.keep_open_is = false;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 0;
        ostream_settings.auto_flush_ns = 0;

        Dark_Ostream* const ostream = dark_malloc(allocator, sizeof(*ostream));

        dark_ostream_construct_file(allocator, ostream, ostream_settings, "test.txt", NULL);
        dark_ostream_destruct(ostream);

        dark_ostream_construct_stdout(allocator, ostream, ostream_settings, NULL);
        dark_ostream_destruct(ostream);

        dark_ostream_construct_stderr(allocator, ostream, ostream_settings, NULL);
        dark_ostream_destruct(ostream);

        dark_free(allocator, ostream, sizeof(*ostream));
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_new/_delete")
    {
        Dark_Ostream_Settings ostream_settings;
        ostream_settings.keep_open_is = false;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 0;
        ostream_settings.auto_flush_ns = 0;

        Dark_Ostream* ostream = dark_ostream_new_file(allocator, ostream_settings, "test.txt", NULL);
        dark_ostream_delete(ostream);

        ostream = dark_ostream_new_stdout(allocator, ostream_settings, NULL);
        dark_ostream_delete(ostream);

        ostream = dark_ostream_new_stderr(allocator, ostream_settings, NULL);
        dark_ostream_delete(ostream);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_flush_unbuffered")
    {
        const char buffer[] = { "test message larger than buffer" };
        const Dark_Buffer_View view = { sizeof(buffer), buffer };

        Dark_Ostream_Settings ostream_settings;
        ostream_settings.keep_open_is = false;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 10;
        ostream_settings.auto_flush_ns = 0;

        Dark_Ostream* const ostream = dark_ostream_new_file(allocator, ostream_settings, "test.txt", NULL);

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
        ostream_settings.keep_open_is = false;
        ostream_settings.binary_is = false;
        ostream_settings.force_size_is = false;
        ostream_settings.buffer_size = 10;
        ostream_settings.auto_flush_ns = 0;

        Dark_Ostream* const ostream = dark_ostream_new_file(allocator, ostream_settings, "test.txt", NULL);

        dark_ostream_write(ostream, view);
        dark_ostream_flush(ostream);

        dark_ostream_delete(ostream);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("ostream_struct_byte")
    {
        DARK_TEST_GT_U(dark_ostream_struct_byte(), 0);
    }
    //--------------------------

    dark_test_shutdown();

    dark_mutex_delete(mutex);
    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
