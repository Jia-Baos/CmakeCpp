#include <bits/stdc++.h>

template<typename Type>
int Solution(const std::vector<std::vector<Type>> &vec) {
    int width = vec.size();
    std::vector<std::vector<Type>> tmp = vec;

    for (size_t i = 0; i < vec.size() / 2; ++i) {
        for (size_t j = i; j < vec[0].size() - i - 1; ++j) {
            Type val = tmp[i][j];
            tmp[i][j] = vec[vec.size() - 1 - j][i];
            tmp[vec.size() - 1 - j][i] = vec[vec.size() - 1 - i][vec.size() - 1 - j];
            tmp[vec.size() - 1 - i][vec.size() - 1 - j] = vec[j][vec.size() - 1 - i];
            tmp[j][vec.size() - 1 - i] = val;
        }
    }

    for (auto iter: tmp) {
        for (auto iter1: iter) {
            std::cout << iter1 << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

int main() {
    //    std::vector<std::vector<int>> vec{{1, 2, 3},
//                                      {4, 5, 6},
//                                      {7, 8, 9}};
    std::vector<std::vector<int>> vec{{1,  2,  3,  4},
                                      {5,  6,  7,  8},
                                      {9,  10, 11, 12},
                                      {13, 14, 15, 16}};
    int val = Solution(vec);
    std::cout << "return val: " << val << std::endl;
}