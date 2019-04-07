#ifndef POW_H_INCLUDED
#define POW_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double epsilon = 0.0000000001,
                  x0 = -1.2,
                  x1 = -1.1,
                  x_simp = -1.15,
                 g_x = -0.056652706,
                 q_simp = 0.25;


const int iterations = 14;

/// function for exponentiation
///

double power(const double& x, int n)
{
    int res = 1;
	while (n) {
		if (n & 1)
			res *= x;
		x *= x;
		n >>= 1;
	}
	return res;


void test_power()
{
    cout << "\n X = ... " << endl;
    double x; cin >> x;
    x = power(x,11);
    cout << " New X = " << x;
}
///_____________________________________________


///     given function - X^7+X+4

double f(const double& x)
{
    return ( power(x,7) + x + 4 );
}

/// aposterior criterium

bool aposter_check(const double& x_prev, const double& x_curr, const double& q)
{
    return ( abs(x_curr - x_prev) <= ((1-q) * epsilon / q) );
}

///----------------------------------------------------
///  SIMPLE ITERATION
///----------------------------------------------------

///     chosen g(x) = -e^x -- guarantees values for the derivative of phi(x)

double g(const double& x)
{
    return ( -exp(x) / 5 );
}

///  changed function used within iterative method --  x = PHI(x) = x + g(x)*f(x)

double phi_iter(const double& x)
{
    return ( x + g(x) * f(x) );
}

///  iterating function

void run_simple_iter(double x_0, int max_iters, double precision)
{
    double tmp = x_0, nxt = 0, delta = 1.0, func;
    int cntr = 0;
    //cout << std::setprecision(10) << std::fixed << "k" << " |\t " << "X[k]" << " |\t " << "f(X[k])" << " |\t (" << "X[k] - X[k-1]" << ")";
    bool flag = false;
    while (cntr < max_iters) ///!flag && delta >= precision)
    {
        nxt = phi_iter(tmp);
        delta = abs(tmp - nxt);
        func = f(tmp);

        if (cntr < 10) cout << "0";
        cout << std::setprecision(10) << std::fixed << cntr << " |\t " << tmp << " |\t ";
        if (func > 0) cout << " ";
        cout << func << " |\t (" << delta << ")";

        flag = aposter_check(tmp, nxt, q_simp);
        if (flag) cout << " **";
        cout << endl;
        ///cout << boost::format("%2d | %3.7s | %3.7f | (%3.7f)\n") % cntr % tmp % func % delta;
        tmp = nxt;
        cntr++;
    }
    delta = abs(tmp-phi_iter(tmp));
    if (cntr < 10) cout << "0";
    cout << std::setprecision(10) << std::fixed << cntr << " |\t " << tmp << " |\t ";
    if (func > 0) cout << " ";
    cout << func << " |\t (" << delta << ")";

    flag = aposter_check(tmp, nxt, q_simp);
    if (flag) cout << " **";
    cout << endl;
}

/// body-function

void test_simp()
{
    run_simple_iter(x_simp,iterations,epsilon);
}

///----------------------------------------------------
///  RELAXATION
///----------------------------------------------------

///  changed function used within iterative method --  x = PHI(x) = x + g(x)*f(x)
/// here g(x) = const

double phi_relax(const double& x)
{
    return ( x + g_x * f(x) );
}

///  iterating function

void run_relax(double x_0, int max_iters, double precision)
{
    double tmp = x_0, nxt = 0, delta = 1.0, func;
    int cntr = 0;
    //cout << std::setprecision(10) << std::fixed << "k" << " |\t " << "X[k]" << " |\t " << "f(X[k])" << " |\t (" << "X[k] - X[k-1]" << ")";
    while (cntr < max_iters && delta >= precision)
    {
        nxt = phi_relax(tmp);
        delta = abs(tmp - nxt);
        func = f(tmp);

        cout << endl;
        if (cntr < 10) cout << "0";
        cout << std::setprecision(10) << std::fixed << cntr << " |\t " << tmp << " |\t ";
        if (func > 0) cout << " ";
        cout << func << " |\t (" << delta << ")";


        ///cout << boost::format("%2d | %3.7s | %3.7f | (%3.7f)\n") % cntr % tmp % func % delta;
        tmp = nxt;
        cntr++;
    }
    delta = abs(tmp - phi_relax(tmp));
    cout << endl;
    if (cntr < 10) cout << "0";
    cout << std::setprecision(10) << std::fixed << cntr << " |\t " << tmp << " |\t ";
    if (func > 0) cout << " ";
    cout << func << " |\t (" << delta << ")";
    //cout << " **" << endl;
}

/// body-function

void test_relax()
{
    run_relax(x0,iterations,epsilon);
}

///----------------------------------------------------
///  CHORDS
///----------------------------------------------------

// a, b - ������� �����, epsilon � ����������� �����������
double iter_(double a, double b) {
    while(fabs(b - a) > epsilon) {
        a = b - (b - a) * f(b) / (f(b) - f(a));
        b = a + (a - b) * f(a) / (f(a) - f(b));
    }
    // a, b � (i - 1)-� � i-� �����

    return b;
}

void run_cuts(double x_l,double x_r,double max_iters, double precision)
{
    double nxt, tmp = x_l, prev = x_r, func = 0, delta = 0, f_nxt;
    int cntr = 0;
    func = f(prev);
    //cout << std::setprecision(10) << std::fixed << "k" << " |\t " << "X[k]" << " |\t " << "f(X[k])" << " |\t (" << "X[k] - X[k-1]" << ")" << endl;
    if (cntr < 10) cout << "0";
    cout << std::setprecision(12) << std::fixed << cntr << " |\t " << prev << " |\t ";
    if (func > 0) cout << " ";
    cout << func << " |\t (" << delta << ")";
    cntr++;
    delta = abs(tmp - prev);
    f_nxt = f(tmp);
    while (cntr < max_iters && delta > precision && abs(f_nxt) > precision)
    {
        nxt = tmp - (tmp - prev) * f(tmp) / (f(tmp) - f(prev));
        delta = abs(tmp - nxt);
        func = f_nxt;

        cout << endl;
        if (cntr < 10) cout << "0";
        cout << std::setprecision(12) << std::fixed << cntr << " |\t " << tmp << " |\t ";
        if (func > 0) cout << " ";
        cout << func << " |\t (" << delta << ")";

        prev = tmp;
        tmp = nxt;
        f_nxt = f(tmp);
        cntr++;
    }

    nxt = tmp - (tmp - prev) * f(tmp) / (f(tmp) - f(prev));
    delta = abs(tmp - nxt);

    func = f_nxt;
    cout << endl;
    if (cntr < 10) cout << "0";
    cout << std::setprecision(12) << std::fixed << cntr << " |\t " << tmp << " |\t ";
    if (func > 0) cout << " ";
    cout << func << " |\t (" << delta << ")";
    ///cout << " **" << endl;
}

void test_cuts()
{
    run_cuts(x0,x1,iterations,epsilon);
}

#endif // POW_H_INCLUDED
