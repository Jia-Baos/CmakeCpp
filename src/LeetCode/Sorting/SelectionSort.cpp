#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        auto index = i;
        // 注意 j 的范围的下限
        for (size_t j = i; j < vec.size(); ++j) {
            // 找到后子序列中的最小值
            if (vec[index] > vec[j]) {
                index = j;
            }
        }
        if (index != i) {
            std::swap(vec[i], vec[index]);
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