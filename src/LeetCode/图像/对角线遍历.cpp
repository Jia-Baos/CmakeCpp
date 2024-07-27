#include <bits/stdc++.h>

template<typename Type>
int Solution(const std::vector<std::vector<Type>> &vec) {
    std::vector<Type> tmp(vec.size() * vec[0].size(), 0);

    int x = 0;
    int y = 0;
    for (size_t i = 0; i < tmp.size(); ++i) {
        tmp[i] = vec[x][y];
        if (0 == (x + y) % 2) {
            if (vec[0].size() - 1 == y) {
                x += 1;
            } else if (x == 0) {
                y += 1;
            } else {
                x -= 1;
                y += 1;
            }

        } else {
            if (vec.size() - 1 == x) {
                y += 1;
            } else if (0 == y) {
                x += 1;
            } else {
                x += 1;
                y -= 1;
            }
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
    std::vector<std::vector<int>> vec{{1,  2,  3,  4},
                                      {5,  6,  7,  8},
                                      {9,  10, 11, 12},
                                      {13, 14, 15, 16}};
    int val = Solution(vec);
    std::cout << "return val: " << val << std::endl;
}