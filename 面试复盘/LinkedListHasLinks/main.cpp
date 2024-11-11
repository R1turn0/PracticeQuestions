#include<iostream>
#include<map>

using namespace std;

struct Node{
    int val{};
    Node* next=nullptr;
};

//class Solution {
//public:
//    map<Node*,Node*> deal;
//    bool Has_loop(Node* node)
//    {
//        if(node==nullptr||node->next==nullptr)
//            return false;
//        Node* p=node;
//        while(p)
//        {
//
//            if(deal[p] != nullptr)
//            {
//                return true;
//            }
//            deal[p]=p;
//            p=p->next;
//        }
//    }
//};

class Solution{
public:
    bool hasloop(Node* node)
    {
        if(node==nullptr||node->next==nullptr)
            return false;

        Node* fast, *second;
        fast=node;
        second = node;
        while(fast&&fast->next)
        {
            second = second -> next;
            fast = fast -> next -> next;
            if(fast == second)
                return true;
        }
        return false;
    }
};

int main()
{
    return 0;
}

