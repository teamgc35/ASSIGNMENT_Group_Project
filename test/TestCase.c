#include "as_enrypt.h"

#include <string.h>
#include <stdio.h>

int main()
{
    char a = 'a';
    char b;
    char c;
    encrypt_char(&b, &a, 123);
    printf("%c\n", b);
    decrypt_char(&c, &b, 123);
    printf("%c\n",c );
    
}