//
// Created by fx50j on 2023/9/3.
//

#ifndef LEETCODE_PRIORITYQUEUE_H
#define LEETCODE_PRIORITYQUEUE_H


#include <bits/stdc++.h>

template<typename Type> requires std::is_integral_v<Type>
class BinaryHeap {
public:
    BinaryHeap() = delete;

    ~BinaryHeap() = delete;

    // 调整为最大堆
    static void HeapAdjust(std::vector<Type> &vec,
                           int parent, int right) {
        auto children = 2 * parent + 1; // 左孩子
        while (children <= right) {
            if (children + 1 <= right && vec[children] < vec[children + 1]) {
                children += 1;
            }
            if (vec[parent] > vec[children]) {
                return;
            } else {
                std::swap(vec[parent], vec[children]);
                parent = children;
                children = 2 * children + 1;
            }
        }
    }

    // 将数组构建为二叉堆
    static void Heapify(std::vector<Type> &vec) {
        for (int i = (vec.size() / 2) - 1; i >= 0; --i) {
            BinaryHeap<Type>::HeapAdjust(vec,
                                         i, vec.size() - 1);
        }
    }

    // 入队操作
    static void HeapPush(std::vector<Type> &vec, Type val) {
        vec.push_back(val);
        auto old_index = vec.size() - 1;

        while ((old_index - 1) / 2 >= 0) {
            auto curr_index = (old_index - 1) / 2;
            if (vec[curr_index] > val) {
                break;
            }
            // 转移比val小的元素，类比插入排序
            vec[old_index] = vec[curr_index];
            old_index = curr_index;
        }
        vec[old_index] = val;
    }

    // 出队操作
    static Type HeapPop(std::vector<Type> &vec) {
        // 将最大元素调整到堆尾
        std::swap(vec.front(), vec.back());
        auto val = vec.back();
        vec.pop_back();
        if (vec.size() > 0) {
            BinaryHeap<Type>::HeapAdjust(vec,
                                         0, vec.size() - 1);
        }
        return val;
    }

    // 升序对排序
    static void HeapSort(std::vector<Type> &vec) {
        BinaryHeap<Type>::Heapify(vec);
        for (size_t i = vec.size() - 1; i > 0; --i) {
            std::swap(vec[0], vec[i]);
            BinaryHeap<Type>::HeapAdjust(vec, 0, i - 1);
        }
    }
};

template<typename Type> requires std::is_integral_v<Type>
class PriorityQueue {
private:
    int index_;
    std::vector<Type> queue_;
public:
    explicit PriorityQueue() : index_(0) { this->queue_.reserve(100); }

    void enQueue(Type val) {
        BinaryHeap<Type>::HeapPush(this->queue_, val);
        this->index_ += 1;
    }

    Type deQueue() {
        return BinaryHeap<Type>::HeapPop(this->queue_);
    }
};


#endif //LEETCODE_PRIORITYQUEUE_H
