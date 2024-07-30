#include <dark/darkstar.h>
#include <dark/darktest.h>

bool foreach_helper(int32_t* element, int32_t* context)
{
    *context += *element;
}

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
    DARK_TEST("array_view")
    {
        int buffer[12] = { 0 };

        Dark_Array array = { .data = buffer, .size = 12, .element_byte = sizeof(int32_t)};
        dark_array_view(array);
    }
    //--------------------------

    //----------TEST----------
    DARK_TEST("array_foreach")
    {
        int buffer[5] = { 0, 1, 2, 3, 4 };

        Dark_Array array = { .data = buffer, .size = 5, .element_byte = sizeof(int32_t)};

        int32_t sum = 0;
        dark_array_foreach(array, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 10);
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
