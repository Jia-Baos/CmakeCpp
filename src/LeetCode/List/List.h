//
// Created by fx50j on 2023/7/9.
//

#ifndef GEODESICDISTANCE_LIST_H
#define GEODESICDISTANCE_LIST_H


#include <bits/stdc++.h>

struct ListNode {
    int val_;
    ListNode *next_;

    explicit ListNode(int val) :
            val_(val), next_(nullptr) {}
};

class MyLinkerList {
public:
    int size_;
    ListNode *head_;

public:
    // 头节点的val_为o
    MyLinkerList() {
        this->size_ = 0;
        this->head_ = new ListNode(0);
    }

    // 链表深拷贝
    MyLinkerList *clone() const {
        MyLinkerList *newlinkerlist = new MyLinkerList();
        ListNode *iter = this->head_->next_;
        while (iter) {
            newlinkerlist->addAtTail(iter->val_);
            iter = iter->next_;
        }
        return newlinkerlist;
    }

    // 获取索引为index的元素
    int get(int index) const {
        if (index < 0 || index >= this->size_) {
            return -1;
        }

        // 头指针后第一节点的index为0
        ListNode *cur = this->head_;
        for (size_t i = 0; i <= index; i++) {
            cur = cur->next_;
        }

        return cur->val_;
    }

    // 链表指定索引处添加元素
    void addAtIndex(int index, int val) {
        if (index > this->size_) {
            return;
        }

        index = std::max(0, index);
        this->size_ += 1;

        ListNode *pred = this->head_;
        // 获取当前插入位置前一个元素的指针
        for (size_t i = 0; i < index; i++) {
            pred = pred->next_;
        }

        ListNode *toAdd = new ListNode(val);
        // 先链接后节点再连接前节点
        toAdd->next_ = pred->next_;
        pred->next_ = toAdd;
    }

    // 链表头部添加元素
    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    // 链表尾部添加元素
    void addAtTail(int val) {
        addAtIndex(this->size_, val);
    }

    // 删除链表指定索引处元素
    void deleteAtindex(int index) {
        if (index < 0 || index >= this->size_) {
            return;
        }

        this->size_ -= 1;
        ListNode *pred = this->head_;
        for (size_t i = 0; i < index; i++) {
            pred = pred->next_;
        }

        ListNode *toDelete = pred->next_;
        pred->next_ = pred->next_->next_;
        delete toDelete;
    }
};

struct DListNode {
    int val_;
    DListNode *prev_;
    DListNode *next_;

    DListNode(int val) :
            val_(val), prev_(nullptr), next_(nullptr) {}
};

class MyLinkerListDouble {
private:
    int size_;
    DListNode *head_;
    DListNode *tail_;

public:
    MyLinkerListDouble() {
        this->size_ = 0;
        this->head_ = new DListNode(0);
        this->tail_ = new DListNode(0);
        this->head_->next_ = this->tail_;
        this->tail_->prev_ = this->head_;
    }

    int get(int index) {
        if (index < 0 || index >= this->size_) {
            return -1;
        }

        DListNode *cur; // 根据index的位置选择起始位置
        if (index < this->size_ - index) {
            cur = this->head_;
            for (size_t i = 0; i <= index; i++) {
                cur = cur->next_;
            }
        } else {
            cur = this->tail_;
            for (size_t i = this->size_; i > index; i--) {
                cur = cur->prev_;
            }
        }

        return cur->val_;
    }

    void addAtIndex(int index, int val) {
        if (index > this->size_) {
            return;
        }

        index = std::max(0, index);

        DListNode *pred;
        DListNode *succ;
        if (index < this->size_ - index) {
            pred = this->head_;
            for (size_t i = 0; i < index; i++) {
                pred = pred->next_;
            }

            succ = pred->next_;
        } else {
            succ = this->tail_;
            for (size_t i = this->size_; i > index; i--) {
                succ = succ->prev_;
            }

            pred = succ->prev_;
        }

        this->size_ += 1;

        DListNode *toAdd = new DListNode(val);
        toAdd->prev_ = pred;
        toAdd->next_ = succ;
        pred->next_ = toAdd;
        succ->prev_ = toAdd;
    }

    void addAtHead(int val) {
        addAtIndex(0, val);
    }

    void addAtTail(int val) {
        addAtIndex(this->size_, val);
    }

    void deleteAtindex(int index) {
        if (index < 0 || index >= this->size_) {
            return;
        }

        DListNode *pred;
        DListNode *succ;
        if (index < this->size_ - index) {
            pred = this->head_;
            for (size_t i = 0; i < index; i++) {
                pred = pred->next_;
            }

            succ = pred->next_->next_;
        } else {
            succ = this->tail_;
            for (size_t i = this->size_ - 1; i > index; i--) {
                succ = succ->prev_;
            }

            pred = succ->prev_->prev_;
        }

        this->size_ -= 1;

        DListNode *toDelte = pred->next_;
        // DListNode *toDelte = succ->prev_;
        pred->next_ = succ;
        succ->prev_ = pred;
        delete toDelte;
    }
};

// 打印链表
void printList(ListNode *node);

// 反转链表
ListNode *reverseList(ListNode *head);

//奇偶链表
ListNode *evenOddList(ListNode *head);

// 回文链表
int palindromicList(ListNode *head);

// 冒泡排序
ListNode *bubbleSort(ListNode *head);

// 选择排序Pure
ListNode *selectSortPure(ListNode *head);

// 选择排序
ListNode *selectSort(ListNode *head);

// 插入排序
ListNode *insertSort(ListNode *head);

#endif //GEODESICDISTANCE_LIST_H
