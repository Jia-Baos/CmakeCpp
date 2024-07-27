#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
void Solution(std::vector<Type> &vec,
              const int left, const int right) {
    if (left >= right) {
        return;
    }

    Type pivot = vec[left];
    int i = left;
    int j = right;
    while (i < j) {
        // 倒序第一个小于pivot的元素
        while (i < j && vec[j] >= pivot) {
            j--;
        }
        // 正序第一个大于pivot的元素
        while (i < j && vec[i] <= pivot) {
            i++;
        }
        std::swap(vec[i], vec[j]);
    }

    vec[left] = vec[i];
    vec[i] = pivot;

    Solution(vec, left, i - 1);
    Solution(vec, i + 1, right);

}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};
    Solution(vec, 0, vec.size() - 1);
    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}