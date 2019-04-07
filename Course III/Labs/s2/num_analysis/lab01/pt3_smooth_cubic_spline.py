import scipy.integrate as integr
import matplotlib.pyplot as plt
import numpy as np
import math
import constnts as c
import time as t

######################################################################################################################

#####         PART III
##### (smoothing spline approximation)

n0 = 10
rho = 1

def f(x):
    return c.f(x)
    # return 1 - 2**p * abs(x)**2.4

def spline(n=n0, a0=c.left_edge, b0=c.right_edge, rho0=rho):
    t1 = t.time()

    x = np.empty([n + 1])
    h = np.empty(n)
    h0 = (b0-a0)/n
    for i in range(n+1):
        x[i] = a0 + i * h0
        if i > 0:
            h[i-1] = x[i] - x[i-1]
    a = np.zeros([n+1, n+1])
    b = np.zeros(n+1)
    ro = rho0 * np.ones(n+1)
    ro_inv = np.ones(n+1) * 1 / rho0
    R = np.diag(ro)
    R_inv = np.diag(ro_inv)
    H = np.zeros([n+1, n+1])
    y = np.array([f(x[i]) for i in range(n+1)])
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
            b[i] = (y[i+1] - y[i]) / h[i] - (y[i] - y[i-1]) / h[i-1]

    m = np.linalg.solve(a + np.matmul(H, np.matmul(R_inv, H.transpose())), b)
    f_u = y - np.matmul(R_inv, np.matmul(H.transpose(), m))


    def f_sol(x0):
        for i in range(1, n + 1):
            if x[i] >= x0 >= x[i - 1]:
                return m[i - 1] * ((x[i] - x0) ** 3) / (6 * h[i - 1]) + \
                       m[i] * ((x0 - x[i - 1]) ** 3) / (6 * h[i - 1]) + \
                       (f_u[i - 1] - m[i - 1] * (h[i - 1] ** 2) / 6) * (x[i] - x0) / h[i - 1] + \
                       (f_u[i] - m[i] * (h[i - 1] ** 2) / 6) * (x0 - x[i - 1]) / h[i - 1]

    t1 = t.time() - t1
    print(t1, " seconds (spline 1)")

    x1 = np.arange(a0, b0, c.plot_step)
    pol = []
    for i in x1:
        pol.append(f_sol(i))
    plt.figure(figsize=(14, 9))
    plt.plot(x1, pol, 'r--', label='Approximation polynomial')
    plt.plot(x1, f(x1), 'b-.', label='Real polynomial')
    plt.title("Spline interpolation")
    plt.legend()
    plt.show()

#######################################################################

def spline_wiki(n=n0, ro=rho):
    x = np.empty(n+1)
    h = np.empty(n+1)
    b0 = c.right_edge
    a0 = c.left_edge
    h[0] = (b0 - a0) / n
    x[0] = a0
    x[n] = b0
    for i in range(1,n+1):
        # x[i] = a0 + i * h0
        x[i] = (i * b0 + (n-i) * a0) / n
        h[i] = x[i] - x[i - 1]
    y = np.array([f(x[i]) for i in range(n + 1)])

    A = np.zeros([n-1,n-1])
    A[0][0] = (h[1]+h[2])/3
    for i in range(1,n-1):
        A[i][i-1] = h[i+1]/6
        A[i][i] = (h[i+2] + h[i+1])/3
        A[i - 1][i] = h[i+1]/6

    H = np.zeros([n-1,n+1])
    I = np.diag(np.ones(n+1))
    for i in range(1,n):
        H[i-1][i-1] = 1/h[i]
        H[i - 1][i] = - (1 / h[i] + 1/h[i+1])
        H[i - 1][i + 1] = 1 / h[i+1]

    W = np.matmul(np.matmul(H.transpose(), np.linalg.inv(A)), H)
    m0 = np.linalg.solve(I + ro * W, y.transpose())
    m = np.linalg.solve(A, np.matmul(H, m0))
    m = np.concatenate((np.array([0]), m, np.array([0])))

    def f_sol(x0):
        i = 0
        while (x[i+1] <= x0):
            i = i + 1
        return m0[i] * ((x[i+1] - x0) ** 3) / (6 * h[i]) + \
               m0[i+1] * ((x0 - x[i]) ** 3) / (6 * h[i]) + \
               (m[i] - m0[i] * (h[i] ** 2) / 6) * (x[i+1] - x0) / h[i] + \
               (m[i+1] - m0[i+1] * (h[i] ** 2) / 6) * (x0 - x[i]) / h[i]

    x1 = np.arange(a0, b0, c.plot_step)
    pol = []
    for i in x1:
        pol.append(-f_sol(i))
    plt.plot(x1, pol, 'r--', label='Approximation polynomial')
    plt.plot(x1, f(x1), 'b-.', label='Real polynomial')
    plt.title("Spline interpolation")
    plt.legend()
    plt.show()

####################################################################

def spline2(n=n0, ro=rho):
    t1 = t.time()

    x = np.empty(n+1)
    h = np.empty(n+1)
    b0 = c.right_edge
    a0 = c.left_edge
    h[0] = (b0 - a0) / n
    x[0] = a0
    x[n] = b0
    for i in range(1,n+1):
        # x[i] = a0 + i * h0
        x[i] = (i * b0 + (n-i) * a0) / n
        h[i] = x[i] - x[i - 1]
    y = np.array([f(x[i]) for i in range(n + 1)])

    A = np.zeros([n-1,n-1])
    A[0][0] = (h[1]+h[2])/3
    for i in range(1,n-1):
        A[i][i-1] = h[i+1]/6
        A[i][i] = (h[i+2] + h[i+1])/3
        A[i - 1][i] = h[i+1]/6

    H = np.zeros([n-1,n+1])
    I = np.diag(np.ones(n+1))
    for i in range(1,n):
        H[i-1][i-1] = 1/h[i]
        H[i - 1][i] = - (1 / h[i] + 1/h[i+1])
        H[i - 1][i + 1] = 1 / h[i+1]

    R_inv = np.diag(np.array([(i-i+1/ro) for i in range(n+1)]))
    m0 = np.linalg.solve(A + np.matmul(np.matmul(H, R_inv), H.transpose()), np.matmul(H, y.transpose()))
    m = y.transpose() - np.matmul(np.matmul(R_inv, H.transpose()), m0)

    m0 = np.concatenate((np.array([0]), m0, np.array([0])))

    def f_sol(x0):
        for i in range(1,n+1):
            if x[i-1] <= x0 <= x[i]:
                return m0[i-1] * ((x[i] - x0) ** 3) / (6 * h[i]) + \
                    m0[i] * ((x0 - x[i - 1]) ** 3) / (6 * h[i]) + \
                    (m[i - 1] - m0[i-1] * (h[i] ** 2) / 6) * (x[i] - x0) / h[i] + \
                    (m[i] - m0[i] * (h[i] ** 2) / 6) * (x0 - x[i - 1]) / h[i]

    t1 = t.time() - t1
    print(t1, " seconds (spline 2)")

    x1 = np.arange(a0, b0, c.plot_step)
    pol = []
    for i in x1:
        pol.append(f_sol(i))
    plt.figure(figsize=(14,9))
    plt.plot(x1, pol, 'r--', label='Approximation polynomial')
    plt.plot(x1, f(x1), 'b-.', label='Real polynomial')
    plt.title("Spline interpolation")
    plt.legend()
    plt.show()
