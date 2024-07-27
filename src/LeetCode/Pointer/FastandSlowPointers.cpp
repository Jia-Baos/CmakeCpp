//
// Created by fx50j on 2023/8/22.
//

#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    if (vec.size() <= 1) {
        return vec.size();
    }

    int slow = 0;
    int fast = 1;
    while (fast < vec.size()) {
        if (vec[slow] != vec[fast]) {
            slow += 1;
            vec[slow] = vec[fast];
        }
        fast += 1;
    }

    return slow + 1;
}

int main() {
    // 如果数组无序则先进行排序
    std::vector<int> vec = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    auto val = Solution(vec);
    std::cout << "return val: " << val << std::endl;
    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}