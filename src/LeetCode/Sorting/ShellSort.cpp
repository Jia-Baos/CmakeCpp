#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    int gap = vec.size() / 2;
    while (gap > 0) {
        for (size_t i = gap; i < vec.size(); ++i) {
            Type tmp = vec[i];
            int j = i;
            while (j >= gap && vec[j - gap] > tmp) {
                vec[j] = vec[j - gap];
                j -= gap;
            }
            vec[j] = tmp;
        }
        gap /= 2;
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