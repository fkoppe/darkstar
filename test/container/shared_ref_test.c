#include <dark/darkstar.h>
#include <dark/darktest.h>

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("shared_ref_create/_destroy")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);
        dark_shared_ref_destroy(shared);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("shared_ref_copy")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Shared_Ref shared_copy = dark_shared_ref_copy(shared);

        dark_shared_ref_destroy(shared);

        DARK_SHARED_REF_DATA(shared_copy, uint64_t) = 991199;

        dark_shared_ref_destroy(shared_copy);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("shared_ref_shared_count/_weak_count")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(shared), 1);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(shared), 0);

        const Dark_Shared_Ref shared_copy = dark_shared_ref_copy(shared);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(shared), 2);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(shared), 0);

        dark_shared_ref_destroy(shared);

        DARK_TEST_EQ_U(dark_shared_ref_shared_count(shared), 1);
        DARK_TEST_EQ_U(dark_shared_ref_weak_count(shared), 0);

        DARK_SHARED_REF_DATA(shared_copy, uint64_t) = 991199;

        dark_shared_ref_destroy(shared_copy);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("shared_ref_unlock")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        const Dark_Weak_Ref weak = dark_shared_ref_unlock(shared);

        dark_weak_ref_destroy(weak);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("shared_ref_byte/_data")
    {
        uint64_t a = 12345;
        const Dark_Shared_Ref shared = dark_shared_ref_create(allocator, sizeof(a), &a);

        DARK_TEST_EQ_U(sizeof(a), dark_shared_ref_byte(shared));
        DARK_TEST_EQ_M(&a, dark_shared_ref_data(shared), sizeof(a));

        dark_shared_ref_destroy(shared);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
