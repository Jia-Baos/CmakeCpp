#include <bits/stdc++.h>

void dfsRecursive(std::unordered_map<char, std::vector<char>> &graph,
                  const char start, std::set<char> &visited) {
    // 标记并访问节点
    visited.insert(start);
    std::cout << start << " ";

    for (const auto &iter: graph[start]) {
        if (visited.find(iter) == visited.end()) {
            dfsRecursive(graph, iter, visited);
        }
    }
}

int main() {
    std::set<char> visted{};
    std::unordered_map<char, std::vector<char>> graph{
            {'A', {'B', 'C'}},
            {'B', {'A', 'C', 'D'}},
            {'C', {'A', 'B', 'D', 'E'}},
            {'D', {'B', 'C', 'E', 'F'}},
            {'E', {'C', 'D'}},
            {'F', {'D'}}
    };

    dfsRecursive(graph, 'A', visted);
}