#include <stdlib.h>
#include <stdio.h>

#include "as_general.h"

/**
 * @description: Display menu, and get user choice
 * @param void
 * @return int: choice
 */
static int menu(void);

/**
 * @description: calling the suitable function depends on the choice inputed by the user
 * @param int
 * @return void
 */
static void call(const int choice);

static void encrypt_file();
static void decrypt_file();
static void store_login_credential();
static void retrive_login_credential();
static void compress_file();
static void extract_file();

int main(int argc, const char *argv[])
{
    // int choice;
    // choice = menu();
    FILE *file = fopen("./text.txt", "r");
    if(file == NULL)
    {
        perror("Fail to open");
    }
    int nLen = 0;
    fseek(file, 0, SEEK_END);
    nLen = ftell(file);
    rewind(file);
    char* buffer = (char*)malloc(sizeof(char)*nLen + 1);
    nLen = fread(buffer, sizeof(char), nLen, file);
    buffer[nLen] = '\0';
    printf("%s\n", buffer);
    fclose(file);
    free(buffer);
    return 0;
}

static void call(const int choice)
{
    switch (choice)
    {
    case 1:
        encrypt_file();
        break;
    case 2:
        decrypt_file();
        break;
    case 3:
        store_login_credential();
        break;
    case 4:
        retrive_login_credential();
        break;
    case 5:
        compress_file();
        break;
    case 6:
        extract_file();
        break;
    default:
        printf("Unkown Choice\n");
        return;
    }
}

static int menu()
{
    /*
            <TILE>
        1. encrypt file
        2. dectypt file
        3. store login credential
        4. retrive login credential
        5. compress file
        6. extract file
    */
    int choice;
    printf("%s\n", TITLE);
    printf("1. Encrypt a File.\n");
    printf("2. Decrypt a File.\n");
    printf("3. Store Login Credential.\n");
    printf("4. Retrive Login Credential.\n");
    printf("5. Compress a File.\n");
    printf("6. Extract a File.\n");
    scanf("%d", &choice);
    return choice;
}

static void encrypt_file()
{
}
static void decrypt_file()
{
}
static void store_login_credential()
{
}
static void retrive_login_credential()
{
}
static void compress_file()
{
}
static void extract_file()
{
}