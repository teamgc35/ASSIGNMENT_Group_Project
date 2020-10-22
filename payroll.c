#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu();
void call(int choice);
void add_record();
void display_all();
void search_record();

int main(int argc, const char *argv[])
{
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

int menu()
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
void call(int choice)
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