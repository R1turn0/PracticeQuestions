#include <iostream>
#include <vector>
#include <queue>

struct ListNode {
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // 两个有序链表合并函数
    ListNode *Merge2(ListNode *pHead1, ListNode *pHead2) {
        // 一个为空直接返回另一个
        if ((!pHead1) || (!pHead2)) return pHead1 ? pHead1 : pHead2;

        // 加一个表头
        auto head = new ListNode(0);
        auto cur = head;

        // 当链表为空结束循环
        while (pHead1 && pHead2) {
            // 比较选出最小值
            if (pHead1->val <= pHead2->val) {
                cur->next = pHead1;
                pHead1 = pHead1->next;
            } else {
                cur->next = pHead2;
                pHead2 = pHead2->next;
            }
            cur = cur->next; // 指针后移
        }
        cur->next = (pHead1 ? pHead1 : pHead2); // 剩下的链表直接连在后边
        return head->next; // 返回值去掉表头
    }

    //划分合并区间函数
    ListNode *divideMerge(std::vector<ListNode *> &lists, int left, int right) {
        if (left > right)
            return nullptr;
        else if (left == right)
            return lists[left];
        //从中间分成两段，再将合并好的两段合并
        int mid = (left + right) >> 1;
        return Merge2(divideMerge(lists, left, mid),
                      divideMerge(lists, mid + 1, right));
    }

    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        //k个链表归并排序
        return divideMerge(lists, 0, lists.size() - 1);
    }
};

class Solution1 {
public:
    // 对于两个链表的合并
    ListNode *mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        auto head = new ListNode(0);
        ListNode *tail = head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr;
                aPtr = aPtr->next;
            } else {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head->next;
    }

    // 利用分治 对每一个小组链表进行合并
    ListNode *merge(std::vector<ListNode *> &lists, int left, int right) {
        if (left == right)
            return lists[left];
        if (left > right)
            return nullptr;
        int mid = (right + left) >> 1;
        return mergeTwoLists(merge(lists, left, mid), merge(lists, mid + 1, right));
    }

    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};


/*
 * 方法二：优先队列（扩展思路）
 * 知识点：优先队列
 *
 * 优先队列即PriorityQueue，是一种内置的机遇堆排序的容器，分为大顶堆与小顶堆，大顶堆的堆顶为最大元素，其余更小的元素在堆下方，小顶堆与其刚好相反。且因为容器内部的次序基于堆排序，因此每次插入元素时间复杂度都是O(log 2 n)，而每次取出堆顶元素都是直接取出。
 *
 * 思路：
 *
 * 如果非要按照归并排序的合并思路，双指针不够用，我们可以直接准备k个指针，每次比较得出k个数字中的最小值。为了快速比较k个数字得到最小值，我们可以利用Java提供的PriorityQueue或者C++SLT提供的优先队列或者Python提供的PriorityQueue可以实现，它是一种参照堆排序的容器，容器中的元素是有序的，如果是小顶堆，顶部元素就是最小的，每次可以直接取出最小的元素。
 *
 * 也就是说每次该容器中有k个元素，我们可以直接拿出最小的元素，再插入下一个元素，相当于每次都是链表的k个指针在比较大小，只移动最小元素的指针。
 *
 * 具体做法：
 *
 * step 1：不管是Java还是C++都需要重载比较方法，构造一个比较链表节点大小的小顶堆。（Python版本直接加入节点值）
 * step 2：先遍历k个链表头，将不是空节点的节点加入优先队列。
 * step 3：每次依次弹出优先队列中的最小元素，将其连接在合并后的链表后面，然后将这个节点在原本链表中的后一个节点（如果不为空的话）加入队列，类似上述归并排序双指针的过程。
 */
class Solution2 {
public:
    struct cmp {
        // 重载小顶堆比较方式
        bool operator()(ListNode *a, ListNode *b) {
            return a->val > b->val;
        }
    };

    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        //小顶堆
        std::priority_queue<ListNode *, std::vector<ListNode *>, cmp> pq;
        //遍历所有链表第一个元素
        for (auto &list: lists) {
            //不为空则加入小顶堆
            if (list != nullptr)
                pq.push(list);
        }
        //加一个表头
        auto *res = new ListNode(-1);
        auto head = res;
        //直到小顶堆为空
        while (!pq.empty()) {
            //取出最小的元素
            ListNode *temp = pq.top();
            pq.pop();
            //连接
            head->next = temp;
            head = head->next;
            //每次取出链表的后一个元素加入小顶堆
            if (temp->next != nullptr)
                pq.push(temp->next);
        }
        return res->next;
    }
};

int main() {
    ListNode *output = nullptr;
    std::vector<ListNode *> lists;

    auto *l1 = new ListNode(-5);
    lists.push_back(l1);

    auto *l2 = new ListNode(-9);
    l2->next = new ListNode(-8);
    l2->next->next = new ListNode(-7);
    l2->next->next->next = new ListNode(-5);
    l2->next->next->next->next = new ListNode(1);
    l2->next->next->next->next->next = new ListNode(1);
    l2->next->next->next->next->next->next = new ListNode(1);
    l2->next->next->next->next->next->next->next = new ListNode(3);
    lists.push_back(l2);

    auto *l3 = new ListNode(-10);
    l3->next = new ListNode(-7);
    l3->next->next = new ListNode(-6);
    l3->next->next->next = new ListNode(-6);
    l3->next->next->next->next = new ListNode(-6);
    l3->next->next->next->next->next = new ListNode(0);
    l3->next->next->next->next->next->next = new ListNode(1);
    l3->next->next->next->next->next->next->next = new ListNode(3);
    l3->next->next->next->next->next->next->next->next = new ListNode(3);
    lists.push_back(l3);

    auto *l4 = new ListNode(-10);
    l4->next = new ListNode(-8);
    l4->next->next = new ListNode(-7);
    l4->next->next->next = new ListNode(-2);
    l4->next->next->next->next = new ListNode(3);
    l4->next->next->next->next->next = new ListNode(3);
    lists.push_back(l4);

    auto *l5 = new ListNode(-1);
    l5->next = new ListNode(4);
    lists.push_back(l5);

    auto *l6 = new ListNode(-5);
    l6->next = new ListNode(-4);
    l6->next->next = new ListNode(-1);
    lists.push_back(l6);

    Solution sln;
    output = sln.mergeKLists(lists);
    while (output != nullptr) {
        std::cout << output->val << " -> ";
        output = output->next;
    }
    std::cout << "NULL" << std::endl;

    while (output != nullptr) {
        ListNode *temp = output;
        output = output->next;
        delete temp;
    }

    return 0;
}
