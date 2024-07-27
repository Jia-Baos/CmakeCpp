//
// Created by fx50j on 2023/9/2.
//
#include <bits/stdc++.h>

int main() {
    // int a[10];
    // int b[10];

    // int i{};
    // while (scanf("%d %d", &a[i], &b[i]) != EOF)
    // {
    //     std::cout << a[i] << " " << b[i] << std::endl;
    //     ++i;
    // }

    std::vector<std::vector<int>> vec{};
    std::string str;
    // while 判断的真实对象是std::cin
    // getline 读取时不读取 '\n'
    while (std::getline(std::cin, str)) {
        // 当多行文本输入完后，回车进入下一行
        // 此时std::cin未读到空格或回车，一直等待
        // 再输入空格则读入为空，触发break
        if (str == "") { break; }

        std::vector<int> tmp;
        int num;
        std::stringstream infile(str);
        while (infile >> num) {
            tmp.push_back(num);
        }
        vec.push_back(tmp);
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec[i].size(); ++j) {
            std::cout << vec[i][j] << " ";
        }
        std::cout << std::endl;
    }

}