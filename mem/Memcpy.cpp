#include <cstdio>

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

int main()
{
    char buf[32] = {0};
    char str[32] = "Hello";

    printf("%s\n", static_cast<char*>(Memcpy(buf, str, 5)));
    
    return 0;
}

