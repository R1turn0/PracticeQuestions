#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode *pl1 = pHead1;
        ListNode *pl2 = pHead2;
        while (pl1 != pl2) {
            pl1 = pl1 ? pl1->next : pHead2;
            pl2 = pl2 ? pl2->next : pHead1;
        }
        return pl1;
    }
};

int main() {
    auto pHead1 = new ListNode(1);
    pHead1->next = new ListNode(2);
    pHead1->next->next = new ListNode(3);

    auto pHead2 = new ListNode(4);
    pHead2->next = new ListNode(5);

    auto pHead3 = new ListNode(6);
    pHead3->next = new ListNode(7);
//    pHead1->next->next->next = pHead3;
//    pHead2->next->next = pHead3;

    auto pHead = Solution::FindFirstCommonNode(pHead1, pHead2);
    while (pHead) {
        std::cout << pHead->val << " -> ";
        pHead = pHead->next;
    }
    std::cout << "NULL" << std::endl;
    return 0;
}
