//
// Created by fx50j on 2023/9/2.
//
// 81 4
// 2 2
//
#include <bits/stdc++.h>

int main() {
    double n = 0;
    int m = 0;
    while (std::cin >> n >> m) {
        double res = n;
        for (size_t j = 0; j < m - 1; ++j) {
            n = std::sqrt(n);
            res += n;
        }
        std::cout << std::fixed << std::setprecision(2) << res << std::endl;
    }
    return 0;
}