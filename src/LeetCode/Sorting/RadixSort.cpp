#include <bits/stdc++.h>

template<typename Type>
requires std::is_integral_v<Type>
int Solution(std::vector<Type> &vec) {
    int base = 10;
    int loop_times = 1;
    for (auto iter: vec) {
        while (iter > base) {
            loop_times += 1;
            base *= 10;
        }
    }

    base = 1;
    while (loop_times > 0) {
        std::vector<std::vector<Type>> buckets(10);
        for (size_t i = 0; i < vec.size(); ++i) {
            int index = (vec[i] / base) % 10;
            buckets[index].push_back(vec[i]);
        }

        int index = 0;
        for (size_t i = 0; i < 10; ++i) {
            for (size_t j = 0; j < buckets[i].size(); ++j) {
                vec[index++] = buckets[i][j];
            }
        }
        base *= 10;
        loop_times -= 1;
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