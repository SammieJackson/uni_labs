import scipy.integrate as integr
import matplotlib.pyplot as pplt
import numpy as np
import math as m
import constnts as c
import time as t


# тестик для интергрирования
def f0(x):
    return x

# result = integr.quad(lambda x: f0(x), 0, 2)
# print(result)


######################################################################################################################
# First task: best mean-squared approximation

n = 5
###################################


matr_with_prec = []   # the system matrix with each elements precision
matr = []   # the system matrix
col_with_prec = []    # the system vector with precision
col = []    # system vector
coefs = []  # coefficients of the approximating algo

# first system: phi_i = x^i, i from [0,n]

# build the linear system - find scalar products
def build_slar_powers(n):
    matr.clear()
    matr_with_prec.clear()
    col.clear()
    col_with_prec.clear()

    for i in range(n+1):
        curr_row = []
        for j in range(n+1):
            if (j >= i): curr_row.append(integr.quad(lambda x: c.binpow(x, i+j), c.left_edge, c.right_edge))
            else: curr_row.append(matr_with_prec[j][i])
        matr_with_prec.append(curr_row)
        col_with_prec.append(integr.quad(lambda x: ( c.f(x) * c.binpow(x, i) ), c.left_edge, c.right_edge))

    for row in matr_with_prec:
        row0 = []
        for x in row:
            tmp = x[0]
            row0.append(tmp)
        matr.append(row0)
    for x in col_with_prec:
        col.append(x[0])


# solve slar - find c_i - build approximating polinomial
def gauss(A,b):
  n = len(A)
  M = A

  i = 0
  for x in M:
   x.append(b[i])
   i += 1

  for k in range(n):
   for i in range(k,n):
     if abs(M[i][k]) > abs(M[k][k]):
        M[k], M[i] = M[i],M[k]
     else:
        pass

   for j in range(k+1,n):
       q = float(M[j][k]) / M[k][k]
       for m in range(k, n+1):
          M[j][m] -=  q * M[k][m]

  x = [0 for i in range(n)]

  x[n-1] =float(M[n-1][n])/M[n-1][n-1]
  for i in range (n-1,-1,-1):
    z = 0
    for j in range(i+1,n):
        z = z  + float(M[i][j])*x[j]
    x[i] = float(M[i][n] - z)/M[i][i]
  return x


def approx_func_powers(coeffs, x):
    res = 0
    tmp = 1
    s = len(coeffs)
    n0 = s
    # print('1111111111111111111111111111111', x)
    for i in range(n0):
        res += coeffs[i] * tmp
        tmp *= x
    return res

# plot first approximating function and the error
def my_plot_powers(coeffs):
    t = np.arange(c.left_edge, c.right_edge, c.plot_step)
    pplt.ylim(c.bot_edge, c.top_edge)
    pplt.plot(t, approx_func_powers(coeffs, t), t, c.f(t))
    # pplt.plot(t, c.f(t))
    pplt.show()

    pplt.ylim(c.mini_bot_edge, c.top_edge)
    pplt.plot(t, abs(approx_func_powers(coeffs, t)-c.f(t)))
    pplt.show()

def squared_err_powers(coefs, x):
    tmp = approx_func_powers(coefs, x) - c.f(x)
    res = tmp * tmp
    return res

def find_coefs_pow(n0=n, if_print=False):
    t1 = t.time()

    build_slar_powers(n0)
    '''
    if if_print:
        for row in matr_with_prec:
            print(row)
        print('\n', col_with_prec)
        # print(matr_with_prec[0][0][0])
    #'''

    a = np.matrix(matr)
    b = np.array(col)
    # print(a)
    # print(b)
    x = np.linalg.solve(a, b)
    if if_print:
        err = a.dot(x) - b
        print('\n', err)
        print('\n', x)

    t1 = t.time() - t1
    print('\n', t1, " seconds (pow)")
    return x

