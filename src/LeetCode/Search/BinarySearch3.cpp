#include <bits/stdc++.h>

/// 二分查找直接法
/// \tparam Type 数据类型
/// \param vec 待查找的有序序列
/// \param target 查找的元素
/// \return 查找到则返回元素位置，未查找到则返回-1
template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec, const Type target) {
    int left = 0;
    int right = vec.size() - 1;
    while (left < right) {
        int mid = (left + right + 2 - 1) / 2;
        if (vec[mid] > target) {
            right= mid - 1;
        } else {
            left = mid;
        }
    }

    if (vec[left] == target) {
        return left;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    int target = 9;
    std::vector<int> vec = {-1, 0, 3, 5, 9, 12};

    int val = Solution(vec, target);
    std::cout << "return value: " << val << std::endl;
}