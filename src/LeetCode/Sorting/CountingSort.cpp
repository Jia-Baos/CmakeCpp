#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    Type max = *std::max_element(vec.begin(), vec.end());
    std::vector<Type> count(max + 1, 0);

    for (auto iter: vec) {
        count[iter] += 1;
    }

    int index = 0;
    // 遍历计数容器
    for (size_t i = 0; i < count.size(); ++i) {
        while (count[i] > 0) {
            vec[index++] = i;
            count[i] -= 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};

    int val = Solution(vec);
    std::cout << "return value: " << val << std::endl;

    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}