def main_pow():
    coefs = find_coefs_pow()
    my_plot_powers(coefs)
    eror = integr.quad(lambda x: squared_err_powers(coefs, x), c.left_edge, c.right_edge)
    print('\n Error^2 = ', eror)
    eror = m.sqrt(eror[0])
    print('\n |Error| = ', eror)


########################################################################################################################
# second system: phi_0 = 1, phi_(2i) = sin(ix), phi_(2i+1) = cos(ix), i from [0,n]

new_left_edge = -c.PI
new_right_edge = c.PI

def f_mod(x):
    tmp = x / c.PI
    return c.f(tmp)


def build_slar_trig(n):
    matr0 = []
    matr_with_prec0 = []
    col0 = []
    col_with_prec0 = []
    matr0.clear()
    matr_with_prec0.clear()
    col0.clear()
    col_with_prec0.clear()


    tmp_row0 = []
    # tmp_row.append(2 * PI)
    tmp_row0.append(integr.quad(lambda x: 1, new_left_edge, new_right_edge))
    for j in range(1, n+1):
        tmp_row0.append(integr.quad(lambda x: m.sin(j * x), new_left_edge, new_right_edge))
        # tmp_row.append(0)
        tmp_row0.append(integr.quad(lambda x: m.cos(j * x), new_left_edge, new_right_edge))
    # matr_with_prec0 += tmp_row
    matr_with_prec0.append(tmp_row0)
    col_with_prec0.append(integr.quad(lambda x: f_mod(x), new_left_edge, new_right_edge))
    for i in range(1, n+1):
        tmp_row_s = []
        tmp_row_s.append(integr.quad(lambda x: m.sin(i * x), new_left_edge, new_right_edge))
        for j in range(1, n+1):
            tmp_row_s.append(integr.quad(lambda x: m.sin(i * x) * m.sin(j * x), new_left_edge, new_right_edge))
            tmp_row_s.append(integr.quad(lambda x: m.sin(i * x) * m.cos(j * x), new_left_edge, new_right_edge))
        matr_with_prec0.append(tmp_row_s)
        tmp_row_c = []
        tmp_row_c.append(integr.quad(lambda x: m.cos(i * x), new_left_edge, new_right_edge))
        for j in range(1, n+1):
            tmp_row_c.append(integr.quad(lambda x: m.cos(i * x) * m.sin(j * x), new_left_edge, new_right_edge))
            tmp_row_c.append(integr.quad(lambda x: m.cos(i * x) * m.cos(j * x), new_left_edge, new_right_edge))
        matr_with_prec0.append(tmp_row_c)
        col_with_prec0.append(integr.quad(lambda x: (f_mod(x) * m.sin(i * x)), new_left_edge, new_right_edge))
        col_with_prec0.append(integr.quad(lambda x: (f_mod(x) * m.cos(i * x)), new_left_edge, new_right_edge))

    for row in matr_with_prec0:
        row0 = []
        for x in row:
            row0.append(x[0])
        matr0.append(row0)
    for x in col_with_prec0:
        col0.append(x[0])
    # print(matr_with_prec0)
    return matr_with_prec0, matr0, col_with_prec0, col0


def approx_func_trig(coeffs, x):
    tmp = x * c.PI
    s = len(coeffs)
    if s%2 == 0:
        return 0
    n0 = int((s-1)/2)
    # print('1111111111111111111', x)
    res = coeffs[0]
    for i in range(1, n0+1):
        # print(coeffs[2 * i - 1], coeffs[2 * i])
        # print(np.sin(i * tmp))
        res += np.sin(i * tmp) * coeffs[2 * i - 1]
        res += np.cos(i * tmp) * coeffs[2 * i]
    return res


# plot first approximating function and the error
def my_plot_trig(coeffs):
    t = np.arange(c.left_edge, c.right_edge, c.plot_step)
    pplt.ylim(c.bot_edge, c.top_edge)
    pplt.plot(t, approx_func_trig(coeffs, t), t, c.f(t))
    pplt.show()

    pplt.ylim(c.mini_bot_edge, c.mini_top_edge)
    pplt.plot(t, abs(approx_func_trig(coeffs, t)-c.f(t)))
    pplt.show()


