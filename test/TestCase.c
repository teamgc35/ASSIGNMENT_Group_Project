#include "as_enrypt.h"
#include "as_errno.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    char* src = "Good Morning";
    char* encrypted;
    char* decrypted;
    status_t rv;

    rv = encrypt_str(&encrypted, src);
    assert(rv == STATUS_OK);
    printf("Encrypted String:\n%s\n", encrypted+4);
    rv = decrypt_str(&decrypted, encrypted);
    assert(rv == STATUS_OK);
    printf("Decrypted String:\n%s\n", decrypted);

    
}