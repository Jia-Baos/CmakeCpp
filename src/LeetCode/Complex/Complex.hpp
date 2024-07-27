//
// Created by fx50j on 2023/8/17.
//

#ifndef LEETCODE_COMPLEX_HPP
#define LEETCODE_COMPLEX_HPP

#include <iostream>
#include <cmath>

class complex
{
public:
    complex(double r = 0, double i = 0)
        : re(r), im(i) {}

    double real() const { return re; }
    double imag() const { return im; }

    complex &operator+=(const complex &);
    complex &operator-=(const complex &);
    complex &operator*=(const complex &);
    complex &operator/=(const complex &);

    friend complex &__doapl(complex *ths, const complex &r);
    friend complex &__doami(complex *ths, const complex &r);
    friend complex &__doaml(complex *ths, const complex &r);

private:
    double re, im;
};

inline complex &__doapl(complex *ths, const complex &r)
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}

inline complex &
complex::operator+=(const complex &r)
{
    return __doapl(this, r);
}

inline complex &__doami(complex *ths, const complex &r)
{
    ths->re -= r.re;
    ths->im -= r.im;
    return *ths;
}

inline complex &
complex::operator-=(const complex &r)
{
    return __doami(this, r);
}

inline complex &
__doaml(complex *ths, const complex &r)
{
    double f = ths->re * r.re - ths->im * r.im;
    ths->im = ths->re * r.im + ths->im * r.re;
    ths->re = f;
    return *ths;
}

inline complex &
complex::operator*=(const complex &r)
{
    return __doaml(this, r);
}

inline double
imag(const complex &x)
{
    return x.imag();
}

inline double
real(const complex &x)
{
    return x.real();
}

inline complex
operator+(const complex &x, const complex &y)
{
    return complex(real(x) + real(y), imag(x) + imag(y));
}

inline complex
operator+(const complex &x, double y)
{
    return complex(real(x) + y, imag(x));
}

inline complex
operator+(double x, const complex &y)
{
    return complex(x + real(y), imag(y));
}

inline complex
operator-(const complex &x, const complex &y)
{
    return complex(real(x) - real(y), imag(x) - imag(y));
}

inline complex
operator-(const complex &x, double y)
{
    return complex(real(x) - y, imag(x));
}

inline complex
operator-(double x, const complex &y)
{
    return complex(x - real(y), -imag(y));
}

inline complex
operator*(const complex &x, const complex &y)
{
    return complex(real(x) * real(y) - imag(x) * imag(y),
                   real(x) * imag(y) + imag(x) * real(y));
}

inline complex
operator*(const complex &x, double y)
{
    return complex(real(x) * y, imag(x) * y);
}

inline complex
operator*(double x, const complex &y)
{
    return complex(x * real(y), x * imag(y));
}

inline complex
operator/(const complex &x, double y)
{
    return complex(real(x) / y, imag(x) / y);
}

inline complex
operator+(const complex &x)
{
    return x;
}

inline complex
operator-(const complex &x)
{
    return complex(-real(x), -imag(x));
}

inline bool
operator==(const complex &x, const complex &y)
{
    return real(x) == real(y) && imag(x) == imag(y);
}

inline bool
operator==(const complex &x, double y)
{
    return real(x) == y && imag(x) == 0;
}

inline bool
operator==(double x, const complex &y)
{
    return x == real(y) && imag(y) == 0;
}

inline bool
operator!=(const complex &x, const complex &y)
{
    return real(x) != real(y) || imag(x) != imag(y);
}

inline bool
operator!=(const complex &x, double y)
{
    return real(x) != y || imag(x) != 0;
}

inline bool
operator!=(double x, const complex &y)
{
    return x != real(y) || imag(y) != 0;
}

inline complex
polar(double r, double t)
{
    return complex(r * cos(t), r * sin(t));
}

inline complex
conj(const complex &x)
{
    return complex(real(x), -imag(x));
}

inline double
norm(const complex &x)
{
    return real(x) * real(x) + imag(x) * imag(x);
}

void complex_test();

#endif // LEETCODE_COMPLEX_HPP
