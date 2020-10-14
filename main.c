#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "as_general.h"
#include "as_functional.h"
#include "as_errno.h"
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
            if (choice == 5)
                return 0;
            call(choice);
        }
        return 0;
    }
    if (argc > 1)
    {
        if (!strcmp(argv[1], "encrypt"))
        {
            char *src_path;
            char *out_path;
            char *passwd;
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
        compress_file();
        break;
    case 4:
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
        3. compress file
        4. extract file
    */
    int choice;
    printf("%s\n", TITLE);
    printf("1. Encrypt a File.\n");
    printf("2. Decrypt a File.\n");
    printf("3. Compress a File.\n");
    printf("4. Extract a File.\n");
    printf("5. Exit Program.\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

static void encrypt_file()
{
    char path[256];
    char password[64];
    status_t rv;

    /* Get src file path and open it */
    printf("Please enter the file path: ");
    scanf("%s", path);
    FILE *Fp_in = fopen(path, "rb");
    while (Fp_in == NULL)
    {
        perror("Failed to open src file. Please try again: ");
        scanf("%s", path);
        Fp_in = fopen(path, "rb");
    }
    /* clear the buffer */
    memset(path, '\0', 256);
    scanf("%s", path);

    /* Get output file path and open it */
    printf("Please enter the output path: ");
    FILE *Fp_out = fopen(path, "wb");
    while (Fp_out == NULL)
    {
        perror("Failed to open output file. Please try again: ");
        scanf("%s", path);
        Fp_out = fopen(path, "rb");
    }
    /* Ask for password */
    printf("Please enter the password (Max length 31): ");
    scanf("%s", password);
    /* Ensure the password is correct format */
    while (strlen(password) > MAX_PASSWD_LEN)
    {
        memset(password, 0, 64);
        perror("Password too long. Please try again: ");
        scanf("%s", password);
    }
    /* Encrypt the file */
    rv = Fn_encrypt_file(password, Fp_in, Fp_out);
    /* Close File */
    fclose(Fp_in);
    fclose(Fp_out);
    /* Check result */
    if (rv != 0)
        perror("Failed to encrypt file.\n");
}

static void decrypt_file()
{
    char path[256];
    char password[64];
    status_t rv;

    printf("Please enter the file path: ");
    scanf("%s", path);
    FILE *Fp_in = fopen(path, "rb");
    while (Fp_in == NULL)
    {
        perror("Failed to open src file. Please try again: ");
        scanf("%s", path);
        Fp_in = fopen(path, "rb");
    }
    printf("Please enter the output path: ");
    memset(path, '\0', 256);
    scanf("%s", path);
    FILE *Fp_out = fopen(path, "wb");
    while (Fp_out == NULL)
    {
        perror("Failed to open output file. Please try again: ");
        scanf("%s", path);
        Fp_out = fopen(path, "rb");
    }
    printf("Please enter the password (Max length 31):");
    scanf("%s", password);
    /* Ensure the password is correct format */
    while (strlen(password) > MAX_PASSWD_LEN)
    {
        memset(password, 0, 64);
        perror("Password too long. Please try again: ");
        scanf("%s", password);
    }
    rv = Fn_decrypt_file(password, Fp_in, Fp_out);
    /* If password does not match, ask the user to re-enter the password */
    while (rv == ERR_CREDENTIAL)
    {
        perror("Wrong Password! Please try again: ");
        scanf("%s", password);
        rv = Fn_decrypt_file(password, Fp_in, Fp_out);
    }
    fclose(Fp_in);
    fclose(Fp_out);
    if (rv != 0)
        perror("Failed to decrypt file.\n");
}

static void compress_file()
{
}
static void extract_file()
{
}