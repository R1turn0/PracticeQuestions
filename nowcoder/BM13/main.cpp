#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {};
};

class Solution {
public:
    static bool isPail(ListNode *head) {
        if (!head) return false;
        std::vector<int> vHead;
        while (head) {
            vHead.push_back(head->val);
            head = head->next;
        }
        auto fast = vHead.cbegin(), last = vHead.cend() - 1;
        while (fast != last && fast + 1 != last) {
            if (*fast != *last)
                return false;
            fast++, last--;
        }
        return true;
    }
};

class Solution2 {
public:
    static ListNode *reverseList(ListNode *pHead) {
        if (!pHead)
            return nullptr;
        ListNode *cur = pHead;
        ListNode *pre = nullptr;
        while (cur) {
            //断开链表，要记录后续一个
            ListNode *temp = cur->next;
            //当前的next指向前一个
            cur->next = pre;
            //前一个更新为当前
            pre = cur;
            //当前更新为刚刚记录的后一个
            cur = temp;
        }
        return pre;
    }

    static bool isPail(ListNode *head) {
        auto pHead = head;
        int lent = 0;
        while (pHead) { lent++, pHead = pHead->next; }
        lent = lent >> 1;
        pHead = head;
        while (lent > 0) { pHead = pHead->next, lent--; }
        auto reHead = reverseList(pHead);
        pHead = head;
        while (reHead || pHead) {
            if (reHead->val != pHead->val)
                return false;
            reHead = reHead->next;
            pHead = pHead->next;
        }
        return true;
    }
};

int main() {
    auto head = new ListNode(1);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next->next = new ListNode(4);
    head->next->next->next->next->next->next->next = new ListNode(3);
    head->next->next->next->next->next->next->next->next = new ListNode(2);
    head->next->next->next->next->next->next->next->next->next = new ListNode(1);
    std::cout << Solution2::isPail(head) << std::endl;
    return 0;
}
