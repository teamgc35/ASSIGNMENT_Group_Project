#include "as_bitctl.h"
#include "as_errno.h"

status_t as_bitset(void *buffer, const unsigned nbytes, const char *bits)
{
    size_t bit_width = strlen(bits);
    if (bit_width / 8 != nbytes)
        return ERR_PARAMS;
    char *the_buffer = (char *)buffer + nbytes;
}