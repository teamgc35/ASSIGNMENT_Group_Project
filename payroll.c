#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int menu();
static void call(int choice);
static void cli_help();
static void add_record();
static void display_all();
static void search_record();

int main(int argc, const char *argv[])
{
    if (argc == 1) {
        printf("A payroll file must be specified.\n");
        return 0;
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

}
static void display_all()
{
}
static void search_record()
{

}