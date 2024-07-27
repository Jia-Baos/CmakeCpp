//
// Created by fx50j on 2023/9/2.
//
// 100 120
// 300 380
// no
// 370 371
#include <bits/stdc++.h>

int main() {
    int m{}, n{};
    while (std::cin >> m >> n) {
        int flag = 0;
        for (size_t i = m; i <= n; ++i) {
            int a = i / 100;
            int b = (i % 100) / 10;
            int c = i % 10;

            if (std::pow(a, 3) + std::pow(b, 3) + std::pow(c, 3) == i
                && flag == 0) {
                std::cout << i;
                flag++;
            } else if (std::pow(a, 3) + std::pow(b, 3) + std::pow(c, 3) == i
                       && flag ==1) {
                std::cout << " " << i;
            }
        }
        if (flag != 0) { std::cout << std::endl; }
        if (flag == 0) { std::cout << "no" << std::endl; }
    }
}