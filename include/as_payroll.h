#ifndef __AS_PAYROLL_H__
#define __AS_PAYROLL_H__

#include "as_general.h"
#include "as_list.h"

#define EXNAME ".prl"
#define MAX_NAME_LEN 31
#define MAX_PRNAME_LEN 31
#define MAX_PHONE_LEN 15
#define MAX_EMAIL_LEN 63

#define PR_UNINIT 0
#define PR_ACCESS 1
#define PR_DESTROY -1

enum rank {
    RK_UNKNOWN = -1,
    RK_STAFF = 1,
    RK_MANAGER = 2,
    RK_SUPERVISOR = 3,
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
    int status;
    uint64_t size;
    uint64_t current_id;
    list_t records;
} pr_header_t;

/* Build a record_t according to the information given */
status_t rec_Build(record_t* rec, const char* fname, const char* lname, const char* phone, const char* email, const enum rank rank, float hours, float pay_rate);

/* printf the record */
void rec_print(const record_t* rec);

/* print the record head */
void rechead_print();

/* Create a new payroll */
status_t pr_Init(pr_header_t *__h, const char* name, const char* password);

/* When finishing using the payroll , this func should be called */
void pr_Destroy(pr_header_t *__h);

/* Load a payroll from FILE */
status_t pr_Load(pr_header_t *__h, const char* filename, const char* password);

/* Dump the payroll to a FILE */
status_t pr_Dump(pr_header_t *__h);

/* Add a new record to the payroll */
status_t pr_Add(pr_header_t *__h, const record_t *record);

/* Find matched records and return how many matches, according to fist name and last name given */
uint64_t pr_Find(pr_header_t *__h, record_t **__res, const char* fname, const char* lname);

/* Find matched records and return how many matches, according to fist name only */
uint64_t pr_Findfn(pr_header_t *__h, record_t **__res, const char* fname);

/* Find matched records and return how many matches, according to last name only */
uint64_t pr_Findln(pr_header_t *__h, record_t **__res, const char* lname);

/* Find the record which has the match phone number */
record_t* pr_Getby_ph(pr_header_t *__h, const char* phone);

/* Find the record which has the match email address */
record_t* pr_Getby_em(pr_header_t *__h, const char* email);

/* Pass -> 1; Fail -> 0 */
/* check if phone is correct format */
int checkfmt_phone(const char *phone);

/* check if email is correct format */
int checkfmt_email(const char *email);

/* check if password is correct format */
int checkfmt_passwd(const char *password);

/* check if payroll filename is correct format */
int checkfmt_filename(const char *fname);

/* check if first/last name is correct format */
int checkfmt_name(const char *name);

/* check if the phone number is unique */
int uniq_phone(const pr_header_t *__h, const char *phone);

/* check if the email is unique */
int uniq_email(const pr_header_t *__h, const char *email);

/* check if file exist and current user is able to access it */
int check_filepriv(const char *fname);

#endif