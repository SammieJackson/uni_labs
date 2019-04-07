import matplotlib.pyplot as pplt
import numpy as np
import math as m


PI = m.pi
left_edge = -1.
right_edge = 1.
top_edge = 1.
bot_edge = 0.
mini_top_edge = 0.5
mini_bot_edge = -0.5
nodes = 11
# x_nodes = []
# node_f_vals = []
# divided_diffs = []
num_of_plot_nodes = 0
plot_step = 0.001



def f(x):
    return 1 / (1 + (25 * x * x))

def binpow(a, n):
    res = 1
    while n:
        if (n & 1):
            res *= a
        a *= a
        n >>= 1
    return res

def polynom(coefs, x):
    res = 0
    x_n = 1
    for i in coefs:
        res += (i * x_n)
        x_n *= x
    return res

def get_nodes_equidist(left, right, num):
    x_nodes = []
    tmp_node = left
    step = (right - left) / (num-1)
    for i in range(num):
        x_nodes.append(tmp_node)
        tmp_node += step
    return x_nodes


def get_nodes_chebyshev(left, right, num):
    xnodes = []
    tmp_node_arg = 1 / (2 * num)
    for i in range(num):
        xnodes.append( (right + left) / 2 + (right - left) / 2 * m.cos(PI * ( (2 * i + 1) / (2 * num) ) ) )
        # xnodes.append( m.cos( PI * ( (2 * i + 1) / (2 * num) ) ) )
        tmp_node_arg += 1 / num
    return xnodes

def compute_nodes_f_vals(xnodes):
    fnodes = []
    for x in xnodes:
        fnodes.append(f(x))
    return fnodes

def w_n(x, xnodes): # product of differececs
    res = 1
    for x_i in xnodes:
        res *= x - x_i
    return res

def compute_differences(xnodes, fnodes):
    diffs_k_order = fnodes
    nums = len(xnodes)
    if nums != len(fnodes): return 0
    for i in range(nums - 1):
        for j in range(nums - i - 1):
            diffs_k_order[(nums - 1) - j] = (diffs_k_order[(nums - 1) - j] - diffs_k_order[(nums - 1) - j - 1]) / (xnodes[nums - j - 1] - xnodes[nums - j - 1 - i - 1])
        # print(diffs_k_order)
    return diffs_k_order

# NEWTON'S INTERPOLATION POLYNOMIAL
def my_polynom(div_diffs, xnodes, x):
    tmp_product = 1
    res = 0
    nums = len(xnodes)
    for i in range(nums):
        res += tmp_product * div_diffs[i]
        tmp_product *= (x - xnodes[i])
    return res


def myplot_1(xnodes, diffs):
    t = np.arange(left_edge, right_edge, plot_step)
    # plotting P_n (x) (our polynom) and f(x)
    pplt.ylim(bot_edge, top_edge)
    pplt.plot(t, my_polynom(diffs, xnodes, t), t, f(t))
    # pplt.plot(t, f(t))
    # pplt.plot(t, my_polynom(diffs, xnodes, t))
    pplt.show()

def myplot_2(xnodes ,diffs):
    t = np.arange(left_edge, right_edge, plot_step)
    # plotting the difference P_n - f (x) and w_n (x)
    # pplt.ylim(mini_bot_edge, mini_top_edge)
    # pplt.plot(t, f(t) - my_polynom(diffs, xnodes, t), t, w_n(t, xnodes))
    #
    pplt.ylim(-0.01, 0.01)
    pplt.plot(t, w_n(t, xnodes), 'C1')
    pplt.show()
    #
    pplt.ylim(mini_bot_edge, mini_top_edge)
    pplt.plot(t, f(t) - my_polynom(diffs, xnodes, t))
    pplt.show()

def main():
    # x_nodes = get_nodes_equidist(left_edge, right_edge, nodes)
    x_nodes = get_nodes_chebyshev(left_edge, right_edge, nodes)
    # print(x_nodes)
    node_f_vals = compute_nodes_f_vals(x_nodes)
    # print(node_f_vals)
    divided_diffs = compute_differences(x_nodes, node_f_vals)
    # print(divided_diffs)
    myplot_1(x_nodes, divided_diffs)
    myplot_2(x_nodes, divided_diffs)

def compute_target_val():
    max_f = f(0)
    min_f = f(1)
    y = min_f + (2/3) * (max_f - min_f)
    return y

def back_interpol():
    # x_nodes = get_nodes_equidist(0.1, 0.2, 4)
    x_nodes = get_nodes_chebyshev(0.1, 0.2, 4)
    print(x_nodes)
    node_f_vals = compute_nodes_f_vals(x_nodes)
    print(node_f_vals)
    diffs = compute_differences(node_f_vals, x_nodes)
    target = compute_target_val()
    print(target)
    # print(f(0.1))
    x_targ = my_polynom(diffs, node_f_vals, target)
    print(x_targ)
    print(f(x_targ))
    print(f(x_targ) - target)


# main()
back_interpol()
