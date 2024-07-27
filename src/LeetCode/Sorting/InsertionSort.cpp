#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        auto j = i;
        auto tmp = vec[i];
        // 将 tmp 移动到前子序列中的合适位置
        while (j > 0 && vec[j - 1] > tmp) {
            vec[j] = vec[j - 1];
            j -= 1;
        }

        vec[j] = tmp;
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