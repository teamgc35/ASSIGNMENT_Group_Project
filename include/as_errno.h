#ifndef __AS_ERRNO_H__
#define __AS_ERRNO_H__

#include "as_general.h"

#define STATUS_OK 0
#define STATUS_FAIL -1
#define BASE_ERR 10000

#define ERR_NULLPTR (BASE_ERR + 100) /* Error NULL pointer */
#define ERR_RANGE (BASE_ERR + 101) /* Error Range */
#define ERR_CREDENTIAL (BASE_ERR + 102) /* Error Credential */
#define ERR_PARAMS (BASE_ERR + 103) /* Error Args */
#define ERR_ARRFULL (BASE_ERR + 104) /* Error Array is Full */
#define ERR_FIELDFMT (BASE_ERR + 105) /* Error Field Format */
#define ERR_UNIQREQ (BASE_ERR + 106) /* Error Unique required */


/* set error */
void as_seterr(status_t, const char *);

/* Print out last error */
void as_plasterr();

#endif