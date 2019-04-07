#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

#include "Dense"
#include "Eigen"
#include "Core"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace Eigen;


const int matr_size = 10;

#define db double
#define n matr_size
#define matr Eigen::Matrix<db,n,n>
#define vect Eigen::Matrix<db,n,1>

db det_A = 1, cond_A = 0, det_A_exact = 1;
int swaps = 0, precision = 8;
vect x, b;
matr A, E;
db eps = 1e-10;

void print_vect(const vector<db> v)
{
    int s = v.size();
    cout << "\n\n" << scientific;
    for (int i = 0; i < s; ++i)
    {
        cout << " " << v[i] << endl;
    }
}

/// FUNCTION FOR SETTING INITIAL VALUES OF OUR MATRIX
void matr_init(matr& m, vect& b)
{
    ///if (m.rows() != matr_size) return;
    vector<db> vals;
    vals.resize(0);
    vals.push_back(1);
    for (int i = 1; i < n; ++i){vals.push_back(1.0 / i);}
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            m(i,j) = vals[j];
        }
    }
    for (int i = 1; i < n; ++i)
    {
        m(i,i) += 1 + vals[i];
        det_A_exact *= (1+vals[i]);
    }
    for (int i = 0; i < n; ++i){b(i,0) = (1.0 / (n-i));}
}

void init_ident(matr& m)
{
    m = matr::Zero(n,n);
    for (int i = 0; i < n; ++i){m(i,i) = 1;}
}

/// ROW SWAPPING
void swap_rows(matr& m, int i, int j)
{
    //if (m.rows() != n || m.cols() != n) return;
    if (i < 0 || i >= n || j < 0 || j >= n || i == j) return;
    db tmp;
    for (int k = 0; k < n; k++)
    {
        tmp = m(i,k);
        m(i,k) = m(j,k);
        m(j,k) = tmp;
    }
}

/// COLUMN SWAPPING
void swap_cols(matr& m, int i, int j)
{
    //if (m.rows() != n || m.cols() != n) return;
    if (i < 0 || i >= n || j < 0 || j >= n || i == j) return;
    db tmp;
    for (int k = 0; k < n; k++)
    {
        tmp = m(k,i);
        m(k,i) = m(k,j);
        m(k,j) = tmp;
    }
}

int find_max_in_row(const matr m, int row_num, int col_range1, int col_range2)
{
    db maxx = m(row_num, col_range1);
    int i = row_num, pivot = col_range1;
    for (int j = col_range1 + 1; j < col_range2; ++j)
    {
        if (maxx < m(i,j)) {maxx = m(i,j); pivot = j;}
    }
    return pivot;
}

int find_max_in_col(const matr m, int col_num, int row_range1, int row_range2)
{
    db maxx = m(row_range1, col_num);
    int i = col_num, pivot = row_range1;
    for (int j = row_range1 + 1; j < row_range2; ++j)
    {
        if (maxx < m(j,i)) {maxx = m(j,i); pivot = j;}
    }
    return pivot;
}

void row_multiply(matr& m, int row_num, db coeff)
{
    int j = row_num;
    for (int i = 0 ; i < n; ++i)
    {
        m(j,i) *= coeff;
    }
}

void row_divide(matr& m, int row_num, db coeff)
{
    int j = row_num;
    for (int i = 0 ; i < n; ++i)
    {
        m(j,i) /= coeff;
    }
}

/// subtract row 2 multiplied by coefficient c from row 1
void row_coeff_subtr(matr& m, int row_num1, int row_num2, db coeff)
{
    int r1 = row_num1, r2 = row_num2;
    for (int i = 0; i < n; ++i)
    {
        m(r1,i) -= coeff * m(r2,i);
    }
}

///OUR NORM FINDS THE MAXIMUM ELEMENT OF MATRIX/VECTOR
db norm_M(const matr& m)
{
    db maxx = abs(m(0,0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if ( maxx < abs(m(i,j)) ) maxx = abs(m(i,j));
        }
    }
    return maxx;
}

db norm_V(const vect& v)
{
    db sum = 0;
    for (int j = 0; j < n; ++j)
    {
        sum += v(j,0) * v(j,0);
    }
    return sqrt(sum);
}

/**
void normalize_col(matr& m, int col_num)
{
    int i = col_num;
    row_divide(m,i,m(i,i));
    for (int j = i + 1; j < n; ++j)
    {
        row_coeff_subtr(m, j, i, m(i,j));
    }
}
**/

///DIRECT METHOD

void Gauss_direct_step_M(matr& m, int col_num, matr& b)
{
    if (b.rows() != n) return;
    int i = col_num;
    for (int k = 0; k < n; ++k)
    {
        b(i,k) /= m(i,i);
        for (int j = i+1; j < n; ++j)
        {
            b(j,k) -= b(i,k) * m(j,i);
        }
    }

    row_divide(m,i,m(i,i));
    for (int j = i + 1; j < n; ++j)
    {
        row_coeff_subtr(m, j, i, m(j,i));
    }
}

void Gauss_direct_step_V(matr& m, int col_num, vect& b)
{
    if (b.rows() != n) return;
    int i = col_num;
    for (int k = 0; k < 1; ++k)
    {
        b(i,k) /= m(i,i);
        for (int j = i+1; j < n; ++j)
        {
            b(j,k) -= b(i,k) * m(j,i);
        }
    }

    row_divide(m,i,m(i,i));
    for (int j = i + 1; j < n; ++j)
    {
        row_coeff_subtr(m, j, i, m(j,i));
    }
}

