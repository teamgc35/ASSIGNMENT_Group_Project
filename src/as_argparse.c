#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "as_argparse.h"

int has_sarg(int argc, const char **argv, const char sarg)
{
    int i;
    char buffer[3];
    buffer[0] = '-';
    buffer[1] = sarg;
    buffer[2] = '\0';
    for (i = 1; i < argc; i += 2)
    {
        if (!strcmp(argv[i], buffer))
            /* if the sarg exist, return the value index */
            return i + 1;
    }
    return 0;
}
int has_larg(int argc, const char **argv, const char *larg)
{
    int i;
    char buffer[16];
    buffer[0] = '-';
    buffer[1] = '-';
    strcpy(buffer + 2, larg);
    for (i = 1; i < argc; i += 2)
    {
        if (!strcmp(argv[i], buffer))
            return i + 1;
    }
    return 0;
}
const char *get_sarg(int argc, const char **argv, const char sarg)
{
    /* Check if the sarg exist*/
    int rv;
    rv = has_sarg(argc, argv, sarg);
    if (rv == 0)
        return NULL;
    return argv[rv];
}

const char *get_larg(int argc, const char **argv, const char *larg)
{
    int rv;
    rv = has_larg(argc, argv, larg);
    if (rv == 0)
        return NULL;
    return argv[rv];
}

const char *parse_argv(int argc, const char **argv, const char *larg, const char sarg)
{
    const char *temp = get_larg(argc, argv, larg);
    if (temp == NULL)
        return get_sarg(argc, argv, sarg);
    return temp;
}