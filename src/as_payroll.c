#include <string.h> /* strlen strcmp */
#include <stdlib.h> /* malloc free */
#include <stdio.h>  /* fopen fclose */
#include <unistd.h> /* access */

#include "as_payroll.h"
#include "as_errno.h"
#include "as_encrypt.h"

/****************************************************************
 * static function prototypes
 ****************************************************************/
/* Pass -> 1; Fail -> 0 */
static int checkfmt_phone(const char *phone);
static int checkfmt_email(const char *email);
static int checkfmt_passwd(const char *password);
static int checkfmt_filename(const char *fname);
static int checkfmt_name(const char *name);

/* check if the phone number is unique */
static int uniq_phone(const pr_header_t *__h, const char *phone);

/* check if the email is unique */
static int uniq_email(const pr_header_t *__h, const char *email);

/* check if file exist and current user is able to access it */
static int check_filepriv(const char *fname);

/******************************************************************
* implementation
******************************************************************/
status_t pr_Init(pr_header_t *__h, const char *name, const char *password)
{
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    /* Check if creating payroll header is in correct format */
    if (!checkfmt_filename(name))
    {
        _DEBUG("Invalid payroll filename format.");
        return ERR_FIELDFMT;
    }
    /* Check if the password is in correct format */
    if (!checkfmt_passwd(password))
    {
        _DEBUG("Invalid password format.");
        return ERR_FIELDFMT;
    }
    __h->current_id = 0;
    __h->size = 0;
    __h->status= PR_ACCESS;
    list_Init(&(__h->records), sizeof(record_t));
    return STATUS_OK;
}

void pr_Destroy(pr_header_t *__h)
{
    list_Destroy(&(__h->records));
    __h->status = PR_DESTROY;
}

status_t pr_Load(pr_header_t *__h, const char *filename, const char *password)
{
    status_t rv;
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    if (!check_filepriv(filename))
    {
        _DEBUG("Unable to access the file.");
        return STATUS_FAIL;
    }
    FILE *Fp_pr = fopen(filename, "w+b");
    if (Fp_pr == NULL)
    {
        _DEBUG("Failed to open payroll file.");
        return STATUS_FAIL;
    }
    list_Init(&(__h->records), sizeof(record_t));
    /* Try to extract encrypted password in a payroll file */
    encrbuff_t encrpwd;
    fread(&(encrpwd.nbytes), sizeof(size_t), 1, Fp_pr);
    _DEBUG("Password nbytes load.");
    encrpwd.buffer = (char *)malloc(encrpwd.nbytes + 1);
    encrpwd.buffer[encrpwd.nbytes] = '\0';
    fread(&(encrpwd.buffer), 1, encrpwd.nbytes, Fp_pr);

    /* Decrypte the password */
    char *desire_pwd;
    rv = decrypt_buff((void **)&desire_pwd, &encrpwd);
    if (rv != STATUS_OK)
    {
        _DEBUG("Failed to decrypt.");
        return rv;
    }

    /* Check if password match */
    if (strcmp(password, desire_pwd) != 0)
    {
        _DEBUG("Password does not match.");
        return ERR_CREDENTIAL;
    }

    /* Load size and current id */
    fread(&(__h->size), sizeof(uint64_t), 1, Fp_pr);
    fread(&(__h->current_id), sizeof(uint64_t), 1, Fp_pr);

    /* Load Records */
    register uint64_t i;
    char tmp_buff[sizeof(record_t)];
    for (i = 0; i < __h->size; i++)
    {
        fread(tmp_buff, sizeof(record_t), 1, Fp_pr);
        list_PushBack(&(__h->records), tmp_buff);
    }
    fclose(Fp_pr);
    free(encrpwd.buffer);
    __h->status = PR_ACCESS;
    return STATUS_OK;
}

status_t pr_Dump(pr_header_t *__h)
{
    status_t rv;
    if(__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    // TODO:

    return STATUS_OK;
}

status_t pr_Add(pr_header_t *__h, const record_t *record)
{
    status_t rv;
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header.");
        return STATUS_FAIL;
    }
    /* ensure phone is correct format */
    if (!checkfmt_phone(record->phone))
    {
        _DEBUG("Invalid Phone Format.");
        return ERR_FIELDFMT;
    }
    /* ensure phone is unique in the payroll table */
    if (!uniq_phone(__h, record->phone))
    {
        _DEBUG("Record Phone should be unique.");
        return ERR_UNIQREQ;
    }
    /* ensure email is correct format */
    if (!checkfmt_email(record->email))
    {
        _DEBUG("Invalid Email Format.");
        return ERR_FIELDFMT;
    }
    /* ensure email is unique in the payroll table */
    if (!uniq_email(__h, record->email))
    {
        _DEBUG("Record email should be unique.");
        return ERR_UNIQREQ;
    }
    rv = list_PushBack(&(__h->records), record);
    // TODO: modify record id
    // list_Get(&(__h->records), )
    if (rv != STATUS_OK)
    {
        _DEBUG("Failed to add record.");
        return rv;
    }
    __h->size+=1;
    return STATUS_OK;
}

