#include "as_list.h"
#include "as_general.h"
#include "as_array.h"

#include <stdio.h>
#include <assert.h>

static status_t rv;

void Test_CreateList1()
{
    list_t list1;
    list_Init(&list1, 8);
    assert(list1.size == 0);
    assert(list1.element_size == 8);
    rv = list_Destroy(&list1);
    assert(rv == STATUS_OK);
    printf("Create List 1 PASS.\n");
}

void Test_PushBack1()
{
    list_t list;
    list_Init(&list, 4);
    int data = 100;
    assert(list.size == 0);
    assert(list.element_size == 4);
    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 1);
    lnode_t* node = list_Get(&list, 0);
    assert(node);
    assert(*((int*)(node->data)) == data);
    rv = list_Destroy(&list);
    assert(rv == STATUS_OK);
    printf("Push Back 1 PASS.\n");
}

void Test_PushBack2()
{
    list_t list;
    list_Init(&list, 4);
    int data = 100;
    lnode_t *get_data;
    assert(list.size == 0);
    assert(list.element_size == 4);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 1);
    get_data = list_Get(&list, 0);
    assert(get_data);
    assert( *((int*)(get_data->data)) == data);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 2);
    get_data = list_Get(&list, 1);
    assert(get_data);
    assert( *((int*)(get_data->data)) == data);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 3);
    get_data = list_Get(&list, 2);
    assert(get_data);
    assert( *((int*)(get_data->data)) == data);

    rv = list_Destroy(&list);
    assert(rv == STATUS_OK);
    printf("Push Back 2 PASS!.\n");
}

void Test_Finalize()
{
    list_t list;
    array_t arr;
    list_Init(&list, 8);
    double data = 3.1415;
    list_PushBack(&list, &data);
    list_PushBack(&list, &data);
    list_PushBack(&list, &data);
    list_PushBack(&list, &data);
    assert(list.size == 4);
    list_Finalize(&list, &arr);
    assert(arr.capacity == 4);
    double* arr_data = (double*)arr.data;
    assert(arr_data[0] == data);
    assert(arr_data[1] == data);
    assert(arr_data[2] == data);
    assert(arr_data[3] == data);

    printf("Finalize PASS!\n");
}

int main()
{
    Test_CreateList1();
    Test_PushBack1();
    Test_PushBack2();
    Test_Finalize();
    return 0;
}