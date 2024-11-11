#include <iostream>
#include <list>

struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {} // 构造函数初始化列表
};

class Solution {
public:
    static ListNode *ReverseList(ListNode *pHead) {
        if (!pHead || !pHead->next)
            return pHead;
        ListNode *ans = ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
        return ans;
    }
    
    static ListNode *ReverseList2(ListNode* pHead) {
        if(!pHead)
            return nullptr;
        ListNode* cur = pHead;
        ListNode* pre = nullptr;
        while(cur){
            //断开链表，要记录后续一个
            ListNode* temp = cur->next;
            //当前的next指向前一个
            cur->next = pre;
            //前一个更新为当前
            pre = cur;
            //当前更新为刚刚记录的后一个
            cur = temp;
        }
        return pre;
    }
};

int main() {
    auto *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    auto *ans = Solution::ReverseList(head);
    return 0;
}
