#include "as_errno.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char ERR_BUFF[256];
static void flush_msg();

void as_seterr(status_t err_code, const char* msg)
{
    as_errno = err_code;
    if(strlen(msg) == 0)
        return;
    if(strlen(msg) > 255)
        strncpy(ERR_BUFF, msg, 255);
    else
        strcpy(ERR_BUFF, msg);
}

void as_plasterr() {
    // TODO: Replace stdout with stderr
    printf("ERROR (%d), %s\n", as_errno, ERR_BUFF);
    flush_msg();
    exit(as_errno);
}

static void flush_msg()
{
    memset(ERR_BUFF, 0, 128);
}
