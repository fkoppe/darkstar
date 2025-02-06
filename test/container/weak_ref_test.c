#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("weak_ref_create")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Weak_Ref weak = dark_weak_ref_create(shared);

        dark_shared_ref_destroy(shared);

        dark_weak_ref_destroy(weak);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("weak_ref_copy/valid_is")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref original = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Weak_Ref weak = dark_weak_ref_create(original);

        const Dark_Weak_Ref weak_copy = dark_weak_ref_copy(weak);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(original), 1);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(original), 2);

        DARK_TEST_TRUE(dark_weak_ref_valid_is(weak_copy));

        dark_shared_ref_destroy(original);

        DARK_TEST_FALSE(dark_weak_ref_valid_is(weak_copy));

        dark_weak_ref_destroy(weak_copy);
        dark_weak_ref_destroy(weak);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("weak_ref_shared_count/_weak_count")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref original = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Weak_Ref weak = dark_weak_ref_create(original);

        const Dark_Weak_Ref weak_copy = dark_weak_ref_copy(weak);

        DARK_TEST_EQ_U(dark_weak_ref_shared_count(weak), 1);
        DARK_TEST_EQ_U(dark_weak_ref_weak_count(weak), 2);

        DARK_TEST_TRUE(dark_weak_ref_valid_is(weak_copy));

        dark_shared_ref_destroy(original);

        DARK_TEST_EQ_U(dark_weak_ref_shared_count(weak), 0);
        DARK_TEST_EQ_U(dark_weak_ref_weak_count(weak), 2);
        DARK_TEST_EQ_U(dark_weak_ref_shared_count(weak_copy), 0);
        DARK_TEST_EQ_U(dark_weak_ref_weak_count(weak_copy), 2);

        DARK_TEST_FALSE(dark_weak_ref_valid_is(weak_copy));

        dark_weak_ref_destroy(weak_copy);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("weak_ref_unlock")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref original = dark_shared_ref_create(allocator, sizeof(a), &a);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(original), 1);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(original), 0);

        const Dark_Weak_Ref weak = dark_shared_ref_unlock(original);

        DARK_TEST_EQ_U(dark_weak_ref_shared_count(weak), 0);
        DARK_TEST_EQ_U(dark_weak_ref_weak_count(weak), 1);

        const Dark_Shared_Ref other = dark_weak_ref_lock(weak);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(other), 1);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(other), 0);

        dark_shared_ref_destroy(other);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("weak_ref_byte/_data")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Weak_Ref weak = dark_weak_ref_create(shared);

        dark_shared_ref_destroy(shared);

        DARK_TEST_EQ_U(sizeof(a), dark_weak_ref_byte(weak));

        dark_weak_ref_destroy(weak);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
