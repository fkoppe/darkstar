#include <dark/darkstar.h>
#include <dark/darktest.h>

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

        *dark_entropy_get_64(&entropy) = 11;
        *dark_entropy_get_32(&entropy) = 22;
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("uuid4")
    {
        Dark_Entropy entropy = dark_entropy_seed();

        Dark_Uuid4 uuid_1 = dark_uuid4_generate(dark_entropy_get_64(&entropy));
        Dark_Uuid4 uuid_2 = dark_uuid4_generate(dark_entropy_get_64(&entropy));

        DARK_TEST_NE_U(uuid_1.oct[0], uuid_2.oct[0]);
        DARK_TEST_NE_U(uuid_1.oct[1], uuid_2.oct[1]);

        void* ptr = dark_entropy_get_64(&entropy);

        uuid_1 = dark_uuid4_generate(ptr);
        uuid_2 = dark_uuid4_generate(ptr);

        DARK_TEST_NE_U(uuid_1.oct[0], uuid_2.oct[0]);
        DARK_TEST_NE_U(uuid_1.oct[1], uuid_2.oct[1]);

        DARK_TEST_NE_I(dark_uuid4_compare(&uuid_1, &uuid_2), 0);

        char buffer[DARK_UUID4_SIZE_TERMINATED];
        const Dark_Cbuffer cbuffer = { DARK_UUID4_SIZE_TERMINATED, buffer };

        dark_uuid4_write(uuid_1, cbuffer);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("random_splitmix_32")
    {
        uint32_t value = 213;

        dark_random_splitmix_32(&value);

        DARK_TEST_NE_U(value, 213);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("random_splitmix_32")
    {
        uint64_t value = 213;

        dark_random_splitmix_64(&value);

        DARK_TEST_NE_U(value, 213);
    }
    //------------------------

    dark_test_shutdown();

    return DARK_EXIT_SUCCESS;
}
