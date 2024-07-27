#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
void Solution(std::vector<Type> &vec, int left, int right) {
    std::vector<Type> tmp = vec;
    // 返回条件
    if (left >= right) {
        return;
    }

    int mid = (right - left) / 2 + left;
    int start1 = left;
    int end1 = mid;
    int start2 = mid + 1;
    int end2 = right;

    // 注意此处是tmp，非vec
    Solution(tmp, start1, end1);
    Solution(tmp, start2, end2);

    int index = left;
    while (start1 <= end1 && start2 <= end2) {
        vec[index++] = tmp[start1] < tmp[start2]
                       ? tmp[start1++] : tmp[start2++];
    }
    while (start1 <= end1) {
        vec[index++] = tmp[start1++];
    }
    while (start2 <= end2) {
        vec[index++] = tmp[start2++];
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};
    Solution(vec, 0, vec.size() - 1);
    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}