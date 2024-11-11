#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static ListNode *hasCycle(ListNode *pHead) {
        if ((!pHead) || (!(pHead->next)))
            return nullptr;
        ListNode *fast = pHead;
        ListNode *slow = pHead;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return slow;
        }
        return nullptr;
    }

    static ListNode* EntryNodeOfLoop(ListNode* pHead) {
        // 先判断是否有环，记录快慢指针相遇的节点
        ListNode *slow = hasCycle(pHead);
        if (!slow) return nullptr;
        // 让快指针回到链表头后慢移动，当快慢指针再次相遇的时候就是环的入口点
        ListNode* fast = pHead;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main() {
    auto pHead = new ListNode(1);
    pHead->next = new ListNode(2);
    pHead->next->next = new ListNode(3);
    pHead->next->next->next = new ListNode(4);
    pHead->next->next->next->next = new ListNode(5);
    pHead->next->next->next->next->next = pHead->next->next;
    std::cout << Solution::EntryNodeOfLoop(pHead)->val << std::endl;
    return 0;
}
