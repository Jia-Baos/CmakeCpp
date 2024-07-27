//
// Created by fx50j on 2023/8/22.
//

#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
void Solution(const std::vector<Type> &vec,
              const int target) {

    int left = 0;
    int right = vec.size() - 1;

    while (left < right) {
        if (vec[left] + vec[right] == target) {
            std::cout << left << " " << right << std::endl;
            return;
        } else if (vec[left] + vec[right] < right) {
            left += 1;
        } else {
            right -= 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int target = 9;
    std::vector<int> vec = {2, 7, 11, 15};
    Solution(vec, target);
    return 0;
}