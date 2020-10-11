#include "as_functional.h"
#include "as_errno.h"
#include "as_encrypt.h"

#include <stdio.h>

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
    /* 2. Store the password in the first line in the out file */
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
    fclose(src);
    fclose(out);
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
    encr_passwd.buffer = file_passwd;
    rv = decrypt_str(&decrypted_passwd, &encr_passwd);
    if (strcmp(decrypted_passwd, password))
    {
        fprintf(stderr, "Wrong password!\n");
        exit(-1);
    }
    printf("Valid password! Begin to decrypt...\n");
    fread(&(encr_buffer.nbytes), sizeof(size_t), 1, src);
    char encr_buff[encr_buffer.nbytes];
    fread(encr_buff, 1, encr_buffer.nbytes, src);
    encr_buffer.buffer = encr_buff;
    rv = decrypt_buff((void**)&decrypted_buffer, &encr_buffer);
    printf("%s\n", decrypted_buffer);

}