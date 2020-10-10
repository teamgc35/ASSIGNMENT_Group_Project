#include "as_enrypt.h"
#include "as_errno.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static status_t rv;

void Test_EncryptString1()
{
    char *src = "Good Morning";
    encrbuff_t encrypted;
    char *decrypted;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, &encrypted);
    assert(rv == STATUS_OK);
    assert(!strcmp(src, decrypted));
    printf("Test Encrypt String 1 PASS!\n");
}

void Test_EncryptString2()
{
    char *src = "123123Lorem ipsum dolor sit amet, sed id inani choro feugait, in nisl invenire eloquentiam eos. Has quaestio postulant liberavisse ei. Ea illum suavitate percipitur qui. Usu inani fuisset platonem et.123123123";
    encrbuff_t encrypted;
    char *decrypted;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, &encrypted);
    assert(rv == STATUS_OK);
    assert(!strcmp(src, decrypted));
    printf("Test Encrypt String 2 PASS!\n");
}

void Test_EncryptString3()
{
    char *src = "+123123=-!@#$%^&*()jlsdflkjsvn\n\t\b\b//\\C://\n";
    encrbuff_t encrypted;
    char *decrypted;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, &encrypted);
    assert(rv == STATUS_OK);
    assert(!strcmp(src, decrypted));
    printf("Test Encrypt String 3 PASS!\n");
}

void Test_EncryptBuffer1()
{
    double buffer[] = {1, 2, 3, 4};
    encrbuff_t encrypted;
    double *decrypted;
    encrypt_buff(&encrypted, buffer, sizeof(double) * 4);
    decrypt_buff((void**)&decrypted, &encrypted);
    for(int i = 0; i < 4; i++)
        printf("%lf ", decrypted[i]);
    printf("\n");
}

int main()
{
    Test_EncryptString1();
    Test_EncryptString2();
    Test_EncryptString3();
    return 0;
}