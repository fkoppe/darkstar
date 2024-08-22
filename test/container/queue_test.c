#include <dark/darkstar.h>
#include <dark/darktest.h>

#include <dark/container/queue_struct.h>

void foreach_helper(int32_t* element, int32_t* context)
{
    *context += *element;
}

int main()
{
    Dark_Allocator* const allocator = dark_os_allocator_new();

    dark_test_initialise();

    //----------TEST----------
    DARK_TEST("queue_construct/_destruct")
    {
        Dark_Queue* const queue = dark_malloc(allocator, sizeof(*queue));;

        dark_queue_construct_capacity(allocator, queue, dark_growth_simple, sizeof(int), 1);
        dark_queue_destruct(queue);

        dark_queue_construct(allocator, queue, dark_growth_simple, sizeof(int));
        dark_queue_destruct(queue);

        dark_free(allocator, queue, sizeof(*queue));
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_new_capacity/_delete/_capacity")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 10);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 10);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_new")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_at/QUEUE_AT")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 5);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 22);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 33);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 2, int), 44);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 3, int), 55);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 4, int), 66);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_front/QUEUE_FRONT")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_QUEUE_FRONT(queue, int), 22);

        *(int*)dark_queue_front(queue) = 42;

        DARK_TEST_EQ_U(DARK_QUEUE_FRONT(queue, int), 42);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue/QUEUE_BACK")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_QUEUE_BACK(queue, int), 66);

        *(int*)dark_queue_back(queue) = 42;

        DARK_TEST_EQ_U(DARK_QUEUE_BACK(queue, int), 42);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_data/QUEUE_DATA")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 22, 33, 44, 55, 66 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(*DARK_QUEUE_DATA(queue, int), 22);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_array")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array_buf = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array_buf));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 5);

        const Dark_Array array = dark_queue_array(queue);

        DARK_TEST_EQ_U(array.size, 5);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_array_view")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array_buf = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array_buf));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 5);

        const Dark_Array_View array_view = dark_queue_array_view(queue);

        DARK_TEST_EQ_U(array_view.size, 5);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_emplace")
    {
        int buffer_1[2] = { 33, 35 };
        int buffer_2[4] = { 1, 2, 3, 4 };

        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int* pos_1 = dark_queue_emplace(queue, 2);
        pos_1[0] = buffer_1[0];
        pos_1[1] = buffer_1[1];

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 33);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 35);

        int* pos_2 = dark_queue_emplace(queue, 4);
        pos_2[0] = buffer_2[0];
        pos_2[1] = buffer_2[1];
        pos_2[2] = buffer_2[2];
        pos_2[3] = buffer_2[3];

        DARK_TEST_GE_U(dark_queue_capacity(queue), 6);
        DARK_TEST_EQ_U(dark_queue_size(queue), 6);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 33);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 35);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 2, int), 1);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 3, int), 2);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 4, int), 3);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 5, int), 4);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_emplace_array")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        const Dark_Array array = dark_queue_emplace_array(queue, 10);

        DARK_TEST_EQ_U(array.size, 10);

        DARK_QUEUE_AT(queue, 9, int) = 42;

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_inplace")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        *(int*)dark_queue_inplace(queue) = 705;

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 705);

        *(int*)dark_queue_inplace(queue) = 1;

        DARK_TEST_GE_U(dark_queue_capacity(queue), 2);
        DARK_TEST_EQ_U(dark_queue_size(queue), 2);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 705);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 1);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_inplace_array")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        *((int*)(dark_queue_inplace_array(queue).data)) = 705;

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 705);

        *((int*)(dark_queue_inplace_array(queue).data)) = 7;

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 7);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 2);
        DARK_TEST_EQ_U(dark_queue_size(queue), 2);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 705);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 7);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_push")
    {
        int buffer[2] = { 333, 666666 };
        const Dark_Array array = { sizeof(int), 2, buffer };

        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 666666);

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 666666);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 2, int), 333);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 3, int), 666666);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 4);
        DARK_TEST_EQ_U(dark_queue_size(queue), 4);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_insert")
    {
        int a = 333;
        int b  = 666666;

        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_insert(queue, &a);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 333);

        dark_queue_insert(queue, &b);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 333);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 666666);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 2);
        DARK_TEST_EQ_U(dark_queue_size(queue), 2);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_pop")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        dark_queue_pop(queue, 3);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 2);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 10);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 20);

        dark_queue_pop(queue, 2);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_erase")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 10, 20, 55, 6, 999 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        dark_queue_erase(queue);
        dark_queue_erase(queue);
        dark_queue_erase(queue);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 2);

        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 0, int), 10);
        DARK_TEST_EQ_U(DARK_QUEUE_AT(queue, 1, int), 20);

        dark_queue_erase(queue);
        dark_queue_erase(queue);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_reserve/_additional")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve(queue, 100);

        const size_t capacity = dark_queue_capacity(queue);
        DARK_TEST_GE_U(capacity, 100);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve(queue, 0);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), capacity);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve(queue, 101);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 101);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve_additional(queue, 101);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 202);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_reserve_exact")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve_exact(queue, 100);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 100);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve_exact(queue, 0);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve_exact(queue, 101);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 101);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_shrink_to_fit")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_reserve_exact(queue, 100);
        dark_queue_shrink_to_fit(queue);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_shrink")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 0);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));
        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_GE_U(dark_queue_capacity(queue), 10);
        DARK_TEST_EQ_U(dark_queue_size(queue), 10);

        dark_queue_shrink(queue, 9);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 10);
        DARK_TEST_EQ_U(dark_queue_size(queue), 9);

        dark_queue_shrink(queue, 5);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 10);
        DARK_TEST_EQ_U(dark_queue_size(queue), 5);

        dark_queue_shrink(queue, 0);

        DARK_TEST_GE_U(dark_queue_capacity(queue), 10);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_clear")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        DARK_TEST_EQ_U(dark_queue_size(queue), 5);

        dark_queue_clear(queue);

        DARK_TEST_EQ_U(dark_queue_capacity(queue), 5);
        DARK_TEST_EQ_U(dark_queue_size(queue), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_ITERATE")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int));

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        Dark_Iterator* const iterator = dark_queue_iterate(queue);

        size_t i = 0;
        while (!dark_iterator_done(iterator))
        {
            dark_iterator_peek(iterator);
            dark_iterator_next(iterator);

            i++;
        }

        DARK_TEST_EQ_U(5, i);

        dark_iterator_reset(iterator);

        DARK_TEST_EQ_U(dark_iterator_skip(iterator, i), i);
        DARK_TEST_EQ_U(dark_iterator_skip(iterator, 100), 0);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_element_byte")
    {
        Dark_Queue* const queue = dark_queue_new_capacity(allocator, dark_growth_standard, sizeof(int), 5);

        DARK_TEST_EQ_U(dark_queue_element_byte(queue), sizeof(int));

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_foreach")
    {
        Dark_Queue* const queue = dark_queue_new(allocator, dark_growth_standard, sizeof(int32_t));

        int32_t buffer[5] = { 1, 333, 111, 0, -1 };
        const Dark_Array array = { sizeof(int32_t), 5, buffer };

        dark_queue_push(queue, dark_array_to_view(array));

        int32_t sum = 0;
        dark_queue_foreach(queue, &sum, (Dark_Foreach)foreach_helper);

        DARK_TEST_EQ_I(sum, 444);

        dark_queue_delete(queue);
    }
    //------------------------

    //----------TEST----------
    DARK_TEST("queue_struct_byte")
    {
        DARK_TEST_GT_U(dark_queue_struct_byte(), 0);
    }
    //------------------------

    dark_test_shutdown();

    dark_os_allocator_delete(allocator);

    return DARK_EXIT_SUCCESS;
}
