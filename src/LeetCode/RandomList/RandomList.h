//
// Created by fx50j on 2023/7/9.
//

#ifndef LEETCODE_RANDOMLIST_H
#define LEETCODE_RANDOMLIST_H


#include <bits/stdc++.h>

struct RandomListNode {
    int val_;
    RandomListNode *next_;
    RandomListNode *random_;

    explicit RandomListNode(int val) : val_(val),
                                       next_(nullptr),
                                       random_(nullptr) {}
};

class Solution {
public:
    std::unordered_map<RandomListNode *, RandomListNode *> cachedNode;

    RandomListNode *copyRandomList(RandomListNode *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }
        if (!cachedNode.count(head))
        {
            RandomListNode *headNew = new RandomListNode(head->val_);
            cachedNode[head] = headNew;
            headNew->next_ = copyRandomList(head->next_);
            headNew->random_ = copyRandomList(head->random_);
        }
        return cachedNode[head];
    }


};


#endif //LEETCODE_RANDOMLIST_H
