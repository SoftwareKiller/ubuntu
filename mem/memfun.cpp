#include <stdio.h>

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

void* Memcpy(void* dest, const void* src, size_t n)
{
    if(dest == NULL || src == NULL)
        return NULL;
    char* ret = (char*)dest;
    char* psrc = (char*)src;
    for(int i= 0; i < n; ++i)
    {
        *ret++ = *psrc++;
    }
    ret = (char*)dest;
    return ret;
}

size_t Strlen(char* str)
{
    if(str == NULL)
        return 0;

    int count = 0;
    while(*str++)
        ++count;
    return count;
}

int main()
{
    char buf[32] = {0};
    char str[32] = "Hello";
    //printf("%s\n", Strcpy(buf, str));
    printf("%s\n", (char*)Memcpy(buf, str, Strlen(str)));
    
    return 0;
}

