#include "header.h"

#define PREFIX_SIZE (sizeof(size_t))

void decrRefCount(obj* o)
{
    if(o->refcount <= 0)
    {
        printf("decrRefCount against refcount <= 0");
        assert(NULL);
    }

    if(o->refcount == 1)
    {
        switch(o->type)
        {
        case SET:
            freeSetObject(o);
            break;
        default:
            printf("Unknown object type");
            break;
        }

        free(o);
    }
    else
    {
        o->refcount--;
    }
}

void freeSetObject(obj* o)
{
    void *realptr;
    size_t oldsize;

    if(o == NULL)
        return;

    realptr = (char*)o-PREFIX_SIZE;
    oldsize = *((size_t*)realptr);
    free(realptr);
}

