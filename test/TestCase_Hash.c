#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "as_hash.h"

void Test_Hash()
{
    const char* strings[] = {
        "Good Morning",
        "Good",
        "lksfjgdsfg",
        "ewojhcvnjkl;dfs",
        "Xiao ZHONG",
        "ASDNM<VOUYDSF",
        "EequalsMC2",
        "EequalsMC^2",
        "jklhdbklvhuherReCoXD",
        "coldzeradfgljl;kdjsf"
    };
    for(int i =0; i < 10; i++)
        printf("%s\t%d\n", strings[i], as_hash(strings[i], strlen(strings[i])));
    printf("---------------------------\n");
    for(int i =0; i < 10; i++)
        printf("%s\t%d\n", strings[i], as_hashstr(strings[i]));
}

int main()
{
    Test_Hash();
}