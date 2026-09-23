#include "complex.h"
#include <cmath>

Complex::Complex(double r, double i)
{
    re = r;
    im = i;
}

Complex Complex::operator+(const Complex& other) const
{
    return Complex(re + other.re,
                   im + other.im);
}

Complex Complex::operator*(const Complex& other) const
{
    return Complex(
        re * other.re - im * other.im,
        re * other.im + im * other.re);
}

double Complex::abs() const
{
    return sqrt(re * re + im * im);
}