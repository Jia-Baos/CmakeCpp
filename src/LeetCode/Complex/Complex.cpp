//
// Created by fx50j on 2023/8/17.
//

#include "Complex.hpp"

std::ostream &operator<<(std::ostream &os, const complex &x)
{
    return os << '(' << real(x) << ',' << imag(x) << ')';
}

void complex_test()
{
    complex c1(2, 1);
    complex c2(4, 0);

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;

    std::cout << c1 + c2 << std::endl;
    std::cout << c1 - c2 << std::endl;
    std::cout << c1 * c2 << std::endl;
    std::cout << c1 / 2 << std::endl;

    std::cout << conj(c1) << std::endl;
    std::cout << norm(c1) << std::endl;
    std::cout << polar(10, 4) << std::endl;

    std::cout << (c1 += c2) << std::endl;

    std::cout << (c1 == c2) << std::endl;
    std::cout << (c1 != c2) << std::endl;
    std::cout << +c2 << std::endl;
    std::cout << -c2 << std::endl;

    std::cout << (c2 - 2) << std::endl;
    std::cout << (5 + c2) << std::endl;
}
