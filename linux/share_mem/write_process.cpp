#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>

#include "share_mem.h"

using namespace std;

int main()
{
    MemPtr share_mem;
    if(CreateSharedMemory("wr_mem", 256, share_mem))
    {
        cout << "mem size : " << share_mem.m_size << " mem_name: "
            << share_mem.m_name << endl;
    }

    int count = 10;
    while(count--)
    {
        snprintf(share_mem.m_p_share_mem, 256, "count:%d\n", count);
        sleep(1);
    }

    CloseSharedMemory(share_mem);
    return 0;
}

