#include <cstdio>

char* Strcpy(char* dest, const char* src)
{
    if(dest == NULL || src == NULL)
        return NULL;
    char* ret = dest;
    while(*ret++ = *src++)
        ;
    ret = dest;
    return ret;
}

int main()
{
    char buf[32] = {0};
    char str[32] = "Hello";

    printf("%s\n", Strcpy(buf, str));

    return 0;
}

