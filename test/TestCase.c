#include "as_enrypt.h"
#include "as_errno.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>


static status_t rv;

void Test_EncryptString1()
{
    char *src = "Good Morning";
    char *encrypted;
    char *decrypted;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, encrypted);
    assert(rv == STATUS_OK);
    assert(!strcmp(src, decrypted));
    printf("Test Encrypt String 1 PASS!");
}

void Test_EncryptString2()
{
    char *src = "123123Lorem ipsum dolor sit amet, sed id inani choro feugait, in nisl invenire eloquentiam eos. Has quaestio postulant liberavisse ei. Ea illum suavitate percipitur qui. Usu inani fuisset platonem et.123123123";
    char *encrypted;
    char *decrypted;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, encrypted);
    assert(rv == STATUS_OK);
    assert(!strcmp(src, decrypted));
    printf("Test Encrypt String 2 PASS!");
}

void Test_EncryptBuffer1()
{
    double src = 3.1415926;
    double *encrypted;
    double *decrypted;

    rv = encrypt_str(&encrypted, &src);
    assert(rv == STATUS_OK);
    rv = decrypt_str(&decrypted, encrypted);
    assert(rv == STATUS_OK);
    assert(*decrypted == src);
    printf("Test Encrypt Buffer 2 PASS!");
}

int main()
{
}