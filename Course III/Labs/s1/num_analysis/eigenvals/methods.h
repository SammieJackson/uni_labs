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

using db = double;
#define n matr_size
#define matr Eigen::Matrix<db,n,n>
#define vvect Eigen::Matrix<double,n,1> ///vertical vector
#define hvect Eigen::Matrix<double,1,n> ///horizontal vector

const vvect x_0 = vvect::Ones(n,1);
const db eps = 1e-16;

void init_matr (matr& m)
{
    ///if (m.rows() != matr_size) return;
    vector<db> vals;
    vals.resize(0);
    vals.push_back(1);
    for (int i = 1; i < n; ++i){vals.push_back(1.0 / i);}
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            m(j,i) = m(i,j) = vals[j];
        }
    }
    for (int i = 1; i < n; ++i)
    {
        m(i,i) = 1 + 2 * vals[i];
    }
}

/**
bool check_symmetry (const matr& A)
{

}
//**/

db norm_V_max (const vvect& v)
{
    db maxx = v(0,0);
    for (int i = 0; i < n; ++i)
    {
        if (maxx < v(i,0)) maxx = v(i,0);
    }
    return maxx;
}

db norm_V_sqr (const vvect& v)
{
    db sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += v(i,0) * v(i,0);
    }
    return sqrt(sum);
}

void normalize (vvect& v)
{
    db vnorm = norm_V_sqr(v);
    if (vnorm == 0) return;
    for (int i = 0; i < n; ++i)
    {
        v(i,0) /= vnorm;
    }
}

/// matrix non-diagonal elements evaluation
db non_diag_elem_eval (const matr& A)
{
    db res = 0;
    for(int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            res += A(i,j) * A (i,j);
            /// since the Jacobi rotative method is meant for symmetrical matrices, it is enough to evaluate only the elements above the diagonal
        }
    }
    ///res /= (n * (n-1) / 2); /// if we need an average value
    return res;
}

/// finds maximum non-diagonal element (since matrix is meant to be symmetrical, we search only above the diagonal)
db find_max_abs_above_diag (const matr& A, int& piv_row, int& piv_col)
{
    if (n == 1)
    {
        piv_row = 0;
        piv_col = 0;
        return 0;
    };
    int pivot_row = 0 , pivot_col = 1;
    db maxx = abs(A(1,0));
    for(int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if ( maxx < abs(A(i,j)) )
            {
                maxx = abs(A(i,j));
                pivot_row = i;
                pivot_col = j;
            }
            /// since the Jacobi rotative method is meant for symmetrical matrices, it is enough to evaluate only the elements above the diagonal
        }
    }
    ///res /= (n * (n-1) / 2); /// if we need an average value
    piv_row = pivot_row;
    piv_col = pivot_col;
    return maxx;
}

void init_identity (matr& A)
{
    A = matr::Zero(n,n);
    for (int i = 0; i < n; ++i)
    {
        A(i,i) += 1;
    }
}

void make_rotational_matr (matr& A, const int& row1, const int& row2, const db& sin_phi, const db& cos_phi)
{
    init_identity(A);
    int i = row1, j = row2;
    A(i,i) = cos_phi;
    A(i,j) = -sin_phi;
    A(j,i) = sin_phi;
    A(j,j) = cos_phi;
}

/// power-method (ratio of components of the vector), also possible through ratio of norms

db find_eig_val_max_abs_powermethod (const matr& A)
{
    int cntr = 0, i = 0;
    db m_tmp = 1, m_nxt, delta = eps + 1; /// ratios dot_product(x_(k+1),x_(k)) / norm(x_(k))
    vvect tmp = x_0, nxt; /// iterate
    normalize(tmp);
    nxt = A * tmp;
    ///m_nxt = nxt(i,0) / tmp(i,0);
    m_nxt = norm_V_sqr(nxt);
    while (delta > eps)
    {
        tmp = nxt;
        normalize(tmp);
        nxt = A * tmp;

        /// print next iteration

        m_tmp = m_nxt;
        ///m_nxt = nxt(i,0) / tmp(i,0);
        m_nxt = norm_V_sqr(nxt);
        delta = abs(m_nxt - m_tmp);
    }
    return m_nxt;
}

