#include <dark/darkstar.h>

int main()
{
    const uint64_t val_1 = 0xBD4732262FEB6E95;
    const uint64_t val_2 = 0x28EFE333B266F183;

    Dark_Entropy entropy = dark_entropy_seed();
    Dark_Uuid4 uuid = dark_uuid4_generate(dark_entropy_get_64(&entropy));

    DARK_TEST_EQ_U(uuid.oct[0], val_1);
    DARK_TEST_EQ_U(uuid.oct[1], val_2);

    return EXIT_SUCCESS;
}
