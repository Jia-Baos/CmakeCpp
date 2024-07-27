#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
void Solution(std::vector<Type> &vec,
              const int left, const int right) {
    int parent = left;
    int children = 2 * parent + 1;  // 左孩子
    while (children <= right) {
        if (children + 1 <= right && vec[children] < vec[children + 1]) {
            children++;
        }
        if (vec[parent] > vec[children]) {
            return;
        } else {
            std::swap(vec[parent], vec[children]);
            parent = children;
            children = 2 * parent + 1;
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};

    for (int i = (vec.size() / 2) - 1; i >= 0; --i) {
        Solution(vec, i, vec.size() - 1);
    }

    for (int i = vec.size() - 1; i > 0; --i) {
        std::swap(vec[0],vec[i]);
        Solution(vec, 0, i - 1);
    }

    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}