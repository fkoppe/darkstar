    #include <dark/darkstar.h>

int main()
{
    //----------TEST#1----------
    DARK_TEST("GROWTH_VALUE#1")
    {
        const Dark_Growth growth = { 0.0f, 10, 0 };
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(0, growth), 10);
    }
    //--------------------------

    //----------TEST#2----------
    DARK_TEST("GROWTH_VALUE#2")
    {
        const Dark_Growth growth = { 2.0f, 0, 4};
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(8, growth), 4);
    }
    //--------------------------

    //----------TEST#3----------
    DARK_TEST("GROWTH_VALUE#3")
    {
        const Dark_Growth growth = { 2.0f, 20, 20};
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(8, growth), 20);
    }
    //--------------------------

    //----------TEST#4----------
    DARK_TEST("GROWTH_VALUE#4")
    {
        const Dark_Growth growth = { 2.0f, 0, 0};
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(8, growth), 16);
    }
    //--------------------------

    //----------TEST#5----------
    DARK_TEST("GROWTH_APPLIED")
    {
        const Dark_Growth growth = { 2.0f, 0, 0};
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(8, growth), 24);
    }
    //--------------------------

    //----------TEST#6----------
    DARK_TEST("GROWTH_STANDARD")
    {
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(0, DARK_GROWTH_STANDARD), 1);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(1, DARK_GROWTH_STANDARD), 1);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(2, DARK_GROWTH_STANDARD), 1);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(3, DARK_GROWTH_STANDARD), 1);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(4, DARK_GROWTH_STANDARD), 2);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(5, DARK_GROWTH_STANDARD), 2);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(6, DARK_GROWTH_STANDARD), 3);
        DARK_TEST_EQ_U(DARK_GROWTH_VALUE(100, DARK_GROWTH_STANDARD), 50);

        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(0, DARK_GROWTH_STANDARD), 1);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(1, DARK_GROWTH_STANDARD), 2);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(2, DARK_GROWTH_STANDARD), 3);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(3, DARK_GROWTH_STANDARD), 4);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(4, DARK_GROWTH_STANDARD), 6);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(5, DARK_GROWTH_STANDARD), 7);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(6, DARK_GROWTH_STANDARD), 9);
        DARK_TEST_EQ_U(DARK_GROWTH_APPLIED(100, DARK_GROWTH_STANDARD), 150);
    }
    //--------------------------

    dark_test_end();

    return EXIT_SUCCESS;
}
