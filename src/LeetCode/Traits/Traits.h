//
// Created by fx50j on 2023/7/6.
//

#ifndef GEODESICDISTANCE_TRAITS_H
#define GEODESICDISTANCE_TRAITS_H

#include <iostream>

// 定义数据 type 类
enum Type {
    TYPE_1,
    TYPE_2,
    TYPE_3
};

// 自定义数据类型
class Foo {
public:
    static const Type type = TYPE_1;
};

class Bar {
public:
    static const Type type = TYPE_2;
};

template<typename T>
struct type_traits {
    static const Type type = T::type;
};

// 内置数据类型
template<>
struct type_traits<int> {
    static const Type type = Type::TYPE_1;
};

template<>
struct type_traits<double> {
    static const Type type = Type::TYPE_2;
};

// 统一的编码函数
template<typename T>
void decode(const T &data) {
    if (type_traits<T>::type == Type::TYPE_1) {
        std::cout << "TYPE_1" << std::endl;
    } else if (type_traits<T>::type == Type::TYPE_2) {
        std::cout << "TYPE_2" << std::endl;
    }
}


#endif //GEODESICDISTANCE_TRAITS_H
