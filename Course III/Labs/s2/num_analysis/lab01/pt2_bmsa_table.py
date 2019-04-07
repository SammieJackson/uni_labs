import scipy.integrate as integr
import matplotlib.pyplot as pplt
import numpy as np
from math import sqrt
import pt1_bmsa_pow_trig as pt1
import constnts as c
import time


#######################################################################################################################
# SECOND PART
# best mean-squared approximation of a table-defined function

N = 12      # number of nodes
min_d = 3   # current polinomial degree/power
max_d = 15  #
opt_d = 5   #


def create_node_matrix(xnodes, degree):
    matr = []
    for i in range(degree + 1):
        tmp_row = []
        for x in xnodes:
            tmp_row.append(c.binpow(x, i))
        matr.append(tmp_row)
    return matr


def add_phi_to_node_matrix(matr, xnodes):
    tmp_row = []
    next_power = len(matr)
    for x in xnodes:
        tmp_row.append(c.binpow(x, next_power))
    matr.append(tmp_row)
    return matr


def dot_prod_phi_phi(i, j, matr_with_node_vals):
    res = 0
    num_of_nodes = len(matr_with_node_vals[0])
    for k in range(num_of_nodes):
        res += matr_with_node_vals[i][k] * matr_with_node_vals[j][k]
    return (res / num_of_nodes)


def dot_prod_f_phi(i, fnodes, matr_with_node_vals):
    res = 0
    num_of_nodes = len(matr_with_node_vals[0])
    for k in range(num_of_nodes):
        res += matr_with_node_vals[i][k] * fnodes[k]
    return (res / num_of_nodes)


def build_slar(n, xnodes, fnodes, matr_with_node_vals):
    syst_matr = []
    syst_col = []

    for i in range(n+1):
        curr_row = []
        for j in range(n+1):
            if (j >= i): curr_row.append(dot_prod_phi_phi(i,j,matr_with_node_vals))
            else: curr_row.append(syst_matr[j][i])
        syst_matr.append(curr_row)
        syst_col.append(dot_prod_f_phi(i, fnodes, matr_with_node_vals))
    return syst_matr, syst_col


def add_func_to_slar(syst_matr, syst_col, matr_with_node_vals, xnodes, fnodes):
    matr_with_node_vals = add_phi_to_node_matrix(matr_with_node_vals, xnodes)
    tmp_n = len(syst_col)
    for i in range(tmp_n):
        syst_matr[i].append(dot_prod_phi_phi(tmp_n+1, i, matr_with_node_vals))
    syst_col.append(dot_prod_f_phi(tmp_n+1, fnodes, matr_with_node_vals))
    tmp_row = []
    for i in range(tmp_n):
        tmp_row.append(syst_matr[i][tmp_n])
    tmp_row.append(dot_prod_phi_phi(tmp_n+1, tmp_n+1, matr_with_node_vals))
    syst_matr.append(tmp_row)
    return syst_matr, syst_col


def find_coeffs(syst_matr, syst_col):
    coefs = np.linalg.solve(syst_matr, syst_col)
    return coefs


def calculate_sigma(total_points, polin_coefs, matr_with_node_vals, fnodes):
    sigma = 0
    current_degree = len(polin_coefs)
    if (total_points <= current_degree):
        return sigma
    for i in range(total_points):
        tmp = 0
        for j in range(current_degree):
            tmp += polin_coefs[j] * matr_with_node_vals[j][i]
        sigma += (tmp - fnodes[i]) ** 2
    # sigma = sqrt(sigma / (total_points - current_degree))
    sigma = sqrt(sigma / total_points)
    return sigma


def find_optimal_degree(xnodes, fnodes, min_deg=min_d, max_deg=max_d):
    num_of_nodes = len(xnodes)
    current_degree = min_deg
    matr_node_vals = create_node_matrix(xnodes, current_degree)
    syst_matr, syst_col = build_slar(current_degree, xnodes, fnodes, matr_node_vals)
    poli_coefs = find_coeffs(syst_matr, syst_col)
    sigma = calculate_sigma(num_of_nodes, poli_coefs, matr_node_vals, fnodes)
    # max_deg = num_of_nodes * 0.75
    print(current_degree, ' - ', sigma)
    while current_degree < max_deg:
        current_degree += 1
        matr_node_vals = add_phi_to_node_matrix(matr_node_vals, xnodes)
        syst_matr, syst_col = add_func_to_slar(syst_matr, syst_col, matr_node_vals, xnodes, fnodes)
        poli_coefs = find_coeffs(syst_matr, syst_col)
        sigma = calculate_sigma(num_of_nodes, poli_coefs, matr_node_vals, fnodes)
        print(current_degree, ' - ', sigma)


def pol(coefs, x):
    degree = len(coefs)
    res = coefs[0]
    tmp = 1
    for i in range(1,degree):
        tmp *= x
        res += tmp * coefs[i]
    return res


def build_approx_polinom(degree, xnodes, fnodes):
    t1 = time.time()

    num_of_nodes = len(xnodes)
    matr_node_vals = create_node_matrix(xnodes, degree)
    syst_matr, syst_col = build_slar(degree, xnodes, fnodes, matr_node_vals)
    poli_coefs = find_coeffs(syst_matr, syst_col)

    t2 = time.time()
    print('\n', t2-t1, " seconds (table)")

    t = np.arange(c.left_edge, c.right_edge, c.plot_step)
    # plotting P_n (x) (our polynom) and f(x)
    pplt.ylim(c.bot_edge, c.top_edge)
    pplt.plot(t, pol(poli_coefs, t), t, c.f(t))
    pplt.show()

    pplt.ylim(c.bot_edge, c.top_edge)
    pplt.plot(t, abs(pol(poli_coefs, t) - c.f(t)))
    pplt.show()

    eror = integr.quad(lambda x: ( pol(poli_coefs, x) - c.f(x) ) ** 2, c.left_edge, c.right_edge)
    print('\n Error^2 = ', eror)
    eror = sqrt(eror[0])
    print('\n Error   = ', eror)


def build_nodes(num_of_nodes):
    nodes = []
    f_nodes = []
    step = (c.right_edge - c.left_edge) / (num_of_nodes-1)
    '''
    tmp = c.left_edge
    nodes.append(tmp)
    for i in range(num_of_nodes-1):
        tmp += step
        nodes.append(tmp)
    #'''
    for i in range(num_of_nodes):
        tmp = c.left_edge + i * step
        nodes.append(tmp)
    for x in nodes:
        f_nodes.append(c.f(x))
    return nodes, f_nodes


def main_table_polinom(n=N, opt_deg = opt_d, min_deg=min_d, max_deg=max_d):
    xnodes = []
    fnodes = []
    xnodes, fnodes = build_nodes(n)
    find_optimal_degree(xnodes, fnodes, min_deg=min_deg, max_deg=max_deg)
    degree = opt_deg
    build_approx_polinom(degree, xnodes, fnodes)
