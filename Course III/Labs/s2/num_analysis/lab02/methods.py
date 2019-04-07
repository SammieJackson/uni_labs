import numpy as np
import math


max_iters = 22
nodes = 10
M4 = 33.0/32

new_bot = 0.
new_top = 1.



def f(x: float):
    if (x == -2) | (x == 1):
        return 0
    return 1 / ((x + 2) * (x - 1))

# 0.46209812037329687294482141430545104538366675624017016941378667299559574797979647707057555133094579169466765401371...
#
# the integral can be calculated by hand and is equal to ln(4)/3


def ft(x: float):
    if (x == 2) | (x == -1):
        return 0
    return 1 / ((2 - x) * (x + 1))


def binpow(a, n):
    res = 1
    while n:
        if n & 1:
            res *= a
        a *= a
        n >>= 1
    return res


def simpsons(func, bot, top, n=nodes):
    h = (top - bot) / n

    # List for storing value of x and f(x)
    x = np.zeros(2*n+1)
    fx = np.zeros(2*n+1)

    # Calcuting values of x and f(x)
    for i in range(n+1):
        x[2*i] = (bot + i * h)
        fx[2*i] = (func(x[2*i]))
    for i in range(n):
        x[2*i+1] = (x[2*i] + x[2*i+2]) / 2
        fx[2*i+1] = (func(x[2*i+1]))

    # Calculating result
    res = fx[0] + fx[-1]
    for i in range(1, n):
        res += 2*fx[2*i]
    for i in range(1, n+1):
        res += 4*fx[2*i-1]

    res *= h / 6
    return res


def simpsons_mod(func, bot: float, top: float, eps: float, n=nodes):
    h0 = math.sqrt(math.sqrt(eps / (M4 * (top-bot) / 2880)))
    print("\n h0 \n", h0)
    n = math.ceil((top-bot)/h0)
    print("\n n0 \n", n)
    h = (top - bot) / n
    print("\n h-step (Simpson) : \n", h)

    # List for storing value of x and f(x)
    x = np.zeros(2*n+1)
    fx = np.zeros(2*n+1)

    # Calcuting values of x and f(x)
    for i in range(n+1):
        x[2*i] = (bot + i * h)
        fx[2*i] = (func(x[2*i]))
    for i in range(n):
        x[2*i+1] = (x[2*i] + x[2*i+2]) / 2
        fx[2*i+1] = (func(x[2*i+1]))

    # Calculating result
    res = fx[0] + fx[-1]
    for i in range(1, n):
        res += 2*fx[2*i]
    for i in range(1, n+1):
        res += 4*fx[2*i-1]

    res *= h / 6
    return res, h


