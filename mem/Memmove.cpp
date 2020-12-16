#include <cmath>
#include <cstdio>
#include <cstring>

void *Memmove(void* dest, void* src, size_t n)
{
    if(dest == nullptr || src == nullptr)
        return nullptr;
    char* ptr_addr1 = static_cast<char*>(dest);
    const char* ptr_addr2 = static_cast<char*>(src);
    int diff = ptr_addr1 - ptr_addr2;
    if(std::abs(diff) > n || ptr_addr1 < ptr_addr2)
    {
        while(n--)
        {
            *ptr_addr1++ = *ptr_addr2++;
        }
    }
    else
    {
        if(ptr_addr1 == ptr_addr2)
        {
            return dest;
        }
        if(ptr_addr1 > ptr_addr2)
        {
            for(int i = n - 1; i >= 0; --i)
            {
                *(ptr_addr1 + i) = *(ptr_addr2 + i);
            }
        }
    }

    return dest;
}

int main()
{
    char buff1[32] = "Hello World";
    char* ptr = buff1 + 1;
    printf("%s\n", Memmove(ptr, buff1, strlen(buff1) + 1));
    printf("%s\n", buff1);
}

