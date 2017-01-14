#include <upo/mem_set.h>

void upo_mem_set(void* p, unsigned char c, size_t n)
{
    size_t i; 
    char* pp = p;
    for (i = 0; i < n; ++i)
    {
        pp[0] = c;
    }
    p = pp;
}