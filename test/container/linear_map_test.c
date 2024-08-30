#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/container/linear_map_struct.h>

void foreach_helper(void* element, int32_t* context)
{
    uint64_t* const key = element;
    int32_t* const value = element + sizeof(uint64_t);

    *context += *value;
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("linear_map_construct/_destruct")
    {
        Dark_Linear_Map* const linear_map = dark_malloc(allocator, sizeof(*linear_map));

        dark_linear_map_construct_capacity(allocator, linear_map, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 10);
        dark_linear_map_destruct(linear_map);

        dark_linear_map_construct(allocator, linear_map, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));
        dark_linear_map_destruct(linear_map);

        dark_free(allocator, linear_map, sizeof(*linear_map));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_new_capacity/_delete/_capacity/_size")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 10);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_new")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 0);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_array_view")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 5);

        const uint64_t key_1 = 1;
        const uint64_t key_2 = 2;
        const uint64_t key_3 = 3;
        const uint64_t key_4 = 4;
        const uint64_t key_5 = 5;
        const int32_t val = 42;

        dark_linear_map_insert(linear_map, &key_1, &val);
        dark_linear_map_insert(linear_map, &key_2, &val);
        dark_linear_map_insert(linear_map, &key_3, &val);
        dark_linear_map_insert(linear_map, &key_4, &val);
        dark_linear_map_insert(linear_map, &key_5, &val);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 5);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 5);

        const Dark_Array_View array_view = dark_linear_map_array_view(linear_map);

        DARK_TEST_EQ_U(array_view.size, 5);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_buffer_view")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 5);

        const uint64_t key_1 = 1;
        const uint64_t key_2 = 2;
        const uint64_t key_3 = 3;
        const uint64_t key_4 = 4;
        const uint64_t key_5 = 5;
        const int32_t val = 42;

        dark_linear_map_insert(linear_map, &key_1, &val);
        dark_linear_map_insert(linear_map, &key_2, &val);
        dark_linear_map_insert(linear_map, &key_3, &val);
        dark_linear_map_insert(linear_map, &key_4, &val);
        dark_linear_map_insert(linear_map, &key_5, &val);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 5);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 5);

        const Dark_Buffer_View buffer_view = dark_linear_map_buffer_view(linear_map);

        DARK_TEST_EQ_U(buffer_view.byte, 5 * (sizeof(uint64_t) + sizeof(int32_t)));

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_contain_is/inplace")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 10);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        const uint64_t key = 32;

        *(int32_t*)dark_linear_map_inplace(linear_map, &key) = 42;

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 1);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key));

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_value/insert")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 10);

        const uint64_t key_1 = 32;
        const uint64_t key_2 = 33;
        const int32_t val_1 = 42;
        const int32_t val_2 = 43;

        dark_linear_map_insert(linear_map, &key_1, &val_1);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_1));

        DARK_TEST_EQ_I(DARK_LINEAR_MAP_VALUE(linear_map, &key_1, int32_t), 42);

        dark_linear_map_insert(linear_map, &key_1, &val_2);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_1));

        DARK_TEST_EQ_I(DARK_LINEAR_MAP_VALUE(linear_map, &key_1, int32_t), 43);

        DARK_TEST_FALSE(dark_linear_map_contain_is(linear_map, &key_2));

        dark_linear_map_insert(linear_map, &key_2, &val_1);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_2));

        DARK_TEST_EQ_I(DARK_LINEAR_MAP_VALUE(linear_map, &key_1, int32_t), 43);
        DARK_TEST_EQ_I(DARK_LINEAR_MAP_VALUE(linear_map, &key_2, int32_t), 42);

        DARK_TEST_GE_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 2);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_erase")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 10);

        const uint64_t key_1 = 32;
        const uint64_t key_2 = 33;
        const int32_t val_1 = 42;
        const int32_t val_2 = 43;

        dark_linear_map_insert(linear_map, &key_1, &val_1);
        dark_linear_map_insert(linear_map, &key_2, &val_2);

        DARK_TEST_GE_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 2);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_1));
        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_2));

        dark_linear_map_erase(linear_map, &key_2);

        DARK_TEST_GE_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 1);

        DARK_TEST_TRUE(dark_linear_map_contain_is(linear_map, &key_1));
        DARK_TEST_FALSE(dark_linear_map_contain_is(linear_map, &key_2));

        dark_linear_map_erase(linear_map, &key_1);

        DARK_TEST_GE_U(dark_linear_map_capacity(linear_map), 10);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        DARK_TEST_FALSE(dark_linear_map_contain_is(linear_map, &key_1));
        DARK_TEST_FALSE(dark_linear_map_contain_is(linear_map, &key_2));

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_reserve_exact")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 0);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_reserve_exact(linear_map, DARK_LINEAR_MAP_SIZE_MAX - 1);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), DARK_LINEAR_MAP_SIZE_MAX - 1);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_reserve_exact(linear_map, 0);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 0);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_reserve_exact(linear_map, DARK_LINEAR_MAP_SIZE_MAX);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), DARK_LINEAR_MAP_SIZE_MAX);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_shrink_to_fit")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 0);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_reserve_exact(linear_map, DARK_LINEAR_MAP_SIZE_MAX);
        dark_linear_map_shrink_to_fit(linear_map);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 0);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_clear")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 5);

        DARK_TEST_EQ_U(dark_linear_map_capacity(linear_map), 5);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        const uint64_t key_1 = 32;
        const uint64_t key_2 = 33;
        const int32_t val_1 = 42;
        const int32_t val_2 = 43;

        dark_linear_map_insert(linear_map, &key_1, &val_1);
        dark_linear_map_insert(linear_map, &key_2, &val_2);

        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 2);

        dark_linear_map_clear(linear_map);

        DARK_TEST_GE_U(dark_linear_map_capacity(linear_map), 2);
        DARK_TEST_EQ_U(dark_linear_map_size(linear_map), 0);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_ITERATOR")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));

        const uint64_t key_1 = 33;
        const int32_t val_1 = 42;
        const uint64_t key_2 = 23;
        const int32_t val_2 = 22;

        dark_linear_map_insert(linear_map, &key_1, &val_1);
        dark_linear_map_insert(linear_map, &key_2, &val_2);

        Dark_Iterator* const iterator = dark_iterator_new_context(allocator, dark_linear_map_iterator_context_byte());

        dark_linear_map_iterator(linear_map, iterator);

        size_t i = 0;
        while (!dark_iterator_done_is(iterator))
        {
            dark_iterator_peek(iterator);
            dark_iterator_next(iterator);
            i++;
        }

        DARK_TEST_EQ_U(2, i);

        dark_iterator_reset(iterator);

        DARK_TEST_EQ_U(dark_iterator_skip(iterator, i), i);
        DARK_TEST_EQ_U(dark_iterator_skip(iterator, 100), 0);

        dark_iterator_delete(iterator);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_key_byte")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 5);

        DARK_TEST_EQ_U(dark_linear_map_key_byte(linear_map), sizeof(uint64_t));

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_value_byte")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new_capacity(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t), 5);

        DARK_TEST_EQ_U(dark_linear_map_value_byte(linear_map), sizeof(int32_t));

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_foreach")
    {
        Dark_Linear_Map* const linear_map = dark_linear_map_new(allocator, (Dark_Compare)dark_compare_i32, sizeof(uint64_t), sizeof(int32_t));

        const uint64_t key_1 = 33;
        const int32_t val_1 = 42;
        const uint64_t key_2 = 23;
        const int32_t val_2 = 22;

        dark_linear_map_insert(linear_map, &key_1, &val_1);
        dark_linear_map_insert(linear_map, &key_2, &val_2);

        int32_t sum = 0;
        dark_linear_map_foreach(linear_map, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 64);

        dark_linear_map_delete(linear_map);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_map_struct_byte")
    {
        DARK_TEST_GT_U(dark_linear_map_struct_byte(), 0);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
