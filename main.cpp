#include <QApplication>
#include "mainwindow.h"
#include "complex.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Complex z1(2, 3);
    Complex z2(4, 5);

    Complex sum = z1 + z2;
    Complex product = z1 * z2;

    std::cout << "sum: "
              << sum.re << " + "
              << sum.im << "i" << std::endl;

    std::cout << "product: "
              << product.re << " + "
              << product.im << "i" << std::endl;

    std::cout << "abs: "
              << z1.abs() << std::endl;

    MainWindow w;
    w.show();

    return a.exec();
}