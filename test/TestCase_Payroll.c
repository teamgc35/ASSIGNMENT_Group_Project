#include <stdio.h>
#include <assert.h>

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
}

int main()
{
    printf("TestCase Payroll Begin\n");
    TestInit();
}