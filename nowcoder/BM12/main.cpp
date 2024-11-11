#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {};
};

/* 错误写法 */
//class Solution {
//public:
//    static void bubbleSort(int *num, size_t size) {
//        for (int i = 0; i < size; i++) {
//            for (int j = 0; j < size - i - 1; j++) {
//                if (num[j] > num[j + 1]) {
//                    num[j] ^= num[j + 1];
//                    num[j + 1] ^= num[j];
//                    num[j] ^= num[j + 1];
//                }
//            }
//        }
//    }
//
//    static ListNode *sortInList(ListNode *head) {
//        if (!head || !head->next) return head;
//
//        auto fast = head;
//        auto last = head;
//
//        while (fast) {
//            while (last && last->next) {
//                if (last->val > last->next->val) {
//                    // 错误写法：最好不要交换数据
//                    last->val ^= last->next->val;
//                    last->next->val ^= last->val;
//                    last->val ^= last->next->val;
//                }
//                last = last->next;
//            }
//            fast = fast->next;
//            last = head;
//        }
//
//        return head;
//    }
//};

class Solution {
public:
    static ListNode *merge(ListNode *pHead1, ListNode *pHead2) {
        if (!pHead1 || !pHead2) return pHead1 ? pHead1 : pHead2;
        auto head = new ListNode(-1);
        auto cur = head;

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
        return head->next;
    }

    static ListNode *sortInList(ListNode *head) {
        if (!head || !head->next)
            return head;
        ListNode *left = head;
        ListNode *mid = head->next;
        ListNode *right = head->next->next;

        while (right && right->next) {
            left = left->next;
            mid = mid->next;
            right = right->next->next;
        }
        left->next = nullptr;

        return merge(sortInList(head), sortInList(mid));
    }
};

int main() {
    auto pHead = new ListNode(-1);
    pHead->next = new ListNode(0);
    pHead->next->next = new ListNode(-2);
//    pHead->next->next->next = new ListNode(4);
//    pHead->next->next->next->next = new ListNode(5);
//    pHead->next->next->next->next->next = new ListNode(-5);

    pHead = Solution::sortInList(pHead);
    while (pHead) {
        std::cout << pHead->val << " -> ";
        pHead = pHead->next;
    }
    std::cout << "NULL" << std::endl;

    return 0;
}
