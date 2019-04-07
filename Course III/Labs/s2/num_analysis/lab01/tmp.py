import numpy as np
import sys
from scipy import integrate
import matplotlib.pyplot as plt
from math import pi

p = 2.4


def f(x):
    return 1 - 2**p * abs(x)**p


def bin_pow(x, n):
    n = int(n)
    if x == 0:
        return 0
    if n == 0:
        return 1
    if n == 1:
        return x
    if n % 2 == 0:
        a = bin_pow(x, n//2)
        return a*a
    else:
        return x*bin_pow(x, n-1)


def cos_n(x, n):
    return np.cos(n * x)


def sin_n(x, n):
    return np.sin(n * x)


def scalar_product_integ(f1, f2, a, b):
    f0 = lambda x: f1(x) * f2(x)
    res, err = integrate.quad(f0, a, b)
    return res


def scalar_product_discrete(x, f1, f2):
    n = len(x)
    s = 0
    for i in range(n):
        s += f1(x[i]) * f2(x[i])
    return s/n


def root_mean_square_approxim_pol(n, a0, b0):
    b = np.empty([n+1])
    a = np.empty([n+1, n+1])

    for i in range(n+1):
        f0 = lambda x: bin_pow(x, i)
        b[i] = scalar_product_integ(f, f0, a0, b0)

    for i in range(n+1):
        fi = lambda x: bin_pow(x, i)
        for j in range(n+1):
            fj = lambda x: bin_pow(x, j)
            a[i][j] = scalar_product_integ(fj, fi, a0, b0)
    c = np.linalg.solve(a, b)

    def f_sol(x):
        s = 0
        x_pow = 1
        for k in range(n+1):
            s += c[k] * x_pow
            x_pow *= x
        return s

    error = scalar_product_integ(lambda x: f_sol(x) - f(x), lambda x: f_sol(x) - f(x), a0, b0)
    print("Root mean square approximation:")
    print("error", error)

    x = np.linspace(a0, b0, 100)
    plt.plot(x, f_sol(x), label='Approximation polynomial', linestyle='dashed')
    plt.plot(x, f(x), label='Real polynomial', linestyle='dotted')
    plt.xlabel('x label')
    plt.ylabel('y label')
    plt.title("Approximation by x^k")
    plt.legend()
    plt.show()
    return f_sol


def root_mean_square_approxim_trig(n, a0, b0):
    b_sin = np.empty([n])
    b_cos = np.empty([n+1])
    a_sin = np.empty([n, n])
    a_cos = np.empty([n+1, n+1])
    a = np.empty(n+1)
    for i in range(n+1):
        fcos = lambda x:cos_n(x, i)
        if i > 0:
            fsin = lambda x:sin_n(x, i)
        a[i] = scalar_product_integ(f, fcos, a0, b0)
        if i > 0:
            b_sin[i-1] = scalar_product_integ(f, fsin, a0, b0)
        b_cos[i] = scalar_product_integ(f, fcos, a0, b0)
    for i in range(n+1):
        fi_cos = lambda x: cos_n(x, i)
        if i > 0:
            fi_sin = lambda x: sin_n(x, i)
        for j in range(n+1):
            fj_cos = lambda x: cos_n(x, j)
            if i > 0:
                fj_sin = lambda x: sin_n(x, j)
            if i > 0 and j > 0:
                a_sin[i-1][j-1] = scalar_product_integ(fj_sin, fi_sin, a0, b0)
            a_cos[i][j] = scalar_product_integ(fj_cos, fi_cos, a0, b0)
    c_sin = np.linalg.solve(a_sin, b_sin)
    c_cos = np.linalg.solve(a_cos, b_cos)

    def f_sol(x):
        s = 0
        for k in range(n+1):
            if k == 0:
                s += c_cos[k]
            else:
                s += c_cos[k] * cos_n(x, k)
            if k > 0:
                s += c_sin[k-1] * sin_n(x, k)
        return s

    # common form of counting an error
    error = scalar_product_integ(lambda x: f_sol(x) - f(x), lambda x: f_sol(x) - f(x), a0, b0)
    print("Root mean square approximation:")
    print("error", error)

    # simple form of counting an error
    error = scalar_product_integ(f, f, a0, b0)
    for i in range(n+1):
        error -= c_cos[i]**2 * scalar_product_integ(lambda x: cos_n(x, i), lambda x: cos_n(x, i), a0, b0)
        if i > 0:
            error -= c_sin[i - 1] ** 2 * scalar_product_integ(lambda x: sin_n(x, i), lambda x: sin_n(x, i), a0, b0)
    print("Root mean square approximation simple form:")
    print("error", error)

    x = np.linspace(a0, b0, 100)
    plt.plot(x, f_sol(x), label='Approximation polynomial', linestyle='dashed')
    plt.plot(x, f(x), label='Real polynomial', linestyle='dotted')
    plt.xlabel('x label')
    plt.ylabel('y label')
    plt.title("Interpolation plot")
    plt.legend()
    plt.show()
    return f_sol


def root_mean_square_approxim_pol_discrete(n, a0, b0):
    x = np.empty([n+1])
    cost_func_prev = sys.maxsize
    cost_func_new = sys.maxsize - 1
    m = 0
    bo = True
    m0 = 0
    for i in range(n+1):
        x[i] = a0 + i * (b0 - a0)/n

    while m < n - 1:
        m += 1
        if cost_func_new >= cost_func_prev:
            bo = False
        if bo:
            m0 += 1

        b = np.empty([m + 1])
        a = np.empty([m + 1, m + 1])
        for i in range(m+1):
            f0 = lambda x: bin_pow(x, i)
            b[i] = scalar_product_discrete(x, f, f0)

        for i in range(m+1):
            fi = lambda x: bin_pow(x, i)
            for j in range(m+1):
                fj = lambda x: bin_pow(x, j)
                a[i][j] = scalar_product_discrete(x, fj, fi)
        c = np.linalg.solve(a, b)
        cost_func_prev = cost_func_new

        def f_sol(x):
            s = 0
            x_pow = 1
            for k in range(m + 1):
                s += c[k] * x_pow
                x_pow *= x
            return s

        diff = lambda x: f(x) - f_sol(x)
        cost_func_new = scalar_product_discrete(x, diff, diff) * n / (n - m)
        print(m, cost_func_new)

    # true value m
    m0 -= 1
    m = m0
    b = np.empty([m + 1])
    a = np.empty([m + 1, m + 1])
    for i in range(m + 1):
        f0 = lambda x: bin_pow(x, i)
        b[i] = scalar_product_discrete(x, f, f0)
    for i in range(m + 1):
        fi = lambda x: bin_pow(x, i)
        for j in range(m + 1):
            fj = lambda x: bin_pow(x, j)
            a[i][j] = scalar_product_discrete(x, fj, fi)
    c = np.linalg.solve(a, b)

    def f_sol(x):
        s = 0
        x_pow = 1
        for k in range(m + 1):
            s += c[k] * x_pow
            x_pow *= x
        return s
    diff = lambda x: f(x) - f_sol(x)
    cost_func_new = np.sqrt(scalar_product_discrete(x, diff, diff) * n / (n - m))
    print("Least squares")
    print(m, "error",  cost_func_new)

    x = np.linspace(a0, b0, 100)
    plt.plot(x, f_sol(x), label='Approximation polynomial', linestyle='dashed')
    plt.plot(x, f(x), label='Real polynomial', linestyle='dotted')
    plt.xlabel('x label')
    plt.ylabel('y label')
    plt.title("Interpolation plot")
    plt.legend()
    plt.show()
    return f_sol


def spline_interpolation(n, a0, b0):
    x = np.empty([n + 1])
    h = np.empty(n)
    for i in range(n+1):
        x[i] = a0 + i * (b0 - a0)/n
        if i > 0:
            h[i-1] = x[i] - x[i-1]
    a = np.zeros([n+1, n+1])
    b = np.zeros(n+1)
    ro = np.ones(n+1)
    R = np.diag(ro)
    H = np.zeros([n+1, n+1])
    for i in range(n+1):
        if i != 0 and i != n:
            H[i][i-1] = 1 / h[i-1]
            H[i][i] = -(1 / h[i-1] + 1 / h[i])
            H[i][i+1] = 1 / h[i]

    for i in range(n+1):
        if i == 0:
            a[i][i] = 1
        elif i == n:
            a[i][i] = 1
        else:
            a[i][i-1] = h[i-1] / 6
            a[i][i] = (h[i-1] + h[i]) / 3
            a[i][i+1] = h[i]/6
            b[i] = (f(x[i+1]) - f(x[i])) / h[i] - (f(x[i]) - f(x[i-1])) / h[i-1]

    m = np.linalg.solve(a + np.matmul(H, np.transpose(H)), b)
    f_u = np.array([f(x[i]) for i in range(n+1)]) - np.matmul(np.transpose(H), m)


    def f_sol(x0):
        for i in range(1, n+1):
            if x[i] >= x0 >= x[i-1]:
                return m[i-1] * ((x[i] - x0)**3) / (6 * h[i-1]) +\
                       m[i] * ((x0 - x[i-1])**3) / (6 * h[i-1]) +\
                       (f_u[i-1] - m[i-1] * (h[i-1]**2) / 6) * (x[i] - x0) / h[i-1] +\
                       (f_u[i] - m[i] * (h[i-1]**2) / 6) * (x0 - x[i-1]) / h[i-1]

    x1 = np.linspace(a0, b0, 100)
    y = []
    for i in x1:
        y.append(f_sol(i))
    plt.plot(x1, y, label='Approximation polynomial', linestyle='dashed')
    plt.plot(x1, f(x1), label='Real polynomial', linestyle='dotted')
    plt.xlabel('x label')
    plt.ylabel('y label')
    plt.title("Spline interpolation")
    plt.legend()
    plt.show()


a0, b0 = -pi, pi
#root_mean_square_approxim_pol(5, a0, b0)

#root_mean_square_approxim_trig(5, a0, b0)

#root_mean_square_approxim_pol_discrete(12, a0, b0)

spline_interpolation(15, a0, b0)
