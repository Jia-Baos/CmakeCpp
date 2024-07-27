//
// Created by fx50j on 2023/7/9.
//

#include "List.h"

void printList(ListNode *node) {
    // 始终打印头指针内容
    while (node) {
        std::cout << node->val_ << ", ";
        node = node->next_;
    }
    std::cout << std::endl;
}

ListNode *reverseList(ListNode *head) {
    ListNode *newhead = nullptr;
    ListNode *curr = head->next_;   // 指向头指针后面一个元素

    while (curr) {
        ListNode *next = curr->next_;
        curr->next_ = newhead;
        newhead = curr;
        curr = next;
    }

    head->next_ = newhead; // 将主序列连接到头指针

    return head;
}

ListNode *evenOddList(ListNode *head) {
    if (!head || !head->next_ || !head->next_->next_) {
        return head;
    }


    ListNode *odd = head->next_;
    ListNode *even = head->next_->next_;
    ListNode *even_head = head->next_->next_;
    bool isOdd = true;

    ListNode *curr = head->next_->next_->next_;
    while (curr) {
        if (isOdd) {
            odd->next_ = curr;
            odd = curr;
        } else {
            even->next_ = curr;
            even = curr;
        }
        curr = curr->next_;
        isOdd = !isOdd;
    }

    odd->next_ = even_head;
    even->next_ = nullptr;

    return head;
}

int palindromicList(ListNode *head) {
    if (!head->next_->next_) {
        return 0;
    }

    std::vector<int> vec;
    ListNode *iter = head->next_;
    while (iter) {
        vec.push_back(iter->val_);
        iter = iter->next_;
    }

    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        if (vec[left] != vec[right]) {
            return 1;
        } else {
            left += 1;
            right -= 1;
        }
    }

    return 0;
}

ListNode *bubbleSort(ListNode *head) {
    ListNode *node_i = head->next_;
    ListNode *node_tail = nullptr;

    // 外层循环次数，链表节点个数
    while (node_i) {
        ListNode *node_j = head->next_;
        // 内层循环次数，每次减一
        while (node_j && node_j->next_ != node_tail) {
            if (node_j->val_ > node_j->next_->val_) {
                std::swap(node_j->val_, node_j->next_->val_);
            }
            node_j = node_j->next_;
        }

        // 尾指针向前移动 1 位，此时尾指针右侧为排好序的链表
        node_tail = node_j;
        node_i = node_i->next_;
    }

    return head;
}

ListNode *selectSortPure(ListNode *head) {
    ListNode *node_i = head->next_;

    // node_i 为当前未排序链表的第一个链节点
    while (node_i && node_i->next_) {

        // node_min 为未排序链表中的值最小节点
        ListNode *node_min = node_i;
        ListNode *node_j = node_i->next_;

        while (node_j) {
            if (node_j->val_ < node_min->val_) {
                node_min = node_j;
            }
            node_j = node_j->next_;
        }

        // 交换值最小节点与未排序链表中第一个节点的值
        if (node_i->val_ != node_min->val_) {
            std::swap(node_i->val_, node_min->val_);
        }
        node_i = node_i->next_;
    }

    return head;
}

ListNode *selectSort(ListNode *head) {
    ListNode *node_i = head->next_;

    while (node_i) {
        ListNode *node_j = node_i->next_;
        while (node_j) {
            if (node_i->val_ > node_j->val_) {
                // 与选择排序记录位置不同，这里直接交换
                // 保证前面的序列始终是有序的
                std::swap(node_i->val_, node_j->val_);
            }
            node_j = node_j->next_;
        }

        node_i = node_i->next_;
    }

    return head;
}

ListNode * insertSort(ListNode* head)
{
    ListNode* dummy_head = new ListNode(0);
    dummy_head->next_ = head->next_;

    ListNode * sorted_list = head->next_;
    ListNode * curr  = head->next_->next_;
    while(curr)
    {
     if(sorted_list->val_<=curr->val_)
     {
         // 将 curr 插入到 sorted_list 之后
         sorted_list = sorted_list->next_;
     }
     else
     {
         ListNode * node_prev = dummy_head;
         while(node_prev->next_->val_<= curr->val_)
         {
             node_prev = node_prev->next_;
         }

         // 将 curr 移动到链表中间
         sorted_list->next_ = curr->next_;
         curr->next_ = node_prev->next_;
         node_prev->next_ = curr;
     }

     curr  = sorted_list->next_;
    }

    return dummy_head;
}