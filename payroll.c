#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "as_payroll.h"
#include "as_general.h"

static int menu();
static void call(int choice);
static void cli_help();
static void add_record();
static void display_all();
static void search_record();
static enum rank choose_rank();

static pr_header_t payroll;
static status_t rv;
static char TMP_BUFF[256];
static void buff_clean();

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        char filename[MAX_PRNAME_LEN+1];
        char passwd[MAX_PASSWD_LEN+1];

        printf("Since a payroll filename is not given, a new payroll file will be created.\n");
        printf("Please enter the payroll file name (max 31 char): ");
        buff_clean();
        scanf("%s",TMP_BUFF);
        while(!checkfmt_filename(TMP_BUFF))
        {
            printf("Incorrect payroll filename format. Please try again: ");
            buff_clean();
            scanf("%s",TMP_BUFF);
        }
        _DEBUG("Payroll filename format pass.");
        strncpy(filename, TMP_BUFF, MAX_PRNAME_LEN);
        /* Ask user to set a payroll file password */
        printf("Please set a new password for the payroll file: ");
        buff_clean();
        scanf("%s",TMP_BUFF);
        while (!checkfmt_passwd(TMP_BUFF))
        {
            printf("Incorrect payroll password format. Please try again: ");
            buff_clean();
            scanf("%s",TMP_BUFF);
        }
        _DEBUG("Payroll file password format pass.");
        strncpy(passwd, TMP_BUFF, MAX_PASSWD_LEN);
        /* Create a new payroll header */
        rv = pr_Init(&payroll, filename, passwd);
        if (rv != STATUS_OK)
        {
            _DEBUGF("Failed to create a new payroll (%d).", rv);
            return 1;
        }
    } else {
        /* If a payroll filename is specific, open it */
        /* Checking user entered filename is correct format */
        if (!checkfmt_filename(argv[1]))
        {
            _DEBUG("Incorrect payroll filename format.");
            return 1;
        }
        /* Ask the user to enter payroll file access password */
        printf("Please enter the payroll file password: ");
        /* clean TMP_BUFF */
        buff_clean();
        scanf("%s", TMP_BUFF);
        while (!checkfmt_passwd(TMP_BUFF))
        {
            printf("Incorrect payroll file password. Please Try again: ");
            buff_clean();
            scanf("%s", TMP_BUFF);
        }
        _DEBUG("Password format check pass.");

        /* Load the payroll file to memory */
        rv = pr_Load(&payroll, argv[1], TMP_BUFF);
    }

    int choice;
    while (1)
    {
        choice = menu();
        if (choice == 4)
            return 0;
        call(choice);
    }
    return 0;
}

static int menu()
{
    int choice;
    printf("%s\n", "PAYROLL SYSTEM");
    printf("1. Add Record\n");
    printf("2. Display All Records\n");
    printf("3. Search a Record\n");
    printf("4. Exist Program\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    return choice;
}
static void call(int choice)
{
    switch (choice)
    {
    case 1:
        add_record();
        break;
    case 2:
        display_all();
        break;
    case 3:
        search_record();
        break;
    case 4:
        return;
    default:
        printf("Unkown Choice\n");
        return;
    }
}


static void add_record()
{
    record_t tmp;
    /* Set first name */
    printf("Please enter the first name (max 31 char): ");
    buff_clean();
    scanf("%s", TMP_BUFF);
    while(!checkfmt_name(TMP_BUFF))
    {
        printf("Invalid first name format. Please try again: ");
        buff_clean();
        scanf("%s", TMP_BUFF);
    }
    strncpy(tmp.first_name, TMP_BUFF, MAX_NAME_LEN);

    /* Set last name */
    printf("Please enter the last name (max 31 char): ");
    buff_clean();
    scanf("%s", TMP_BUFF);
    while(!checkfmt_name(TMP_BUFF))
    {
        printf("Invalid last name format. Please try again: ");
        buff_clean();
        scanf("%s", TMP_BUFF);
    }
    strncpy(tmp.last_name, TMP_BUFF, MAX_NAME_LEN);

    /* Set Email */
    printf("Please enter the email (max 63 char): ");
    buff_clean();
    scanf("%s", TMP_BUFF);
    while(!checkfmt_email(TMP_BUFF))
    {
        printf("Invalid email format. Please try again: ");
        buff_clean();
        scanf("%s", TMP_BUFF);
    }
    strncpy(tmp.email, TMP_BUFF, MAX_NAME_LEN);

    /* Set Phone */
    printf("Please enter the phone(max 15 char): ");
    buff_clean();
    scanf("%s", TMP_BUFF);
    while(!checkfmt_phone(TMP_BUFF))
    {
        printf("Invalid phone format. Please try again: ");
        buff_clean();
        scanf("%s", TMP_BUFF);
    }
    strncpy(tmp.phone, TMP_BUFF, MAX_NAME_LEN);
    tmp.rank = choose_rank();
    /* Set hours worked */
    printf("Please set hours worked: ");
    buff_clean();
    scanf("%f", &tmp.hours_worked);
    /* Set pay rate */
    printf("Please set pay rate: ");
    buff_clean();
    scanf("%f", &tmp.pay_rate);

    rv = pr_Add(&payroll, &tmp);
    if (rv != STATUS_OK)
        _DEBUGF("Failed to add a new record. (%d)", rv);
}
static void display_all()
{
    if(payroll.size == 0)
    {
        printf("Payroll is still empty.\n");
        return;
    }
    uint64_t i;
    for(i = 0; i < payroll.size; i++)
        rec_print((record_t*)list_GetData(&(payroll.records), i));
    printf("---------------------------------------------------------\n");
    printf("Total: %lu records\n", payroll.size);
}
static void search_record()
{
    printf(
            "1. Search by full name\n"
            "2. Search by first name\n"
            "3. Search by last name\n"
            "4. Search by phone\n"
            "5. Search by email\n"
            );
}
static enum rank choose_rank()
{
    int rk_num;
    printf("Please choose the employee rank\n");
    printf(
            "1. Staff\n"
            "2. Manager\n"
            );
    scanf("%d",&rk_num);
    while (1)
    {
        switch (rk_num)
        {
            case 1:
                return RK_STAFF;
            case 2:
                return RK_MANAGER;
            default:
                printf("Unknown choice, please enter again: ");
                scanf("%d",&rk_num);
        }
    }
    /* next line code shall never reach! */
    return RK_UNKNOWN;
}

static void buff_clean()
{
    _DEBUG("Clean TMP_BUFF.");
    memset(TMP_BUFF, 0, 256);
}