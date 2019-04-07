#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED

#include "methods.h"


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void test_eigen_core()
{
     matr k = matr::Ones(3,3);
    cout << "\n\n" << k << endl;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            k(i,j) = 2*i + j;
        }
    }
    cout << "\n\n" << k << endl;
    //cout << "\n\n" << k.row(2) << endl;
    //cout << "\n\n" << k.col(1) << endl;
}


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void test_print()
{
    Matrix<db,1,matr_size> m;
    for (int j = 0; j < matr_size; ++j)
        {
            m(0,j) = 1.0/(7*j+1);
        }
    cout << "\n\n" << m << endl;
}


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void test_gauss_steps()
{
    matr a0, a1, a2;
    a1 << 1,0,3, 5,4,6, 7,8,9;
    a2 << 1,0,0, 0,3,0, 0,0,5;
    a0 = a1;
    vect b, b0, sol;
    b << 1,2,3;
    b0 = b;
    sol << 0,0,0;
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << a2 << endl;
    cout << "\n\n" << b << endl;
    cout << "\n\n" << sol << endl;

    Gauss_direct_step_V(a1,0,b);
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << b << endl;

    Gauss_direct_step_V(a1,1,b);
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << b << endl;

    Gauss_direct_step_V(a1,2,b);
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << b << endl;

    Gauss_bckwrd_step_V(a1,b,sol);
    vect eps = a0*sol - b0;
    cout << "\n\n" << eps << endl;

    cout << endl;
}


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void test_G_dir_step_arg_pass()
{
    matr a1, a2, arg;
    a1 << (Matrix<db,n,n>() << 1,2,3,4,5,6,7,8,9).finished();
    a2 = a1;
    //arg << 1,1,1,2,2,2,3,3,3;
    init_ident(E);
    arg = E;
    vect b;
    b << 1,2,3;
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << arg << endl;
    cout << "\n\n" << b << endl;
    //**
    Gauss_direct_step_M(a1,1,arg);
    Gauss_direct_step_V(a2,1,b);
    cout << "\n\n" << a1 << endl;
    cout << "\n\n" << a2 << endl;
    cout << "\n\n" << arg << endl;
    cout << "\n\n" << b << endl;
    //**/
}


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int gauss (vector < vector<double> > a, vector<double> & ans) {
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	int INF = INT_MAX;
	db EPS = 1000;

	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i)
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		if (abs (a[sel][col]) < EPS)
			continue;
		for (int i=col; i<=m; ++i)
			swap (a[sel][i], a[row][i]);
		where[col] = row;

		for (int i=0; i<n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > EPS)
			return 0;
	}

	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}


///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void test_emax()
{
    matr a_m, am0;
    a_m << 1,0,1, 1,1,0, 1,1,1;
    ///a_m << 1,0,0, 0,3,0, 0,0,5;
    vect b_m, bm0, sol, eps;
    b_m << 10,11,12;
    am0 = a_m;
    bm0 = b_m;
    cout << "\n\n" << a_m << endl;
    cout << "\n\n" << b_m << endl;
    Gauss_solve(a_m,b_m,sol);
    cout << std::fixed;
    cout << "\n\n" << sol << endl;
    eps = -bm0;
    cout << "\n\n" << eps << endl;
    eps += am0 * sol;
    cout << "\n\n" << eps << endl;


    vector<vector<db>> a_v, av0;
    a_v = {{1,0,1,10},{1,1,0,11},{1,1,1,12}};
    ///a_v = {{1,0,0,10},{0,3,0,11},{0,0,5,12}};
    //vector<db> b_v = {10,11,12};
    av0 = a_v;
    vector<db> sol_v, epsv;
    sol_v.resize(n);
    epsv.resize(n);
    cout << "\n\n";
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            cout << " " << a_v[i][j];
        }
        cout << endl;
    }
    cout << "\n\n";

    if (gauss(a_v,sol_v) != 0)
    for (int i = 0; i < n; ++i)
    {
        cout << " " << sol_v[i];
    }
    cout << endl;

    for (int i = 0; i < n; ++i)
    {
        epsv[i] = -av0[i][n];
    }
    cout << endl;

    cout << "\n\n";
    for (int i = 0; i < n; ++i)
    {
        cout << " " << epsv[i];
    }
    cout << endl;

    for (int i = 0; i < n; ++i)
    {
        //epsv[i] = -av0[i][n];
        //epsv[i] = 0;
        for (int j = 0; j < n; ++j)
        {
            epsv[i] += sol_v[j]*av0[i][j];
        }
    }
    cout << endl;

    cout << "\n\n";
    for (int i = 0; i < n; ++i)
    {
        cout << " " << epsv[i];
    }
    cout << endl;

}
///<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
/// попытка посмотреть что будет с матрицей ярика (по похыбке)
void matr_init_Yarik(matr& m, vect& b)
{
    ///if (m.rows() != matr_size) return;
    vector<db> vals, x_i;
    vals.resize(0);
    for (int i = 1; i <= n; ++i)
    {
        vals.push_back(1.0 / (i*i));
        vals[i-1]++;
        x_i.push_back(vals[i-1]);
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            m(i,j) = 1 + x_i[i];
            x_i[i] *= vals[i];
        }
    }
    for (int i = 0; i < n; ++i){b(i,0) = n-i;}
}

void test_Yarik()
{
    matr a_y;
    vect b_y, ans_y;
    matr_init_Yarik(a_y,b_y);
    Gauss_solve(a_y, b_y, ans_y);
}
//**/

#endif // TESTS_H_INCLUDED