uint64_t pr_Find(pr_header_t *__h, record_t **__res, const char *fname, const char *lname)
{
    status_t rv;
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return 0;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header.");
        return 0;
    }
    /* Check pr_header_t is initialized or loaded. */
    if (__h->records.head == NULL)
    {
        _DEBUG("pr_header_t is neither initialized or loaded.");
        return 0;
    }
    /* Check firstname and lastname format */
    if (!checkfmt_name(fname))
    {
        _DEBUG("Invalid first name format.");
        return 0;
    }
    if (!checkfmt_name(lname))
    {
        _DEBUG("Invalid last name format.");
        return 0;
    }
    list_t find_list;
    array_t find_arr;
    list_Init(&find_list, sizeof(record_t));
    register uint64_t i;
    record_t *tmp;
    /* 
       Looking for matched record and append it to find_list 
       since the exact records it will find is unknown, thus, I choose to use linkedlist 
    */
    for (i = 0; i < __h->size; i++)
    {
        tmp = (record_t *)(list_Get(&(__h->records), i)->data);
        /* if firstname and lastname matches, we add it to find_list */
        if (!strcmp(tmp->first_name, fname) && !strcmp(tmp->last_name, lname))
        {
            _DEBUGF("Matched Record index: %lu", i);
            rv = list_PushBack(&find_list, tmp);
            if (rv != STATUS_OK)
                _DEBUGF("Failed to PushBack Record (%d)", rv);
        }
    }
    /* make it as an continuous data, better access speed O(1) */
    list_Finalize(&find_list, &find_arr);
    /* Just give data buffer of find_arr */
    *__res = (record_t *)(find_arr.data);
    /* return the amount matches */
    return find_arr.size;
}

uint64_t pr_Findfn(pr_header_t *__h, record_t **__res, const char *fname)
{
    status_t rv;
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header");
        return 0;
    }
    /* Check pr_header_t is initialized or loaded. */
    if (__h->records.head == NULL)
    {
        _DEBUG("pr_header_t is neither initialized or loaded.");
        return 0;
    }
    /* Check firstname format */
    if (!checkfmt_name(fname))
    {
        _DEBUG("Invalid first name format.");
        return 0;
    }
    list_t find_list;
    array_t find_arr;
    list_Init(&find_list, sizeof(record_t));
    register uint64_t i;
    record_t *tmp;
    /* 
       Looking for matched record and append it to find_list 
       since the exact records it will find is unknown, thus, I choose to use linkedlist 
    */
    for (i = 0; i < __h->size; i++)
    {
        tmp = (record_t *)(list_Get(&(__h->records), i)->data);
        /* if firstname and lastname matches, we add it to find_list */
        if (!strcmp(tmp->first_name, fname))
        {
            _DEBUGF("Matched Record index: %lu", i);
            rv = list_PushBack(&find_list, tmp);
            if (rv != STATUS_OK)
                _DEBUGF("Failed to PushBack Record (%d)", rv);
        }
    }
    /* make it as an continuous data, better access speed O(1) */
    list_Finalize(&find_list, &find_arr);
    /* Just give data buffer of find_arr */
    *__res = (record_t *)(find_arr.data);
    /* return the amount matches */
    return find_arr.size;
}

uint64_t pr_Findln(pr_header_t *__h, record_t **__res, const char *lname)
{
    status_t rv;
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return ERR_NULLPTR;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header.");
        return 0;
    }
    /* Check pr_header_t is initialized or loaded. */
    if (__h->records.head == NULL)
    {
        _DEBUG("pr_header_t is neither initialized or loaded.");
        return 0;
    }
    /* Check lastname format */
    if (!checkfmt_name(lname))
    {
        _DEBUG("Invalid last name format.");
        return 0;
    }
    list_t find_list;
    array_t find_arr;
    list_Init(&find_list, sizeof(record_t));
    register uint64_t i;
    record_t *tmp;
    /* 
       Looking for matched record and append it to find_list 
       since the exact records it will find is unknown, thus, I choose to use linkedlist 
    */
    for (i = 0; i < __h->size; i++)
    {
        tmp = (record_t *)(list_Get(&(__h->records), i)->data);
        /* if firstname and lastname matches, we add it to find_list */
        if (!strcmp(tmp->last_name, lname))
        {
            _DEBUGF("Matched Record index: %lu", i);
            rv = list_PushBack(&find_list, tmp);
            if (rv != STATUS_OK)
                _DEBUGF("Failed to PushBack Record (%d)", rv);
        }
    }
    /* make it as an continuous data, better access speed O(1) */
    list_Finalize(&find_list, &find_arr);
    /* Just give data buffer of find_arr */
    *__res = (record_t *)(find_arr.data);
    /* return the amount matches */
    return find_arr.size;
}