def runge(func, bot, top, eps=None, iters=None, init_num_of_nodes=nodes, use_Richardson=True):
    flag = False   # flag is True if we do not care for precision (for epsilon), and vice-versa
    if iters is None:
        iters = max_iters
    if iters > max_iters:
        iters = max_iters
    if iters < 1:
        iters = 1
    if eps is None:
        eps = 0
        flag = True
    if eps < 0:
        eps = 0

    n0 = init_num_of_nodes
    iter_step_tmp = binpow(2, iters)
    max_nodes = iter_step_tmp * n0 + 1
    x = np.zeros(max_nodes)
    fx = np.zeros(max_nodes)

    current_num_nodes = n0 + 1
    h_tmp = (top - bot) / (current_num_nodes - 1)
    tmp_ind = 0
    iterations_vals = []
    ih = 0
    for i in range(current_num_nodes):
        x[tmp_ind] = bot + i * h_tmp
        fx[tmp_ind] = func(x[tmp_ind])
        ih += fx[tmp_ind]
        tmp_ind += iter_step_tmp
    # ih = (ih - 0.5 * (fx[0] + fx[-1])) * h_tmp
    # ih = simpsons(func, bot, top, n=n0)
    iterations_vals.append(ih)
    # тут мы взяли интеграл по ф-ле трапеций как начальное приближение

    num_nodes_to_add = n0
    iter_step_tmp //= 2
    iter = 1
    dif = eps + 1
    while (iter <= iters) & (flag | (dif > eps)):
        h_tmp = (top - bot) / (current_num_nodes + num_nodes_to_add - 1)
        ih = 0
        tmp_ind = iter_step_tmp
        for i in range(num_nodes_to_add):
            # x[tmp_ind] = bot + (2 * i + 1) * h_tmp
            x[tmp_ind] = (x[tmp_ind - iter_step_tmp] + x[tmp_ind + iter_step_tmp]) / 2
            fx[tmp_ind] = func(x[tmp_ind])
            ih += 4 * fx[tmp_ind] + fx[tmp_ind - iter_step_tmp] + fx[tmp_ind + iter_step_tmp]
            tmp_ind += 2 * iter_step_tmp

        '''
        ih = fx[0] + fx[-1]
        for i in range(1, num_nodes_to_add):
            ih += 2 * fx[0]
        for i in range(1, num_nodes_to_add+1):
            ih += 4 * fx[0]
        #'''

        ih *= (2 * h_tmp / 6)
        dif = abs(ih - iterations_vals[-1])
        iterations_vals.append(ih)
        current_num_nodes += num_nodes_to_add
        num_nodes_to_add *= 2
        iter_step_tmp //= 2
        iter += 1

    res = 0
    if use_Richardson:
        res = (16 * iterations_vals[-1] - iterations_vals[-2]) / 15  # ф-ла Ричардсона <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    else:
        res = iterations_vals[-1]

    return res, h_tmp


# this one differs from the previous by the way the first approximation and difference are computed
# and here we do one iteration more than in the previous one
def runge2(func, bot, top, eps=None, iters=None, n=nodes, use_Richardson=True):
    # flag = False   # flag is True if we do not care for precision (for epsilon), and vice-versa
    if iters is None:
        iters = max_iters
    if iters > max_iters:
        iters = max_iters
    if iters < 1:
        iters = 1
    if eps is None:
        eps = 0
    if eps < 0:
        eps = 0

    n0 = n
    iter_step_tmp = binpow(2, iters + 1)
    max_nodes = 2 * iter_step_tmp * n0 + 1
    x = np.zeros(max_nodes)
    fx = np.zeros(max_nodes)

    current_num_nodes = n0 + 1
    h_tmp = (top - bot) / (current_num_nodes - 1)
    tmp_ind = 0
    iterations_vals = []
    ih = 0
    for i in range(current_num_nodes):
        x[tmp_ind] = bot + i * h_tmp
        fx[tmp_ind] = func(x[tmp_ind])
        tmp_ind += iter_step_tmp

    num_nodes_to_add = n0
    iter_step_tmp //= 2
    iter = 0
    dif = eps + 1
    prev_ih = math.inf
    while (iter <= iters) & (dif > eps):
        # print(iter)
        h_tmp = (top - bot) / (current_num_nodes + num_nodes_to_add - 1)
        ih = 0
        tmp_ind = iter_step_tmp
        for i in range(num_nodes_to_add):
            # x[tmp_ind] = bot + (2 * i + 1) * h_tmp
            x[tmp_ind] = (x[tmp_ind - iter_step_tmp] + x[tmp_ind + iter_step_tmp]) / 2
            fx[tmp_ind] = func(x[tmp_ind])
            ih += 4 * fx[tmp_ind] + fx[tmp_ind - iter_step_tmp] + fx[tmp_ind + iter_step_tmp]
            tmp_ind += 2 * iter_step_tmp

        ih *= (2 * h_tmp / 6)
        dif = abs(ih - prev_ih)
        prev_ih = ih
        iterations_vals.append(ih)
        current_num_nodes += num_nodes_to_add
        num_nodes_to_add *= 2
        iter_step_tmp //= 2
        iter += 1

    res = 0
    if use_Richardson:
        res = (16 * iterations_vals[-1] - iterations_vals[-2]) / 15  # ф-ла Ричардсона <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    else:
        res = iterations_vals[-1]

    return res, h_tmp

