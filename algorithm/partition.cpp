#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(nullptr){}
};

ListNode* partition(ListNode* head, int x)
{
    ListNode node(0);
    node.next = head;

    ListNode* big = nullptr;
    ListNode* small = nullptr;
    ListNode* bighead = nullptr;

    ListNode* cur = head;
    while(cur)
    {
        if(cur->val >= x)
        {
            if(big == nullptr)
            {
                big = cur;
                bighead = big;
            }
            else
            {
                big->next = cur;
                big = big->next;
            }
        }
        else
        {
            if(small == nullptr)
            {
                small = cur;
                node.next = small;
            }
            else
            {
                small->next = cur;
                small = small->next;
            }
        }
        cur = cur->next;
    }

    if(small)
        small->next = bighead;
    if(big)
        big->next = nullptr;

    return node.next;
}

void print(ListNode* head)
{
    while(head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main()
{
    ListNode* head = nullptr;
    ListNode _1(1);
    ListNode _2(4);
    ListNode _3(3);
    ListNode _4(2);
    ListNode _5(5);
    ListNode _6(2);
    head = &_1;
    _1.next = &_2;
    _2.next = &_3;
    _3.next = &_4;
    _4.next = &_5;
    _5.next = &_6;
    head = partition(head, 3);
    print(head);
}

