#include <math.h>
#include "header.h"

skipListNode* slCreateNode(int level, double score, obj* o)
{
    size_t size = sizeof(skipListNode) + level * sizeof(skipListLevel);
    void* ptr = malloc(size);

    if(ptr == NULL)
    {
        printf("Out of memory\n");
        abort();
    }

    skipListNode* sln = (skipListNode*)ptr;
    
    sln->score = score;
    sln->object = o;

    return sln;
}

//创建并返回一个新的跳跃表
skipList* slCreate(void)
{
    int i;
    skipList* sl;

    sl = (skipList*)malloc(sizeof(*sl));

    sl->level = 1;
    sl->length = 0;
    sl->header = slCreateNode(SKIPLIST_MAXLEVEL, 0, NULL);

    for(i = 0; i < SKIPLIST_MAXLEVEL; ++i)
    {
        sl->header->level[i].forward = NULL;
        sl->header->level[i].span = 0;
    }

    sl->header->backward = NULL;

    sl->tail = NULL;

    return sl;
}

void slFreeNode(skipListNode* node)
{
    //decrRefCount(node->object);
    
    free(node);
}

void slFree(skipList* sl)
{
    skipListNode* node = sl->header->level[0].forward, *next;

    free(sl->header);

    while(node)
    {
        next = node->level[0].forward;

        slFreeNode(node);

        node = next;
    }

    free(sl);
}

int slRandomLevel(void)
{
    int level = 1;
    while((random()&0xFFFF) < (SKIPLIST_P * 0xFFFF))
        level += 1;

    return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
}

skipListNode* slInsert(skipList* sl, double score, obj* obj)
{
    skipListNode* update[SKIPLIST_MAXLEVEL], *x;
    unsigned int rank[SKIPLIST_MAXLEVEL];
    int i, level;

    assert(!isnan(score));  //判断score是否为数字

    x = sl->header;
    for(i = sl->level-1; i >= 0; --i)
    {
        rank[i] = i == (sl->level - 1) ? 0 : rank[i+1];

        //寻找合适从插入位置，并且让update的每一层指向应该增加节点的位置
        //也就是说，新节点的每一层，update将来会指向它
        //现在update的指针，指向新节点的后一位置，新节点会插入两者之间
        while(x->level[i].forward &&
              (x->level[i].forward->score < score || 
               x->level[i].forward->score == score /*&&)*/))
        {
            //记录当前层级的跨度
            rank[i] += x->level[i].span;
            //指针前进
            x = x->level[i].forward;
        }

        update[i] = x;
    }

    level = slRandomLevel();

    if(level > sl->level)
    {
        for(i = sl->level; i < level; ++i)
        {
            rank[i] = 0;
            update[i] = sl->header;
            update[i]->level[i].span = sl->length;
        }

        sl->level = level;
    }

    x = slCreateNode(level, score, obj);

    for(i = 0; i < level; ++i) {
        x->level[i].forward = update[i]->level[i].forward;

        update[i]->level[i].forward = x;

        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);

        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }

    for(i = level; i < sl->level; ++i)
    {
        update[i]->level[i].span++;
    }

    x->backward = (update[0] == sl->header) ? NULL : update[0];
    if(x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        sl->tail = x;

    sl->length++;

    return x;
}

void slDeleteNode(skipList* sl, skipListNode* x, skipListNode** update)
{
    int i;
    for(i = 0; i < sl->level; ++i)
    {
        if(update[i]->level[i].forward == x)
        {
            update[i]->level[i].span += x->level[i].span - 1;
            update[i]->level[i].forward = x->level[i].forward;
        }else
        {
            update[i]->level[i].span -= 1;
        }
    }

    if(x->level[0].forward)
    {
        x->level[0].forward->backward = x->backward;
    }
    else
    {
        sl->tail = x->backward;
    }

    while(sl->level > 1 && sl->header->level[sl->level - 1].forward == NULL)
        sl->level--;

    sl->length--;
}

int slDelete(skipList* sl, double score, obj* o)
{
    skipListNode* update[SKIPLIST_MAXLEVEL], *x;
    int i;

    x = sl->header;
    for(i = sl->level - 1; i >= 0; i--)
    {
        while(x->level[i].forward && 
              (x->level[i].forward->score < score))
        {
            x = x->level[i].forward;
        }

        update[i] = x;
    }

    x = x->level[0].forward;
    if(x && score == x->score)
    {
        slDeleteNode(sl, x, update);

        slFreeNode(x);

        return 1;
    }
    else
    {
        return 0;
    }

    return 0;
}

static int slValueGteMin(double value, rangespec* spec)
{
    return spec->minex ? (value > spec->min) : (value >= spec->min);
}

static int slValueLteMax(double value, rangespec* spec)
{
    return spec->maxex ? (value < spec->max) : ( value <= spec->max );
}

int slIsInRange(skipList* sl, rangespec* range)
{
    skipListNode* x;
    if(range->min > range->max || 
        (range->min == range->max && (range->minex || range->maxex)))
        return 0;

    x = sl->tail;
    if(x == NULL || !slValueGteMin(x->score, range))
        return 0;

    x = sl->header->level[0].forward;
    if(x == NULL || !slValueLteMax(x->score, range))
        return 0;
    
    return 1;
}

skipListNode* slFirstInRange(skipList* sl, rangespec* range)
{
    skipListNode* x;
    int i;

    if(!slIsInRange(sl, range))
        return NULL;

    x = sl->header;
    for(i = sl->level - 1; i >= 0; --i)
    {
        while(x->level[i].forward &&
            !slValueGteMin(x->level[i].forward->score, range))
            x = x->level[i].forward;
    }

    x = x->level[0].forward;
    assert(x != NULL);

    if(!slValueLteMax(x->score, range))
        return NULL;

    return x;
}

skipListNode* slLastInRange(skipList* sl, rangespec* range)
{
    skipListNode* x;
    int i;

    if(slLastInRange(sl, range))
        return NULL;

    x = sl->header;

    for(i = sl->level - 1; i >= 0; --i)
    {
        while(x->level[i].forward && 
              slValueLteMax(x->level[i].forward->score, range))
            x = x->level[i].forward;
    }

    assert(x != NULL);

    if(!slValueGteMin(x->score, range))
        return NULL;

    return x;
}

unsigned long slGetRank(skipList* sl, double score, obj* o)
{
    skipListNode* x;
    unsigned long rank = 0;
    int i;

    x = sl->header;
    for(i = sl->level - 1; i >= 0; --i)
    {
        while(x->level[i].forward &&
              x->level[i].forward->score <= score)
        {
            rank += x->level[i].span;

            x = x->level[i].forward;
        }

        if(x->score == score)
            return rank;
    }

    return 0;
}

void print(const skipList* sl)
{
    skipListNode* x = sl->header->level[0].forward;
    while(x)
    {
        printf("%lf ", x->score);
        x = x->level[0].forward;
    }
    printf(" Length : %ld\n", sl->length);
}

int main()
{
    skipList* slptr;
    slptr = slCreate();
    printf("Create skip List, skipList level is %d\n", slptr->level);
    slInsert(slptr, 3.8, NULL);
    slInsert(slptr, 3.9, NULL);
    slInsert(slptr, 4.1, NULL);
    printf("Create skip List, skipList level is %d\n", slptr->level);
    printf("Create skip List, skipList length is %ld\n", slptr->length);
    print(slptr);
    slDelete(slptr, 3.9, NULL);
    print(slptr);
    printf("Rank : %ld\n", slGetRank(slptr, 4.1, NULL));
    slFree(slptr);
    return 0;
}

