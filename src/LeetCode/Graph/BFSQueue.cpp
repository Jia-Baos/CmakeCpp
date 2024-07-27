#include <bits/stdc++.h>

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

void BFSQueue(std::unordered_map<char, std::vector<char>> &graph,
              const char start) {
    // 标记并访问节点
    std::set<char> visited{start};
    std::cout << start << std::endl;

    auto queue = new AssociateQueue<char>();
    queue->enQueue(start);

    while (!queue->is_empty()) {
        auto curr_char = queue->frontElem();
        queue->deQueue();
        for (auto iter: graph[curr_char]) {
            if (visited.find(iter) == visited.end()) {
                visited.insert(iter);
                queue->enQueue(iter);
                std::cout << iter << std::endl;
            }
        }

    }
}


int main() {
    std::unordered_map<char, std::vector<char>> graph{
            {'A', {'B', 'C'}},
            {'B', {'A', 'C', 'D'}},
            {'C', {'A', 'B', 'D', 'E'}},
            {'D', {'B', 'C', 'E', 'F'}},
            {'E', {'C', 'D'}},
            {'F', {'D'}}
    };

    BFSQueue(graph, 'A');
}