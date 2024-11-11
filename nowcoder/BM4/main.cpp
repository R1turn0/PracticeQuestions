#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *Merge(ListNode *pHead1, ListNode *pHead2) {
        ListNode *vHead = new ListNode(-1);
        ListNode *cur = vHead;

        while (pHead1 && pHead2) {
            if (pHead1->val <= pHead2->val) {
                cur->next = pHead1;
                pHead1 = pHead1->next;
            } else {
                cur->next = pHead2;
                pHead2 = pHead2->next;
            }
            cur = cur->next;
        }
        cur->next = pHead1 ? pHead1 : pHead2;
        return vHead->next;
    }

    ListNode *Merge2(ListNode *pHead1, ListNode *pHead2) {
        if (!pHead1) return pHead2;
        if (!pHead2) return pHead1;
        if (pHead1->val <= pHead2->val) {
            pHead1->next = Merge(pHead1, pHead2->next);
            return pHead1;
        } else {
            pHead2->next = Merge(pHead1->next, pHead2);
            return pHead2;
        }
    }
};

int main() {
    ListNode *pHead = nullptr;

    auto *pHead1 = new ListNode(1);
    pHead1->next = new ListNode(3);
    pHead1->next->next = new ListNode(5);

    auto *pHead2 = new ListNode(2);
    pHead2->next = new ListNode(4);
    pHead2->next->next = new ListNode(6);

    Solution solution;
    pHead = solution.Merge(pHead1, pHead2);

    // 打印结果
    ListNode *current = pHead;
    while (current != nullptr) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;

    // 清理内存
    while (pHead != nullptr) {
        ListNode *temp = pHead;
        pHead = pHead->next;
        delete temp;
    }

    return 0;
}
