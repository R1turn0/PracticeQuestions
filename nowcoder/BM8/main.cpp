#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static ListNode* FindKthToTail(ListNode *pHead, int k) {
        if (!pHead) return nullptr;
        ListNode *fast = pHead, *slow = pHead;
        while (k--) {
            if (fast != nullptr) fast = fast->next;
            else return nullptr;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main() {
    auto pHead = new ListNode(0);
    pHead->next = new ListNode(2);
    pHead->next->next = new ListNode(3);
    pHead->next->next->next = new ListNode(4);
    pHead->next->next->next->next = new ListNode(5);

    pHead = Solution::FindKthToTail(pHead, 2);
    while (pHead) {
        std::cout << pHead->val << " -> " ;
        pHead = pHead->next ? pHead->next : nullptr;
    }
    std::cout << "NULL" << std::endl;

    return 0;
}
