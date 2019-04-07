#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "methods.h"

using namespace std;
using namespace Eigen;

void test_transpose()
{
    vvect a;
    a << 1,2,3;
    cout << fixed;
    cout << "\n\n " << a;
    cout << "\n\n " << a.transpose();
}

void test_dot_product()
{
    vvect a, b;
    db prod;
    a << 1,1,1;
    b << 1,2,3;
    cout << fixed;
    cout << "\n\n " << a;
    cout << "\n\n " << b;
    prod = a.transpose() * b;
    cout << "\n\n " << prod;
}

void test_power_method()
{
    matr a;
    db max_abs, min_, min_abs;
    ///a << 1.2,0,0, 0,2,0, 0,0,1.5 ;
    init_matr(a);

    max_abs = find_eig_val_max_abs_powermethod(a);

    /**
    matr a0, E;
    db c = 1;
    init_identity(E);
    a0 = c * E + a;
    min_ = find_eigen_val_min(a0) - c;
    //**/
    min_ = find_eigen_val_min(a);

    min_abs = find_eigen_val_min_abs(a);

    //**
    cout << fixed;
    cout << "\n\n" << a;
    cout << "\n\n max_abs " << max_abs;
    cout << "\n\n min     " << min_;
    cout << "\n\n min_abs " << min_abs;
    cout << '\n' << endl;
    //**/
}

void test_jacobi_method()
{
    matr a, diag_approx;
    diag_approx = matr::Zero(n,n);
    ///a << 1,1,1, 1,2,0, 1,0,1.5 ;
    init_matr(a);
    Jacobi_rotation_method(a, diag_approx);
    //cout << std::scientific;
    cout << std::fixed;
    cout << "\n\n" << a;
    cout << std::scientific;
    cout << "\n\n" << diag_approx;
    cout << "\n\n";
    cout << std::fixed;
    for (int i = 0; i < n; ++i)
    {
        cout << "\n l" << i+1 << " " << diag_approx(i,i);
    }
    cout << "\n\n" << endl;
}

#endif // TESTS_H_INCLUDED
