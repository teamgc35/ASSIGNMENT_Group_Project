#include "as_list.h"
#include "as_general.h"

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
    printf("Create List 1 Success.\n");
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
    int *get_data = list_Get(&list, 0);
    assert(get_data);
    assert((*get_data) == data);
    rv = list_Destroy(&list);
    assert(rv == STATUS_OK);
    printf("Push Back 1 Success.\n");
}

void Test_PushBack2()
{
    list_t list;
    list_Init(&list, 4);
    int data = 100;
    int *get_data;
    assert(list.size == 0);
    assert(list.element_size == 4);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 1);
    get_data = list_Get(&list, 0);
    assert(get_data);
    assert((*get_data) == data);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 2);
    get_data = list_Get(&list, 1);
    assert(get_data);
    assert((*get_data) == data);

    rv = list_PushBack(&list, &data);
    assert(rv == STATUS_OK);
    assert(list.size == 3);
    get_data = list_Get(&list, 2);
    assert(get_data);
    assert((*get_data) == data);

    rv = list_Destroy(&list);
    assert(rv == STATUS_OK);
    printf("Push Back 2 Success.\n");
}

int main()
{
    Test_CreateList1();
    Test_PushBack1();
    Test_PushBack2();
    return 0;
}