def squared_err_trig(coeffs, x):
    tmp = approx_func_trig(coeffs, x) - c.f(x)
    res = tmp * tmp
    return res


def approx_func_trig_mod(coeffs, x):
    tmp = x
    s = len(coeffs)
    if s%2 == 0:
        return 0
    n0 = int((s-1)/2)
    # print('1111111111111111111', x)
    res = coeffs[0]
    for i in range(1, n0+1):
        # print(coeffs[2 * i - 1], coeffs[2 * i])
        # print(np.sin(i * tmp))
        res += np.sin(i * tmp) * coeffs[2 * i - 1]
        res += np.cos(i * tmp) * coeffs[2 * i]
    return res


def squared_err_trig_mod(coeffs, x):
    tmp = approx_func_trig_mod(coeffs, x) - f_mod(x)
    res = tmp * tmp
    return res

def find_coefs_trig(n0=n, if_print=False):
    t1 = t.time()

    matr_with_prec, matr, col_with_prec, col = build_slar_trig(n0)
    # print('\n', matr_with_prec)
    # print('\n', col_with_prec)
    # print('\n', matr)
    # print('\n', col)

    # print('\n',len(matr))
    # print('\n',len(matr[0]))
    a = np.matrix(matr)
    b = np.array(col)
    # print(a)
    # print('\n', b)
    x = np.linalg.solve(a, b)
    if if_print:
        print('\n', x)
        err = a.dot(x) - b
        print('\n', err)

    t1 = t.time() - t1
    print('\n', t1, " seconds (trig)")
    return x


def compute_orthogon_error(coefs):
    res = integr.quad(lambda x0: f_mod(x0)**2, new_left_edge, new_right_edge)
    sum = 2 * coefs[0]**2
    for i in range(1, len(coefs)):
        sum = sum + coefs[i]**2
    res = res[0] - sum * c.PI
    return res


def main_trig():
    coefs = find_coefs_trig()
    my_plot_trig(coefs)

    print('\n Error - integral - [-1, 1]')
    eror = integr.quad(lambda x0: squared_err_trig(coefs, x0), c.left_edge, c.right_edge)
    print('\n Error^2 = ', eror)
    eror = m.sqrt(eror[0])
    print('\n |Error| = ', eror)

    print('\n Error - integral - [-pi, pi]')
    eror = integr.quad(lambda x0: squared_err_trig_mod(coefs, x0), new_left_edge, new_right_edge)
    print('\n Error^2 = ', eror)
    eror = m.sqrt(eror[0])
    print('\n |Error| = ', eror)

    print('\n Error - sum - [-pi, pi]')
    eror = compute_orthogon_error(coefs)
    print('\n Error^2 = ', eror)
    eror = m.sqrt(eror)
    print('\n |Error| = ', eror)


def plot_both(m=n):
    pow_coefs = find_coefs_pow(2*m+1)
    trig_coefs = find_coefs_trig(m)
    t = np.arange(c.left_edge, c.right_edge, c.plot_step)
    # plotting P_n (x) (our polynom) and f(x)
    pplt.figure(figsize=(14, 9))
    pplt.ylim(c.bot_edge, c.top_edge)
    pplt.plot(t, approx_func_powers(pow_coefs, t), 'r-.', t, approx_func_trig(trig_coefs, t), 'g--', t, c.f(t), 'b-')
    pplt.show()

    pplt.figure(figsize=(14, 9))
    pplt.ylim(c.mini_bot_edge, c.mini_top_edge)
    pplt.plot(t, abs(approx_func_powers(pow_coefs, t) - c.f(t)), 'r-.', t, abs(approx_func_trig(trig_coefs, t) - c.f(t)), 'g--')
    pplt.show()