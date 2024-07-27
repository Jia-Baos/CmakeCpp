//
// Created by fx50j on 2023/7/10.
//

#ifndef LEETCODE_Stack_H
#define LEETCODE_Stack_H

#include <bits/stdc++.h>

template<typename T>
class SequentialStack {
private:
    std::vector<T> SequentialStack_;
    int size_;
    int top_;
public:
    // 初始化空栈
    SequentialStack() : size_(100), top_(-1) {}

    // 判断栈是否为空
    [[nodiscard("no discard")]] int is_empty() const {
        return this->top_ == -1;
    }

    // 判断栈是否已满
    [[nodiscard("no discard")]] int is_full() const {
        return this->top_ + 1 == this->size_;
    }

    // 入栈操作
    void push(T value) {
        if (this->is_full()) {
            std::cerr << "Error: SequentialStack is full" << std::endl;
            exit(-1);
        } else {
            this->SequentialStack_.push_back(value);
            this->top_ += 1;
        }
    }

    // 出栈操作
    void pop() {
        if (this->is_empty()) {
            std::cerr << "Error: SequentialStack is empty" << std::endl;
            exit(-1);
        } else {
            this->SequentialStack_.pop_back();
            this->top_ -= 1;
        }
    }

    // 获取栈顶元素
    [[nodiscard("no discard")]] T peek() const {
        if (this->is_full()) {
            std::cerr << "Error: SequentialStack is full" << std::endl;
            exit(-1);
        } else {
            return this->SequentialStack_[this->top_];
        }
    }
};

template<typename T>
struct ListNode {
    T val_;
    ListNode *next_;

    explicit ListNode(T val) : val_(val), next_(nullptr) {}
};


template<typename T>
class AssociateStack {
private:
    ListNode<T> *top_;
public:
    AssociateStack() : top_(nullptr) {}

    // 判断栈是否为空
    [[nodiscard("no discard")]] int is_empty() const {
        return this->top_ == nullptr;
    }

    // 入栈操作
    void push(T value) {
        auto *curr = new ListNode(value);
        curr->next_ = this->top_;
        this->top_ = curr;
    }

    // 出栈操作
    void pop() {
        if (this->is_empty()) {
            std::cerr << "Error: AssociateStack is empty" << std::endl;
            exit(-1);
        } else {
            ListNode<T> *curr = this->top_;
            this->top_ = this->top_->next_;
            delete curr;
        }
    }

    // 获取栈顶元素
    [[nodiscard("no discard")]] T peek() const {
        if (this->is_empty()) {
            std::cerr << "Error: AssociateStack is empty" << std::endl;
            exit(-1);
        } else {
            return this->top_->val_;
        }
    }
};


#endif //LEETCODE_Stack_H
