#include "as_errno.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void flush_msg();

void as_seterr(status_t err_code, const char* msg)
{
    as_errno = err_code;
    if(strlen(msg) == 0)
        return;
    if(strlen(msg) > 127)
        strncpy(err_msg, msg, 127);
    else
        strcpy(err_msg, msg);
}

void as_plasterr() {
    // TODO: Replace stdout with stderr
    printf("ERROR (%d), %s\n", as_errno, err_msg);
    flush_msg();
    exit(as_errno);
}

static void flush_msg()
{
    memset(err_msg, 0, 128);
}
