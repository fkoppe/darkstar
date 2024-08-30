#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/container/linear_queue_struct.h>

void foreach_helper(int32_t* element, int32_t* context)
{
    *context += *element;
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("linear_queue_construct/_destruct")
    {
        Dark_Linear_Queue* const linear_queue = dark_malloc(allocator, sizeof(*linear_queue));;

        dark_linear_queue_construct(allocator, linear_queue, dark_growth_simple, sizeof(int));
        dark_linear_queue_destruct(linear_queue);

        dark_free(allocator, linear_queue, sizeof(*linear_queue));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_new_capacity/_delete/_capacity/_size")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 10);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 10);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_new")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_at/LINEAR_QUEUE_AT")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 5);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 22);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 33);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 2, int), 44);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 3, int), 55);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 4, int), 66);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_front/LINEAR_QUEUE_FRONT")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_FRONT(linear_queue, int), 22);

        *(int*)dark_linear_queue_front(linear_queue) = 42;

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_FRONT(linear_queue, int), 42);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue/LINEAR_QUEUE_BACK")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_BACK(linear_queue, int), 66);

        *(int*)dark_linear_queue_back(linear_queue) = 42;

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_BACK(linear_queue, int), 42);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_data/LINEAR_QUEUE_DATA")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(*DARK_LINEAR_QUEUE_DATA(linear_queue, int), 22);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_array")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array_buf = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array_buf));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 5);

        const Dark_Array array = dark_linear_queue_array(linear_queue);

        DARK_TEST_EQ_U(array.size, 5);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_array_view")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array_buf = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array_buf));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 5);

        const Dark_Array_View array_view = dark_linear_queue_array_view(linear_queue);

        DARK_TEST_EQ_U(array_view.size, 5);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_emplace")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int* pos_1 = dark_linear_queue_emplace(linear_queue, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 33);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 35);

        int* pos_2 = dark_linear_queue_emplace(linear_queue, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 6);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 6);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 33);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 35);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 2, int), 1);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 3, int), 2);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 4, int), 3);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 5, int), 4);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_emplace_array")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        const Dark_Array array = dark_linear_queue_emplace_array(linear_queue, 10);

        DARK_TEST_EQ_U(array.size, 10);

        DARK_LINEAR_QUEUE_AT(linear_queue, 9, int) = 42;

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_inplace")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        *(int*)dark_linear_queue_inplace(linear_queue) = 705;

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 705);

        *(int*)dark_linear_queue_inplace(linear_queue) = 1;

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 2);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 2);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 705);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 1);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_inplace_array")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        *((int*)(dark_linear_queue_inplace_array(linear_queue).data)) = 705;

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 705);

        *((int*)(dark_linear_queue_inplace_array(linear_queue).data)) = 7;

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 7);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 2);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 2);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 705);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 7);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_push")
    {
        int buffer[2] = { 333, 666666 };
        const Dark_Array array = { sizeof(int), 2, buffer };

        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 666666);

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 2, int), 333);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 3, int), 666666);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 4);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 4);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_insert")
    {
        int a = 333;
        int b  = 666666;

        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_insert(linear_queue, &a);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 333);

        dark_linear_queue_insert(linear_queue, &b);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 666666);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 2);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 2);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_pop")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        dark_linear_queue_pop(linear_queue, 3);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 2);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 10);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 20);

        dark_linear_queue_pop(linear_queue, 2);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_erase")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        dark_linear_queue_erase(linear_queue);
        dark_linear_queue_erase(linear_queue);
        dark_linear_queue_erase(linear_queue);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 2);

        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 0, int), 10);
        DARK_TEST_EQ_U(DARK_LINEAR_QUEUE_AT(linear_queue, 1, int), 20);

        dark_linear_queue_erase(linear_queue);
        dark_linear_queue_erase(linear_queue);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_reserve/_additional")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve(linear_queue, 100);

        const size_t capacity = dark_linear_queue_capacity(linear_queue);
        DARK_TEST_GE_U(capacity, 100);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve(linear_queue, 0);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), capacity);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve(linear_queue, 101);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 101);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve_additional(linear_queue, 101);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 202);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_reserve_exact")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve_exact(linear_queue, 100);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 100);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve_exact(linear_queue, 0);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve_exact(linear_queue, 101);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 101);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_shrink_to_fit")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_reserve_exact(linear_queue, 100);
        dark_linear_queue_shrink_to_fit(linear_queue);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_shrink")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 0);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));
        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 10);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 10);

        dark_linear_queue_shrink(linear_queue, 9);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 10);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 9);

        dark_linear_queue_shrink(linear_queue, 5);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 10);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 5);

        dark_linear_queue_shrink(linear_queue, 0);

        DARK_TEST_GE_U(dark_linear_queue_capacity(linear_queue), 10);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_clear")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 5);

        dark_linear_queue_clear(linear_queue);

        DARK_TEST_EQ_U(dark_linear_queue_capacity(linear_queue), 5);
        DARK_TEST_EQ_U(dark_linear_queue_size(linear_queue), 0);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_ITERATOR")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int));

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        Dark_Iterator* const iterator = dark_iterator_new_context(allocator, dark_linear_queue_iterator_context_byte());

        dark_linear_queue_iterator(linear_queue, iterator);

        size_t i = 0;
        while (!dark_iterator_done_is(iterator))
        {
            dark_iterator_peek(iterator);
            dark_iterator_next(iterator);
            i++;
        }

        DARK_TEST_EQ_U(5, i);

        dark_iterator_reset(iterator);

        DARK_TEST_EQ_U(dark_iterator_skip(iterator, i), i);
        DARK_TEST_EQ_U(dark_iterator_skip(iterator, 100), 0);

        dark_iterator_delete(iterator);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_element_byte")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_linear_queue_element_byte(linear_queue), sizeof(int));

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_foreach")
    {
        Dark_Linear_Queue* const linear_queue = dark_linear_queue_new(allocator, dark_growth_standard, sizeof(int32_t));

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_linear_queue_push(linear_queue, dark_array_to_view(array));

        int32_t sum = 0;
        dark_linear_queue_foreach(linear_queue, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 444);

        dark_linear_queue_delete(linear_queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("linear_queue_struct_byte")
    {
        DARK_TEST_GT_U(dark_linear_queue_struct_byte(), 0);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
