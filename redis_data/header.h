#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SKIPLIST_MAXLEVEL 32
#define SKIPLIST_P 0.25

//对象类型
enum TYPE{
    SET
};

typedef struct Object{
    unsigned type:4;

    unsigned encoding:4;

    int refcount;

    void* ptr;
}obj;

typedef struct skipListLevel{
    struct skipListNode* forward;

    unsigned int span;
}skipListLevel;

typedef struct skipListNode{
    obj* object;

    double score;

    struct skipListNode* backward;

    struct _skipListLevel{
        struct skipListNode* forward;

        unsigned int span;
    }level[];
}skipListNode;

typedef struct skipList{
    struct skipListNode *header, *tail;

    unsigned long length;

    int level;
}skipList;

typedef struct set{
    skipList* sl;
}set;

typedef struct{
    double min, max;

    //标记最小值和最大值是否包含在范围内
    //1为不包含，0为包含
    int minex, maxex;
}rangespec;

//sklist interface
skipList* slCreate(void);
void slFree(skipList* sl);
skipListNode* slInsert(skipList* sl, double score, obj* object);
int slDelete(skipList* sl, double score, obj* object);
skipListNode* slFirstInRange(skipList* sl, rangespec* range);
skipListNode* slLastInRange(skipList* sl, rangespec* range);
double getScore(unsigned char* sptr);
void zlNext(unsigned char* zl, unsigned char** eptr, unsigned char** sptr);
void zlPrev(unsigned char* zl, unsigned char** eptr, unsigned char** sptr);
unsigned int setLength(obj* object);
void setCovert(obj* object, int encoding);
unsigned long slGetRank(skipList* sl, double score, obj* o);

//object
void decrRefCount(obj *o);
void freeSetObject(obj *o);

#endif
