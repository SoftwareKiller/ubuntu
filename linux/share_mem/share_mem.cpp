#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>

#include "share_mem.h"

bool IsShareMemoryExists(const char* name)
{
    int32_t fd = -1;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = shm_open(name, O_RDONLY, mode);
    if(fd > -1)
    {
        close(fd);
        return false;
    }

    return true;
}

bool CreateSharedMemory(const char* name, uint64_t size, MemPtr& ret_mem)
{
    void* mem_ptr = nullptr;
    bool is_new = false;
    int32_t ret = 0;
    MemPtr& ptr = ret_mem;
    ptr.m_p_fd = nullptr;
    ptr.m_p_share_mem = nullptr;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    int32_t fd = -1;

    //删除共享内存
    shm_unlink(name);

    if(fd < 0)
    {
        is_new = true;

        //打开创建共享内存
        fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, mode);
        if(fd > 0)
        {
            //重置共享内存文件大小
            ret = ftruncate(fd, size);
            if(ret != 0)
                return false;
        }
    }

    if(!fd)
        return false;

    if(!is_new)
    {
        struct stat sb;
        //查看文件状态
        ret = fstat(fd, &sb);
        if(ret < 0)
            return false;

        if((int32_t)size < sb.st_size)
            size = sb.st_size;
    }

    //地址映射
    mem_ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mem_ptr == MAP_FAILED)
        return false;

    ptr.m_is_new = is_new;
    ptr.m_p_share_mem = (char*)mem_ptr;
    ptr.m_p_fd = (void*)fd;
    ptr.m_size = size;
    strncpy(ptr.m_name, name, 256);
    printf("[createSharedMemory] name : %s", ptr.m_name);
    
    return true;
}

bool OpenSharedMemory(const char* name, MemPtr& ret_ptr)
{
    int32_t fd = -1;
    uint64_t size = 0;
    int32_t ret = 0;
    void* mem_ptr;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    fd = shm_open(name, O_RDWR, mode);
    if(!fd)
        return false;

    if(fd > 0)
    {
        struct stat sb;
        ret = fstat(fd, &sb);
        if(ret < 0)
            return false;

        size = sb.st_size;
    }

    mem_ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(mem_ptr == MAP_FAILED)
        return false;

    ret_ptr.m_is_new = false;
    ret_ptr.m_p_share_mem = (char*)mem_ptr;
    ret_ptr.m_p_fd = (void*)fd;
    ret_ptr.m_size = size;
    strncpy(ret_ptr.m_name, name, 256);
    
    return false;
}

void CloseSharedMemory(MemPtr& ptr)
{
    int32_t ret = 0;

    ret = munmap(ptr.m_p_share_mem, ptr.m_size);
    if(ret < 0)
        return;

    ret = close((unsigned long int)ptr.m_p_fd);
    if(ret < 0)
        return;

    return;
}

