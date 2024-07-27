#include <bits/stdc++.h>

template<typename Type>
int Solution(const std::vector<std::vector<Type>> &vec) {
    std::vector<Type> tmp{};

    int top = 0;
    int bottom = vec.size() - 1;
    int left = 0;
    int right = vec[0].size() - 1;

    while (true) {
        for (size_t i = left; i <= right; ++i) {
            tmp.push_back(vec[top][i]);
        }
        top += 1;
        if (top > bottom) {
            break;
        }

        for (size_t i = top; i <= bottom; ++i) {
            tmp.push_back(vec[i][right]);
        }
        right -= 1;
        if (left > right) {
            break;
        }

        for (int i = right; i >= left; --i) {
            tmp.push_back(vec[bottom][i]);
        }
        bottom -= 1;
        if (top > bottom) {
            break;
        }

        for (int i = bottom; i >= top; --i) {
            tmp.push_back(vec[i][left]);
        }
        left += 1;
        if (left > right) {
            break;
        }

    }

    for (auto iter: tmp) {
        std::cout << iter << " ";
    }

    return 0;
}

int main() {
//    std::vector<std::vector<int>> vec{{1, 2, 3},
//                                      {4, 5, 6},
//                                      {7, 8, 9}};
    std::vector<std::vector<int>> vec{{1, 2,  3,  4},
                                      {5, 6,  7,  8},
                                      {9, 10, 11, 12}};
    int val = Solution(vec);
    std::cout << "return val: " << val << std::endl;
}