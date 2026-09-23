#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
    double re;
    double im;
    Complex(double r = 0, double i = 0);
    Complex operator+(const Complex& other) const;
    Complex operator*(const Complex& other) const;
    double abs() const;
};

#endif // COMPLEX_H
