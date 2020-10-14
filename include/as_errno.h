#ifndef __AS_ERRNO_H__
#define __AS_ERRNO_H__

#include "as_general.h"

#define STATUS_OK 0
#define STATUS_FAIL -1
#define BASE_ERR 10000

#define ERR_NULLPTR (BASE_ERR + 100)
#define ERR_RANGE (BASE_ERR + 101)
#define ERR_CREDENTIAL (BASE_ERR + 102)
#define ERR_PARAMS (BASE_ERR + 103)
#define ERR_ARRFULL (BASE_ERR + 104)

static status_t as_errno;

/* set error */
void as_seterr(status_t, const char *);

/* Print out last error */
void as_plasterr();

#endif