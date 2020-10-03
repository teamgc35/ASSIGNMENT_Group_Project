#ifndef __AS_ERRNO_H__
#define __AS_ERRNO_H__

#include "as_general.h"

#define STATUS_OK 0
#define STATUS_FAIL 1

#define ERR_NULLPTR 100

static status_t as_errno;

/* set error */
void as_seterr(status_t, const char*); 

/* Print out last error */
void as_plasterr(); 


#endif 