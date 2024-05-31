#include <dark/darkstar.h>
#include <dark/test.h>

int main()
{
    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("entropy")
    {
        Dark_Entropy entropy = dark_entropy_seed();

        void* ptr_1 = dark_entropy_get_64(&entropy);
        void* ptr_2 = dark_entropy_get_64(&entropy);

        DARK_TEST_NE_M(&ptr_1, &ptr_2, sizeof(void*));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("uuid")
    {
        Dark_Entropy entropy = dark_entropy_seed();

        void* ptr = dark_entropy_get_64(&entropy);

        Dark_Uuid4 uuid_1 = dark_uuid4_generate(dark_entropy_get_64(&entropy));
        Dark_Uuid4 uuid_2 = dark_uuid4_generate(dark_entropy_get_64(&entropy));

        DARK_TEST_NE_U(uuid_1.oct[0], uuid_2.oct[0]);
        DARK_TEST_NE_U(uuid_1.oct[1], uuid_2.oct[1]);

        uuid_1 = dark_uuid4_generate(ptr);
        uuid_2 = dark_uuid4_generate(ptr);

        DARK_TEST_NE_U(uuid_1.oct[0], uuid_2.oct[0]);
        DARK_TEST_NE_U(uuid_1.oct[1], uuid_2.oct[1]);
    }
    //------------------------

    dark_test_shutdown();

    return dark_test_return();
}
