#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static bool hasCycle(ListNode *head) {
        if ((!head) || (!(head->next))) return false;
        // 快慢指针
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return true;
        }
        return false;
    }
};

int main() {
    auto pHead = new ListNode(3);
    pHead->next = new ListNode(2);
    pHead->next->next = new ListNode(0);
    pHead->next->next->next = new ListNode(-4);
    pHead->next->next->next->next = pHead->next;
    std::cout << (Solution::hasCycle(pHead) ? "true" : "false") << std::endl;
    return 0;
}
