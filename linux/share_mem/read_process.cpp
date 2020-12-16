#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>

#include "share_mem.h"

using namespace std;

int main()
{
    MemPtr share_mem;
    if(OpenSharedMemory("wr_mem", share_mem))
    {
        cout << "mem size : " << share_mem.m_size << " mem_name: "
            << share_mem.m_name << endl;
    }

    int count = 10;
    while(count--)
    {
        printf("%s\n", share_mem.m_p_share_mem);
        sleep(1);
    }
    return 0;
}

