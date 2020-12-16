#include <stdio.h>

int Strlen(char* str)
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
    char str[32] = "Hello";
    printf("%d\n", Strlen(str));
    
    return 0;
}