/// same with dot-products
//**
db find_eig_val_max_abs_productmethod (const matr& A)
{
    int cntr = 0;
    db m_tmp = 1, m_nxt, delta = eps + 1; /// ratios dot_product(x_(k+1),x_(k)) / norm(x_(k))
    vvect tmp = x_0, nxt; /// iterate
    normalize(tmp);
    nxt = A * tmp;
    m_nxt = nxt.transpose() * tmp;
    while (delta > eps)
    {
        tmp = nxt;
        normalize(tmp);
        nxt = A * tmp;

        /// print next iteration

        m_tmp = m_nxt;
        m_nxt = nxt.transpose() * tmp;
        delta = abs(m_nxt - m_tmp);
    }
    return m_nxt;
}
//**/

db find_eigen_val_min (const matr& A)
{
    db eig_max_A = find_eig_val_max_abs_powermethod(A);
    matr B;
    init_identity(B);
    B = eig_max_A * B - A;
    db eig_max_B = find_eig_val_max_abs_powermethod(B);
    db val_min_A = eig_max_A - eig_max_B;
    return val_min_A;
}

db find_eigen_val_min_abs (const matr& A)
{
    matr C;
    init_identity(C);
    db eig_max_A = find_eig_val_max_abs_powermethod(A);
    C = C - ( (A * A) / (eig_max_A * eig_max_A) );
    db eig_max_C = find_eig_val_max_abs_powermethod(C);
    ///if (eig_max_C < 1)
    db min_val_abs_A = (eig_max_A * eig_max_A) * (1 - eig_max_C);
    min_val_abs_A = sqrt(min_val_abs_A);
    return min_val_abs_A;
}

db Jacobi_rotation_method(const matr& A, matr& diag, int num = 1)
{
    if (num <= 0 || num > n) return 0;
    num--;
    int piv_row, piv_col;
    db sin_phi, cos_phi;
    matr tmp, U;
    tmp = A;
    db non_diag_val = non_diag_elem_eval(tmp);
    //cout << "\n\n " << non_diag_val << "\n\n";
    while (non_diag_val > eps)
    {
        find_max_abs_above_diag(tmp, piv_row, piv_col);
        int i = piv_row, j = piv_col;

        //**
        db tau, t , s, c;
        int sgn = 1;
        tau = (tmp(i,i) - tmp(j,j)) / (2 * tmp(i,j));
        if (tau < 0) sgn = -1;
        t = sgn / ( abs(tau) + sqrt(1 + tau * tau) );
        c = 1 / sqrt(1 + t * t);
        s = c * t;
        sin_phi = s;
        cos_phi = c;
        //**/
        /**
        db cos_two_phi = (tmp(i,i) - tmp(j,j)) / sqrt( 4 * tmp(i,j) * tmp(i,j) + (tmp(i,i) - tmp(j,j)) * (tmp(i,i) - tmp(j,j)) );
        if (tmp(i,i) == tmp(j,j)) cos_two_phi = 0;
        sin_phi = sqrt(0.5 * (1 - cos_two_phi));
        cos_phi = sqrt(0.5 * (1 + cos_two_phi));
        //if (tmp(i,j) * (tmp(i,i) - tmp(j,j)) < 0) sin_phi *= -1;
        //**/

        make_rotational_matr(U, piv_row, piv_col, -sin_phi, cos_phi);
            //cout << "\n\n" << U;
        tmp = U * tmp;
            //cout << "\n\n" << tmp;
        make_rotational_matr(U, piv_row, piv_col, sin_phi, cos_phi);
        tmp = tmp * U;

        non_diag_val = non_diag_elem_eval(tmp);

        /// print next iteration
        /**
        cout << std::fixed;
        cout << std::setprecision(9);
        cout << "\n\n" << tmp;
        cout << "\n\n" << non_diag_val;
        //cout << "\n\n" << (sin_phi * sin_phi + cos_phi * cos_phi);
        cout << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
        //**/

    }
    diag = tmp;
    return tmp(num,num);
}

#endif // METHODS_H_INCLUDED