record_t *pr_Getby_ph(pr_header_t *__h, const char *phone)
{
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return NULL;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header.");
        return NULL;
    }
    /* Check pr_header_t is initialized or loaded. */
    if (__h->records.head == NULL)
    {
        _DEBUG("pr_header_t is neither initialized or loaded.");
        return NULL;
    }
    /* Check phone format */
    if (!checkfmt_phone(phone))
    {
        _DEBUG("Invalid phone format.");
        return NULL;
    }
    register uint64_t i;
    record_t *rec;
    for (i = 0; i < __h->records.size; i++)
    {
        rec = (record_t *)(list_Get(&(__h->records), i)->data);
        if (!strcmp(rec->phone, phone))
            return rec;
    }
    /* if record not found, return NULL */
    return NULL;
}

record_t *pr_Getby_em(pr_header_t *__h, const char *email)
{
    if (__h == NULL)
    {
        _DEBUG("Payroll Header is NULL.");
        return NULL;
    }
    if(__h->status != PR_ACCESS)
    {
        _DEBUG("Unable to access Payroll Header.");
        return NULL;
    }
    /* Check pr_header_t is initialized or loaded. */
    if (__h->records.head == NULL)
    {
        _DEBUG("pr_header_t is neither initialized or loaded.");
        return NULL;
    }
    /* Check phone format */
    if (!checkfmt_email(email))
    {
        _DEBUG("Invalid phone format.");
        return NULL;
    }
    register uint64_t i;
    record_t *rec;
    for (i = 0; i < __h->records.size; i++)
    {
        rec = (record_t *)(list_Get(&(__h->records), i)->data);
        if (!strcmp(rec->email, email))
            return rec;
    }
    /* if record not found, return NULL */
    return NULL;
}

/****************************************************************
 * static function implementation
 ****************************************************************/
static int checkfmt_phone(const char *phone)
{
    if (strlen(phone) <= MAX_PHONE_LEN)
        return 1;
    return 0;
}
static int checkfmt_email(const char *email)
{
    if (strlen(email) <= MAX_EMAIL_LEN)
        return 1;
    return 0;
}
static int checkfmt_passwd(const char *password)
{
    if (strlen(password) <= MAX_PASSWD_LEN)
        return 1;
    return 0;
}
static int checkfmt_filename(const char *fname)
{
    uint64_t i;
    /* filename (Payroll Name) length */
    uint64_t __inLen = strlen(fname);
    if (__inLen <= MAX_PRNAME_LEN)
    {
        for (i = 0; i < __inLen; i++)
        {
            /* filename shall not contain <space> */
            if (fname[i] == ' ' || fname[i] == '\\' || fname[i] == '/')
                return 0;
        }
        return 1;
    }
    return 0;
}

static int checkfmt_name(const char *name)
{
    uint64_t i;
    uint64_t __inLen = strlen(name);
    if(__inLen <= MAX_NAME_LEN)
    {
        for(i = 0; i < __inLen; i++)
        {
            if (name[i] == ' ' || name[i] == '\\' || name[i] == '/')
                return 0;
        }
        return 0;
    }
    return 0;
}

static int uniq_phone(const pr_header_t *__h, const char *phone)
{
    register uint64_t i;
    record_t *rec;
    for(i = 0; i < __h->size; i++)
    {
        rec = (record_t*)list_Get(&(__h->records), i);
        if(!strcmp(phone, rec->phone))
        /* if one record matches, the phone is not unique */
            return 0;
    }
    return 1;
}
static int uniq_email(const pr_header_t *__h, const char *email)
{
    register uint64_t i;
    record_t *rec;
    for(i = 0; i < __h->size; i++)
    {
        rec = (record_t*)list_Get(&(__h->records), i);
        if(!strcmp(email, rec->email))
        /* if one record matches, the phone is not unique */
            return 0;
    }
    return 1;
}
static int check_filepriv(const char *fname)
{
    if (access(fname, R_OK | W_OK | F_OK) == 0)
        return 1;
    return 0;
}