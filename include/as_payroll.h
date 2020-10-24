#ifndef __AS_PAYROLL_H__
#define __AS_PAYROLL_H__

#include "as_general.h"
#include "as_list.h"

#define EXNAME ".prl"
#define WEEKEND_BONUS (2);
#define MAX_NAME_LEN 31
#define MAX_PRNAME_LEN 31
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 63

enum rank {
    _STAFF,
    _MANAGER,
};

typedef struct payroll_record {
    uint64_t id; /* PRIMARY_KEY, AUTO_INCREMENT, UNIQUE */
    char first_name[MAX_NAME_LEN+1];
    char last_name[MAX_NAME_LEN+1];
    char phone[MAX_PHONE_LEN+1]; /* phone nust be unique */
    char email[MAX_EMAIL_LEN+1]; /* email must be unique */
    enum rank rank;
    float hours_worked;
    float pay_rate;
} record_t;

typedef struct payroll_header {
    char pr_fname[MAX_PRNAME_LEN+1]; /* payroll filename */
    char password[32];
    int auth;
    uint64_t size;
    uint64_t current_id;
    list_t records;
} pr_header_t;

status_t pr_Init(pr_header_t *__h, const char* name, const char* password);
status_t pr_Load(pr_header_t *__h, const char* filename, const char* password);
status_t pr_Add(pr_header_t *__h, const record_t *record);
uint64_t pr_Find(pr_header_t *__h, record_t **__res, const char* fname, const char* lname);
uint64_t pr_Findfn(pr_header_t *__h, record_t **__res, const char* fname);
uint64_t pr_Findln(pr_header_t *__h, record_t **__res, const char* lname);
record_t* pr_Getby_ph(pr_header_t *__h, const char* phone);
record_t* pr_Getby_em(pr_header_t *__h, const char* email);

#endif