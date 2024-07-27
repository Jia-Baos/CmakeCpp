//
// Created by fx50j on 2023/8/22.
//

#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
void Solution(std::vector<Type> &vec1,
              std::vector<Type> &vec2) {
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    std::vector<Type> ans;
    int left1 = 0;
    int left2 = 0;

    while (left1 < vec1.size() && left2 < vec2.size()) {
        if (vec1[left1] == vec2[left2]) {
            if (std::find(ans.begin(), ans.end(), vec1[left1]) == ans.end()) {
                ans.push_back(vec1[left1]);
            }
            left1 += 1;
            left2 += 1;
        } else if (vec1[left1] < vec2[left2]) {
            left1 += 1;
        } else if (vec1[left1] > vec2[left2]) {
            left2 += 1;
        }
    }

    for (auto &iter: ans) {
        std::cout << iter << " ";
    }
}

int main() {
    std::vector<int> vec1 = {4, 9, 5};
    std::vector<int> vec2 = {9, 4, 9, 8, 4};
    Solution(vec1, vec2);
}