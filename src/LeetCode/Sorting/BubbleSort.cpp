#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        // 注意 j 的范围的上限
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};
    int val = Solution(vec);
    std::cout << "return val: " << val << std::endl;
    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}