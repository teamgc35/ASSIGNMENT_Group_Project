#include "as_encrypt.h"
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
    uint64_t i;
    double src_sum = 0;
    double decrypted_sum = 0;
    double buffer[] = {1, 2, 3, 4};
    for (i = 0; i < 4; i++)
        src_sum += buffer[i];
    encrbuff_t encrypted;
    double *decrypted;
    encrypt_buff(&encrypted, buffer, sizeof(double) * 4);
    decrypt_buff((void **)&decrypted, &encrypted);
    for (i = 0; i < 4; i++)
        decrypted_sum += decrypted[i];
    assert(decrypted_sum == src_sum);
    printf("Test Encrypt Buffer 1 PASS!\n");
}

void Test_EncryptBuffer2()
{
    char *buffer = "Good Morning!!!";
    encrbuff_t encrypted;
    char *decrypted;

    encrypt_buff(&encrypted, buffer, strlen(buffer));
    decrypt_buff((void **)&decrypted, &encrypted);
    assert(!strcmp(buffer, decrypted));
    printf("Test Encrypt Buffer 2 PASS!\n");
}

int main()
{
    Test_EncryptString1();
    Test_EncryptString2();
    Test_EncryptString3();
    printf("\n");
    Test_EncryptBuffer1();
    Test_EncryptBuffer2();
    return 0;
}