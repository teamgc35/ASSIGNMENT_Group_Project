#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "as_general.h"
#include "as_functional.h"
#include "as_argparse.h"

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
    if (argc == 1)
    {
        int choice;
        while (1)
        {
            choice = menu();
            if (choice == 7)
                return 0;
            call(choice);
        }
        return 0;
    }
    if (argc > 1)
    {
        if (!strcmp(argv[1], "encrypt"))
        {
            char* src_path;
            char* out_path;
            char* passwd;
        }

    }
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
    printf("7. Exit Program.\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

static void encrypt_file()
{
    char path[256];
    char password[32];
    status_t rv;

    printf("Please enter the file path: ");
    scanf("%s", path);
    FILE *Fp_in = fopen(path, "r");
    if (Fp_in == NULL)
        perror("Failed to open input file.\n");
    printf("Please enter the output path: ");
    memset(path, '\0', 256);
    scanf("%s", path);
    FILE *Fp_out = fopen(path, "w");
    if (Fp_out == NULL)
        perror("Failed to open output file.\n");
    printf("Please enter the password (Max length 31): ");
    scanf("%s", password);
    rv = Fn_encrypt_file(password, Fp_in, Fp_out);
    if (rv != 0)
        perror("Failed to encrypt file.\n");
}

static void decrypt_file()
{
    char path[256];
    char password[32];
    status_t rv;

    printf("Please enter the file path: ");
    scanf("%s", path);
    FILE *Fp_in = fopen(path, "r");
    if (Fp_in == NULL)
        perror("Failed to open input file.\n");
    printf("Please enter the output path: ");
    memset(path, '\0', 256);
    scanf("%s", path);
    FILE *Fp_out = fopen(path, "w");
    if (Fp_out == NULL)
        perror("Failed to open output file.\n");
    printf("Please enter the password (Max length 31):");
    scanf("%s", password);
    rv = Fn_decrypt_file(password, Fp_in, Fp_out);
    if (rv != 0)
        perror("Failed to decrypt file.\n");
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