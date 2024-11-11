#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static ListNode *reverseList(ListNode *pHead) {
        if (!pHead || !pHead->next)
            return pHead;
        ListNode *ans = reverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
        return ans;
    }

    static ListNode *addInList(ListNode *pHead1, ListNode *pHead2) {
        if (!pHead1 || !pHead2) return pHead1 ? pHead1 : pHead2;

        auto res = new ListNode(-1);
        auto head = res;

        int carry = 0;

        pHead1 = reverseList(pHead1);
        pHead2 = reverseList(pHead2);

        while (pHead1 || pHead2 || carry) {
            int val1 = pHead1 ? pHead1->val : 0;
            int val2 = pHead2 ? pHead2->val : 0;

            int temp = val1 + val2 + carry;

            carry = temp / 10;
            temp %= 10;

            head->next = new ListNode(temp);
            head = head->next;

            pHead1 = pHead1 ? pHead1->next : nullptr;
            pHead2 = pHead2 ? pHead2->next : nullptr;
        }

        return reverseList(res->next);
    }
};

int main() {
    auto pHead1 = new ListNode(9);
    pHead1->next = new ListNode(3);
    pHead1->next->next = new ListNode(7);

    auto pHead2 = new ListNode(6);
    pHead2->next = new ListNode(3);

    auto pHead = Solution::addInList(pHead1, pHead2);
    while (pHead) {
        std::cout << pHead->val << " -> ";
        pHead = pHead->next;
    }
    std::cout << "NULL" << std::endl;
    return 0;
}
