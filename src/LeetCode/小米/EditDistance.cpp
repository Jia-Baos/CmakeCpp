//
// Created by fx50j on 2023/9/3.
//
#include <bits/stdc++.h>

/// 编辑距离递归实现
/// \param str_a 序列1
/// \param str_b 序列2
/// \param i 序列1子序列的长度
/// \param j 序列2子序列的长度
/// \return 最小编辑长度
int EditDistance1(std::string &str_a, std::string &str_b,
                  int i, int j) {
    if (j == 0) {
        return i;
    } else if (i == 0) {
        return j;
        // 算法中 a, b 字符串下标从 1 开始，c 语言从 0 开始，所以 -1
    } else if (str_a[i - 1] == str_b[j - 1]) {
        return EditDistance1(str_a, str_b, i - 1, j - 1);
    } else {
        return std::min(
                {EditDistance1(str_a, str_b, i - 1, j) + 1,
                 EditDistance1(str_a, str_b, i, j - 1) + 1,
                 EditDistance1(str_a, str_b, i - 1, j - 1) + 1});
    }
}

/// 编辑距离动态规划实现
/// \param str_a 序列1
/// \param str_b 序列2
/// \return 最小编辑距离
int EditDistance2(const std::string &str_a, const std::string &str_b) {
    const int size_a = str_a.size() + 1;
    const int size_b = str_b.size() + 1;

    std::vector<std::vector<int>> vec{};
    std::vector<int> tmp(size_b);
    vec.resize(size_a, tmp);

    // 初始化边缘区域编辑长度
    for (size_t i = 0; i < size_a; ++i) {
        vec[i][0] = i;
    }
    for (size_t j = 0; j < size_b; ++j) {
        vec[0][j] = j;
    }

    // 动态规划计算编辑长度
    for (size_t i = 1; i < size_a; ++i) {
        for (size_t j = 1; j < size_b; ++j) {
            if (str_a[i - 1] == str_b[i - 1]) {
                vec[i][j] = vec[i - 1][j - 1];
            } else {
                vec[i][j] = std::min(
                        {vec[i - 1][j] + 1,
                         vec[i][j - 1] + 1,
                         vec[i - 1][j - 1] + 1});
            }
        }
    }
    return vec[size_a - 1][size_b - 1];
}

/// 编辑距离积分图实现
/// \param str_a 序列1
/// \param str_b 序列2
/// \return 最小编辑距离
int EditDistance3(const std::string &str_a, const std::string &str_b) {
    const int size_a = str_a.size() + 1;
    const int size_b = str_b.size() + 1;

    std::vector<int> vec(size_b);
    // 初始化边缘区域的编辑距离
    for (size_t j = 0; j < size_b; ++j) {
        vec[j] = j;
    }

    // 积分图计算编辑距离
    for (size_t i = 1; i < size_a; ++i) {
        int top_left = i - 1;
        vec[0] = i; // down_left
        for (size_t j = 1; j < size_b; ++j) {
            // 在被修改前保存值，作为下次的top_left
            int tmp = vec[j];   // top_right
            if (str_a[i - 1] == str_b[j - 1]) {
                vec[j] = top_left;  // down_right
            } else {
                vec[j] = std::min(
                        {vec[j] + 1, vec[j - 1] + 1, top_left + 1});
            }
            top_left = tmp;
        }
    }
    return vec.back();
}