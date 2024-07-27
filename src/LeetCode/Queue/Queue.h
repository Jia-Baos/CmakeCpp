//
// Created by fx50j on 2023/8/7.
//

#ifndef LEETCODE_QUEUE_H
#define LEETCODE_QUEUE_H

#include <vector>
#include <iostream>

/*
 * 避免假溢出的解决方案一
 * 每次删除队头元素之后，
 * 就将整个队列往前移动一个位置
 * 每次出队的复杂度为O(N)
*/
template<typename Type>
class SequentialQueueType1 {
public:
    int capacity_;
    int front_;
    int rear_;
    std::vector<Type> queue_;
public:
    SequentialQueueType1() :
    capacity_(100), front_(-1), rear_(-1) { queue_.reserve(capacity_); }

    // 判断队列是否为空
    int is_empty() {
        return this->front_ == this->rear_;
    }

    // 判断队列是否已满
    int is_full() {
        return this->rear_ + 1 == this->capacity_;
    }

    // 入栈操作
    void enQueue(Type val) {
        if (this->is_full()) {
            std::cerr << "Queue is full..." << std::endl;
        } else {
            this->rear_ += 1;
            this->queue_[this->rear_] = val;
        }
    }

    // 出队操作
    Type deQueue() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            int value = this->queue_.front();
            for (size_t i = 0; i < this->rear_; ++i) {
                this->queue_[i] = this->queue_[i + 1];
            }
            this->rear_ -= 1;
            return value;
        }
    }

    // 获取队头元素
    Type frontElem() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            return this->queue_[this->front_ + 1];
        }
    }

    // 获取队尾元素
    Type rearElem() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            return this->queue_[this->rear_];
        }
    }
};

/*
 * 避免假溢出的解决方案一
 * 将队列想象为头尾相连的循环表，
 * 利用数学中的求模运算
 */
template<typename Type>
class SequentialQueueType2 {
public:
    int capacity_;
    int size_;  // 添加 size_ 成员变量记录元素个数
    int front_;
    int rear_;
    std::vector<Type> queue_;
public:
    // 因为采用了取余操作，所以必须以0作为起点
    SequentialQueueType2() : capacity_(101), size_(0),
                             front_(0), rear_(0) { queue_.reserve(capacity_); }

    // 判断队列是否为空
    int is_empty1() {
        return this->size_ == 0;
    }

    int is_empty2() {
        return this->front_ == this->rear_;
    }

    // 判断队列是否已满
    int is_full1() {
        return this->size_ == this->capacity_ - 1;
    }

    int is_full2() {
        return (this->rear_ + 1) % this->capacity_ == this->front_;
    }

    // 入栈操作
    void enQueue(Type val) {
        if (this->is_full2()) {
            std::cerr << "Queue is full..." << std::endl;
        } else {
            this->rear_ = (this->rear_ + 1) % this->capacity_;
            this->queue_[this->rear_] = val;
            this->size_ += 1;
        }
    }

    // 出队操作
    void deQueue() {
        if (this->is_empty2()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            this->front_ = (this->front_ + 1) % this->capacity_;
            this->size_ -= 1;
        }
    }

    // 获取队头元素
    Type frontElem() {
        if (this->is_empty2()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            int value = this->queue_[(this->front_ + 1) % this->capacity_];
            return value;
        }
    }

    // 获取队尾元素
    Type rearElem() {
        if (this->is_empty2()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            return this->queue_[this->rear_];
        }
    }
};

template<typename Type>
struct ListNode {
    Type val_;
    ListNode *next_;
    explicit ListNode(int val) : val_(val), next_(nullptr) {}
};

template<typename Type>
class AssociateQueue {
public:
    ListNode<Type> *head_;
    ListNode<Type> *front_;
    ListNode<Type> *rear_;

    // 初始化空队列
    AssociateQueue() {
        this->head_ = new ListNode<Type>(0);
        this->front_ = this->head_;
        this->rear_ = this->head_;
    }

    // 判断队列是否为空
    int is_empty() {
        return this->front_ == this->rear_;
    }

    // 入队操作
    void enQueue(int val) {
        auto curr_node = new ListNode<Type>(val);
        this->rear_->next_ = curr_node;
        this->rear_ = curr_node;
    }

    // 出队操作
    void deQueue() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            auto curr_node = this->front_->next_;
            this->front_->next_ = curr_node->next_;
            // 当队列中最后一个元素出队时，
            // 需要将 rear_ 重新指向 front_
            if (this->rear_ == curr_node) {
                this->rear_ = this->front_;
            }
            delete curr_node;
        }
    }

    // 获取队头元素
    Type frontElem() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            return this->front_->next_->val_;
        }
    }

    // 获取队尾元素
    Type rearElem() {
        if (this->is_empty()) {
            std::cerr << "Queue is empty..." << std::endl;
        } else {
            return this->rear_->val_;
        }
    }
};


#endif //LEETCODE_QUEUE_H
