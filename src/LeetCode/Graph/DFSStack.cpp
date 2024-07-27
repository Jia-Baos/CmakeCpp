#include <bits/stdc++.h>

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

void dfsStack(std::unordered_map<char, std::vector<char>> &graph,
              const char start) {
    // 标记并访问节点
    std::set<char> visited{start};
    std::cout << start << std::endl;
    auto stack = new AssociateStack<char>();
    stack->push(start);

    while (!stack->is_empty()) {
        const char stack_top = stack->peek();   // 获取栈顶元素
        int index = 0;
        // 遍历栈顶元素的邻居，访问未被访问过的节点
        while (index < graph[stack_top].size()) {
            const char curr_char = graph[stack_top][index];
            if (visited.find(curr_char) == visited.end()) {
                std::cout << curr_char << std::endl;
                stack->push(curr_char);
                visited.insert(curr_char);
                break;
            }
            index += 1;
        }

        if (index == graph[stack_top].size()) {
            stack->pop();
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

    dfsStack(graph, 'A');
}