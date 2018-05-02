#include <stdio.h>
#include <sys/mman.h>


int main()
{
    char* p = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    // void* p2 = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    // void* p3 = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    // void* p4 = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    for (int i = 0; i < 1000; ++i)
        printf("%c", p[i]);
    // printf("%p\n", p2);
    // printf("%p\n", p3);
    // printf("%p\n", p4);
    return (0);
}