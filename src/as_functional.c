#include "as_functional.h"
#include "as_errno.h"
#include "as_encrypt.h"

#include <stdio.h>  /* fputs fgets fread fwrite fseek rewind perror printf */
#include <stdlib.h> /* free malloc*/
#include <string.h> /* strcmp */

status_t Fn_encrypt_file(const char *password, FILE *src, FILE *out)
{
    /* 1. Encrypt the password */
    int rv;
    encrbuff_t encr_passwd;
    encrbuff_t encr_file;
    char *buffer;

    rv = encrypt_str(&encr_passwd, password);
    if (rv != 0)
        return STATUS_FAIL;
    /* 2. Store the password */
    fwrite(&(encr_passwd.nbytes), sizeof(size_t), 1, out);
    fputs(encr_passwd.buffer, out);

    // fwrite(encr_passwd.buffer, sizeof(char), encr_passwd.nbytes, out);
    // fwrite("\n", 1, 1, out);
    /* 3. Encrypt buffer */

    /* 3.1. Find out the nbytes of the src file */
    long nLen = 0;
    fseek(src, 0, SEEK_END);
    nLen = ftell(src);
    rewind(src);
    buffer = (char *)malloc(sizeof(char) * nLen + 1);
    buffer[nLen] = '\0';
    nLen = fread(buffer, sizeof(char), nLen, src);
    /* 3.2. Store the nLen */
    fwrite(&nLen, sizeof(long), 1, out);
    /* 3.3. Encrypte the buffer */
    rv = encrypt_buff(&encr_file, buffer, nLen);
    if (rv != 0)
        return STATUS_FAIL;
    /* 3.4. Write to file */
    fwrite(encr_file.buffer, sizeof(char), nLen, out);
    free(buffer);
    return STATUS_OK;
}
status_t Fn_decrypt_file(const char *password, FILE *src, FILE *out)
{
    status_t rv;
    char file_passwd[32];
    char *decrypted_passwd;
    char *decrypted_buffer;
    encrbuff_t encr_passwd;
    encrbuff_t encr_buffer;
    /* 1. Check password matches. */
    /* 1.1. decrypt the password stored in the src */
    fread(&(encr_passwd.nbytes), sizeof(size_t), 1, src);
    fgets(file_passwd, encr_passwd.nbytes, src);
    /* 
        Compare input password length with encrypted file password length
    */
    if (strlen(password) != (encr_passwd.nbytes-1))
        return ERR_CREDENTIAL;
    encr_passwd.buffer = file_passwd;
    rv = decrypt_str(&decrypted_passwd, &encr_passwd);
    if (rv != STATUS_OK)
    {
        _DEBUGF("Failed to decrypt string (%d)", rv);
        return rv;
    }
    // ensure password match
    if (strcmp(decrypted_passwd, password))
    {
        _DEBUG("Password not match.");
        return ERR_CREDENTIAL;
    }
    printf("Valid password! Begin to decrypt...\n");
    fread(&(encr_buffer.nbytes), sizeof(size_t), 1, src);
    char encr_buff[encr_buffer.nbytes];
    fread(encr_buff, 1, encr_buffer.nbytes, src);
    encr_buffer.buffer = encr_buff;
    rv = decrypt_buff((void **)&decrypted_buffer, &encr_buffer);
    if(rv != STATUS_OK)
    {
        _DEBUGF("Failed to decrypt buffer (%d)", rv);
        return rv;
    }
    fwrite(decrypted_buffer, sizeof(char), encr_buffer.nbytes, out);
    return STATUS_OK;
}
status_t Fn_compress_file(FILE *src, FILE *out)
{

    return STATUS_OK;
}

status_t Fn_extract_file(FILE *src, FILE* out)
{

    return STATUS_OK;
}