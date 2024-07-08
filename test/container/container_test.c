#include <dark/darkstar.h>
#include <dark/darktest.h>

bool next_is_helper(void* context)
{
    return true;
}

void* next_helper(void* context)
{
    return next_is_helper;
}

static const Dark_Iterator_Struct custom_iterator_struct = { next_is_helper, next_helper, next_helper };

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("array")
    {
        Dark_Array array = { .data = NULL, .size = 0, .element_size = 0};
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("iterator")
    {
        DARK_TEST_TRUE(dark_iterator_next_is((Dark_Iterator*)&custom_iterator_struct));
        DARK_TEST_NE_P(NULL, dark_iterator_next((Dark_Iterator*)&custom_iterator_struct));
    }
    //--------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}