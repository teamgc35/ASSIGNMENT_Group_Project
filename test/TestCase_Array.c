#include "as_array.h"
#include <assert.h>
#include <stdio.h>

void Test_CreateArray1()
{
    array_t arr;
    array_Init(&arr, 10, 8, NULL);
    assert(arr.size == 0);
    assert(arr.capacity == 10);
    assert(arr.data);
    printf("Test Create Array PASS!\n");
}

void Test_Destroy()
{
    array_t arr;
    array_Init(&arr, 10, 8, NULL);
    array_Destroy(&arr);
    assert(arr.size == 0);
    assert(arr.element_size == 0);
    assert(arr.capacity == 0);
    assert(arr.data == NULL);
    printf("Test Destroy PASS!\n");
}

void Test_PushBack()
{
    array_t arr;
    double data[] = {1, 2, 3, 4};
    array_Init(&arr, 10, 8, NULL);
    array_PushBack(&arr, data);
    array_PushBack(&arr, data + 1);
    array_PushBack(&arr, data + 2);
    array_PushBack(&arr, data + 3);
    assert(arr.size == 4);
    assert(arr.capacity == 10);
    assert(arr.element_size == 8);
    assert(arr.data);
    double *buffer = (double *)arr.data;
    assert(buffer[0] == data[0]);
    assert(buffer[1] == data[1]);
    assert(buffer[2] == data[2]);
    assert(buffer[3] == data[3]);
    array_Destroy(&arr);
    printf("Test Push Back PASS\n");
}

void Test_Get()
{
    array_t arr;
    double data[] = {1, 2, 3, 4};
    array_Init(&arr, 10, 8, NULL);
    array_PushBack(&arr, data);
    array_PushBack(&arr, data + 1);
    array_PushBack(&arr, data + 2);
    array_PushBack(&arr, data + 3);
    assert(arr.size == 4);
    assert(arr.capacity == 10);
    assert(arr.element_size == 8);
    assert(arr.data);
    double num = *((double *)array_Get(&arr, 0));
    assert(num == data[0]);
    num = *((double *)array_Get(&arr, 1));
    assert(num == data[1]);
    num = *((double *)array_Get(&arr, 2));
    assert(num == data[2]);
    num = *((double *)array_Get(&arr, 3));
    assert(num == data[3]);
    array_Destroy(&arr);
    printf("Test Get PASS!\n");
}

typedef struct entity
{
    int x;
    int y;
    int z;
} entity_t;

int FindCondition(const void *elem, const void *desire)
{
    entity_t *e = (entity_t *)elem;
    entity_t *d = (entity_t *)desire;
    if (e->x == d->x && e->y == d->y && e->z == d->z)
        return 1;
    return 0;
}
void Test_Find()
{
    array_t arr;
    status_t rv;
    int64_t find_index;
    array_Init(&arr, 10, sizeof(entity_t), FindCondition);
    entity_t e1 = {1, 1, 1};
    entity_t e2 = {1, 2, 3};

    rv = array_PushBack(&arr, &e1);
    assert(rv == 0);
    array_PushBack(&arr, &e2);
    assert(rv == 0);

    find_index = array_Find(&arr, &e2);
    assert(find_index == 1);
    printf("Test Find PASS!\n");
}

int main()
{
    Test_CreateArray1();
    Test_Destroy();
    Test_PushBack();
    Test_Get();
    Test_Find();
}