void Gauss_bckwrd_step_V(const matr& m, const vect& b, vect& sol)
{
    sol = Eigen::Matrix<db,n,1>::Zero(n,1);
    for (int i = 1; i <= n; ++i)
    {
        sol(n-i,0) = b(n-i,0);
        for (int j = 1; j < i; ++j)
        {
            sol(n-i,0) -= m(n-i,n-j) * sol(n-j,0);
        }
        ///sol(n-i,0) /= m(n-i,n-i);
        ///cout << sol << "\n\n"; ///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    }
}

void Gauss_bckwrd_step_M(const matr& m, const matr& b, matr& sol)
{
    sol = Eigen::Matrix<db,n,n>::Zero(n,n);
    for (int k = 0; k < n; ++k)
    {
        for (int i = 1; i <= n; ++i)
        {
            sol(n-i,k) = b(n-i,k);
            for (int j = 1; j < i; ++j)
            {
                sol(n-i,k) -= m(n-i,n-j) * sol(n-j,k);
            }
            ///sol(n-i,k) /= m(n-i,n-i);
        }
    }
}

/// ---------------------------------------------

/// BODY PROGRAMS (Part I - GAUSS)

void Gauss_solve(matr A, vect b, vect& sol)
{
    matr a; a = A;
    vect b0 = b;

    //**
    cout << std::setprecision(precision) << std::fixed << "\n\n" << A;
    cout << "\n\n" << b;
    //**/

    //**
    for (int i = 0; i < n; ++i)
    {
        int piv_row = find_max_in_col(a,i,i,n);
        det_A *= a(piv_row,i);
        if (piv_row > i)
        {
            swap_rows(a,i,piv_row);
            swaps++;
            det_A *= -1;
        }
        Gauss_direct_step_V(a,i,b);
    }

    Gauss_bckwrd_step_V(a,b,sol);

    //**
    vect epsilon = A * sol - b0;
    cout << std::fixed;
    cout << "\n\n" << A;
    cout << std::fixed;
    cout << "\n\n" << sol;
    cout << std::scientific;
    cout << "\n\n" << epsilon;
    cout << "\n\n error vector norm = " << norm_V(epsilon);
    cout << std::fixed;
    ///cout << "\n\n det(A) = " << det_A;
    cout << std::scientific;
    ///cout << "\n\n determinant error = " << det_A - det_A_exact;
    cout << endl;
    //**/
}

void inverse()
{
    matr_init(A,b);
    matr a, inv, e0; a = A;
    init_ident(E);
    e0 = E;
    inv = matr::Zero(n,n);

    for (int i = 0; i < n; ++i)
    {
        int piv_row = find_max_in_col(a,i,i,n);
        if (piv_row > i) swap_rows(a,i,piv_row);
        Gauss_direct_step_M(a,i,E);
    }

    Gauss_bckwrd_step_M(a,E,inv);

    matr approx_E = A * inv - e0;
    cout << std::fixed;
    cout << "\n\n" << inv;
    cout << std::scientific;
    cout << "\n\n" << approx_E;
    cout << "\n\n Norm of the error matrix " << norm_M(approx_E);
    cond_A = norm_M(A) * norm_M(inv);
    cout << std::fixed << "\n\n cond(A) = " << cond_A;
    cout << endl;
}

void part_I_everything()
{
    matr_init(A,b);
    Gauss_solve(A,b,x);
    ///inverse();
}

/// ---------------------------------------------


/// ITERATIVE METHOD

void iterateZ_step(const matr& m, const vect& b, vect& tmp, vect& nxt)
{
    for (int i = 0; i < n; ++i)
    {
        nxt(i,0) = b(i,0);
        for (int j = 0; j < i; ++j)
        {
            nxt(i,0) -= m(i,j) * nxt(j,0);
        }
        for (int j = i + 1; j < n; ++j)
        {
            nxt(i,0) -= m(i,j) * tmp(j,0);
        }
        nxt(i,0) /= m(i,i);
    }
}

/// BODY PROGRAMS (Part II - GAUSS)

void Zeydell_solve(vect x0)
{
    matr_init(A,b);
    ///vector<db> deltas; deltas.resize(0);
    db dlta = 1;
    int iter_num = 1;
    vect tmp = x0, nxt, delta, epsln;
    cout << "\n\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
    cout << "\n\n " << "iteration 0";
    cout << std::fixed << std::setprecision(10);
    cout << "\n\n" << tmp;

    while (dlta > eps)
    {
        iterateZ_step(A,b,tmp,nxt);
        delta = nxt - tmp;
        dlta = norm_V(delta);
        cout << "\n\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
        cout << "\n\n " << "iteration " << iter_num;
        cout << std::fixed << std::setprecision(10);
        cout << "\n\n" << nxt;
        cout << "\n\n" << A*tmp; /// to see how the target vector b is approached
        cout << std::scientific;
        cout << "\n\n" << delta;
        cout << "\n\n" << dlta;
        tmp = nxt;
        iter_num++;
        ///deltas.push_back(dlta);
    }
    cout << "\n\n <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "\n\n final result ";
    cout << std::fixed;
    cout << "\n\n" << tmp;
    cout << std::fixed;
    cout << "\n\n" << A*tmp;
    epsln = A * tmp - b;
    cout << std::scientific;
    cout << "\n\n" << epsln;
    cout << "\n\n" << norm_V(epsln);
    cout << endl;
}

void part_II()
{
    vect x0;
    x0 = vect::Ones(n,1);
    Zeydell_solve(x0);
}

#endif // METHODS_H_INCLUDED
