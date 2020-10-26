#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "as_general.h"
#include "as_payroll.h"

static status_t rv;

void TestInit()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    assert(pr.current_id == 0);
    pr_Destroy(&pr);
    assert(pr.status == PR_DESTROY);
    printf("Test Init PASS!\n");
}

void TestAdd()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 1);
    assert(pr.current_id == 1);

    pr_Destroy(&pr);
    assert(pr.status == PR_DESTROY);
    printf("Test Add PASS!\n");
}

void Test_Getby_ph()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 1);
    assert(pr.current_id == 1);
    record_t *added_rec = pr_Getby_ph(&pr, "13281122813");
    assert(added_rec->id == 1);
    assert(added_rec->pay_rate = 35.5);
    assert(added_rec->rank == RK_MANAGER);
    assert(added_rec->hours_worked == 5.5);
    assert(!strcmp(added_rec->first_name, "Xiao"));
    assert(!strcmp(added_rec->last_name, "ZHONG"));
    assert(!strcmp(added_rec->phone, "13281122813"));
    assert(!strcmp(added_rec->email, "zhongxiao0711@gmail.com"));

    pr_Destroy(&pr);
    assert(pr.status == PR_DESTROY);
    printf("Test Getby_ph PASS!\n");
}

void Test_Getby_em()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 1);
    assert(pr.current_id == 1);
    record_t *added_rec = pr_Getby_em(&pr, "zhongxiao0711@gmail.com");
    assert(added_rec->id == 1);
    assert(added_rec->pay_rate = 35.5);
    assert(added_rec->rank == RK_MANAGER);
    assert(added_rec->hours_worked == 5.5);
    assert(!strcmp(added_rec->first_name, "Xiao"));
    assert(!strcmp(added_rec->last_name, "ZHONG"));
    assert(!strcmp(added_rec->phone, "13281122813"));
    assert(!strcmp(added_rec->email, "zhongxiao0711@gmail.com"));
    rechead_print();
    rec_print(added_rec);

    pr_Destroy(&pr);
    assert(pr.status == PR_DESTROY);
    printf("Test Getby_em PASS!\n");
}

void Test_Find()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "Xiao", "ZHONG", "13281122814", "zhongxiao0712@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "Xiao", "ZHONG", "13281122815", "zhongxiao0713@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 3);
    assert(pr.current_id == 3);

    record_t *result;
    uint64_t len;
    len = pr_Find(&pr, &result, "Xiao", "ZHONG");
    assert(len == 3);
    for(uint64_t i = 0; i < len; i++)
    {
        assert(!strcmp(result[i].first_name, "Xiao"));
        assert(!strcmp(result[i].last_name, "ZHONG"));
    }

    pr_Destroy(&pr);
    printf("Test Find PASS!\n");
}

void Test_Findln()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "zzzz", "ZHONG", "13281122814", "zhongxiao0712@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "bbbb", "ZHONG", "13281122815", "zhongxiao0713@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 3);
    assert(pr.current_id == 3);

    record_t *result;
    uint64_t len;
    len = pr_Findln(&pr, &result, "ZHONG");
    assert(len == 3);
    assert(!strcmp(result[0].first_name, "Xiao"));
    assert(!strcmp(result[0].last_name, "ZHONG"));

    assert(!strcmp(result[1].first_name, "zzzz"));
    assert(!strcmp(result[1].last_name, "ZHONG"));

    assert(!strcmp(result[2].first_name, "bbbb"));
    assert(!strcmp(result[2].last_name, "ZHONG"));

    pr_Destroy(&pr);
    printf("Test Findln PASS!\n");
}

void Test_Findfn()
{
    pr_header_t pr;
    rv = pr_Init(&pr, "payroll_1", "123aaa");
    assert(rv == 0);
    assert(pr.status == PR_ACCESS);
    record_t rec;
    rec_Build(&rec, "Xiao", "ZHONG", "13281122813", "zhongxiao0711@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "Xiao", "zzzz", "13281122814", "zhongxiao0712@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    rec_Build(&rec, "Xiao", "bbbb", "13281122815", "zhongxiao0713@gmail.com", RK_MANAGER, 5.5, 35.5);
    rv = pr_Add(&pr, &rec);
    assert(rv == 0);
    assert(pr.size == 3);
    assert(pr.current_id == 3);

    record_t *result;
    uint64_t len;
    len = pr_Findfn(&pr, &result, "Xiao");
    assert(len == 3);
    assert(!strcmp(result[0].first_name, "Xiao"));
    assert(!strcmp(result[0].last_name, "ZHONG"));

    assert(!strcmp(result[1].first_name, "Xiao"));
    assert(!strcmp(result[1].last_name, "zzzz"));

    assert(!strcmp(result[2].first_name, "Xiao"));
    assert(!strcmp(result[2].last_name, "bbbb"));

    pr_Destroy(&pr);
    printf("Test Findfn PASS!\n");
}

int main()
{
    printf("TestCase Payroll Begin\n");
    TestInit();
    TestAdd();
    Test_Getby_ph();
    Test_Getby_em();
    Test_Find();
    Test_Findln();
    Test_Findfn();
}
