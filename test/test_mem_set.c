#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <upo/mem_set.h>

void test_mem_set()
{
    char cary[] = "Hello, World!";
    char test[] = "?????????????";
    int i = 10;
    unsigned char ucary[] = {255, 128, 64, 32, 16, 8};

    upo_mem_set(cary, '?', strlen(cary));
    assert(strcmp(cary, test) == 0);

    upo_mem_set(&i, 0, sizeof i);
    assert(i == 0);

    upo_mem_set(ucary, 127, (sizeof ucary) / 2);
    assert(ucary[0] == 127);
    assert(ucary[1] == 127);
    assert(ucary[2] == 127);
    assert(ucary[3] == 32);
    assert(ucary[4] == 16);
    assert(ucary[5] == 8);
}

int main() 
{
    printf("Test case 'mem_set'... ");
    fflush(stdout);
    test_mem_set();
    printf("OK\n");

    return 0;
}
