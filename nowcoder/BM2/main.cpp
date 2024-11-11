#include <iostream>

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *tmp = nullptr;  // 用于记录反转区间后的第一个节点

    // 反转从第 m 到第 n 个节点之间的部分链表
    ListNode *reverseBetween(ListNode *pHead, int m, int n) {
        if (m == 1) {
            // 当 m == 1 时，直接从头部开始反转前 n 个节点
            return reverse(pHead, n);
        }
        // 递归到第 m-1 个节点，然后将其 next 指向反转后的子链表
        pHead->next = reverseBetween(pHead->next, m - 1, n - 1);
        return pHead;
    }

    // 递归反转链表的前 n 个节点
    ListNode *reverse(ListNode *pHead, int n) {
        if (n == 1) {
            // 当 n == 1 时，记录第 n+1 个节点到 tmp，后续连接反转部分
            tmp = pHead->next;
            return pHead;
        }
        // 递归反转前 n-1 个节点
        ListNode *newHead = reverse(pHead->next, n - 1);
        // 将反转部分的当前节点 pHead 连接到后面的节点上
        pHead->next->next = pHead;
        pHead->next = tmp;  // 连接反转部分之后的节点
        return newHead;
    }
};

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    // 反转第 2 到第 4 个节点
    Solution solution;
    head = solution.reverseBetween(head, 2, 4);

    // 打印结果
    ListNode *current = head;
    while (current != nullptr) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "NULL" << std::endl;

    // 清理内存
    while (head != nullptr) {
        ListNode *temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
