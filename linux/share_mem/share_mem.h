#ifndef _SHARE_MEM_M_
#define _SHARE_MEM_M_
#include <cstdint>

#pragma pack(push, 1)
struct ShareHeader
{
    int32_t  m_tag;
    uint64_t m_size;
};
#pragma pack(pop)

struct MemPtr
{
    bool        m_is_new;
    char*       m_p_share_mem;
    void*       m_p_fd;
    uint64_t    m_size;
    char        m_name[256];
};

bool CreateSharedMemory(const char* name, uint64_t size, MemPtr& ret_ptr);

bool OpenSharedMemory(const char* name, MemPtr& ret_ptr);

void CloseSharedMemory(MemPtr& ptr);

bool IsShareMemoryExists(const char* name);

void QuerySharedMemory(MemPtr& ptr);

#endif
