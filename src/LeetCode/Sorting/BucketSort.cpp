#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    Type max = *std::max_element(vec.begin(), vec.end());
    int bucket_size = (max / 10) + 1;
    std::vector<std::vector<Type>> buckets(bucket_size);

    for (const Type &iter: vec) {
        buckets[iter / 10].push_back(iter);
    }

    int index = 0;
    for (size_t i = 0; i < bucket_size; ++i) {
        std::sort(buckets[i].begin(), buckets[i].end());
        for (size_t j = 0; j < buckets[i].size(); ++j) {
            vec[index++] = buckets[i][j];
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    std::vector<int> vec = {6, 2, 3, 5, 1, 4};

    int val = Solution(vec);
    std::cout << "return value: " << val << std::endl;

    for (auto iter: vec) {
        std::cout << iter << " ";
    }
}