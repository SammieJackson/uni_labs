import math
import numpy as np
import exceptions as exc


required_bin_length = []
partial_sums_of_bin_length = []
bin_representation_step = []
bin_dec_param_called = False
epsilon = 0
smallest_order = 0
int_part_len = 0
xmin = np.array([])
xmax = np.array([])


def reset_globals():
    global required_bin_length
    global partial_sums_of_bin_length
    global bin_representation_step
    global bin_dec_param_called
    global epsilon
    global smallest_order
    global int_part_len
    global xmin
    global xmax
    required_bin_length = []
    partial_sums_of_bin_length = []
    bin_representation_step = []
    bin_dec_param_called = False
    epsilon = 0
    smallest_order = 0
    int_part_len = 0
    xmin = []
    xmax = []

def check_type(x):
    if isinstance(x, np.ndarray):
        return True
    return False


def gen_dec(rows: int, cols: int, x_min: np.ndarray, x_max: np.ndarray): # -> np.ndarray:
    print(x_min)
    matr = np.zeros([rows, cols])
    if (rows <= 0 | cols <= 0):
        pass
        # raise exc.BadArgumentTypeException()
    flag = (len(x_min.shape) == 1) & (x_min.shape[0] == cols) & (len(x_max.shape) == 1) & (x_max.shape[0] == cols)
    if not flag:
        pass
        # raise exc.BadArgumentDimensionsException()
    for i in range(cols):
        bot = x_min[i]
        top = x_max[i]
        if bot >= top:
            pass
            # raise exc.BadArgument
        for j in range(rows):
            matr[j][i] = bot + (top - bot) * np.random.random()
    #"""
    print(matr)
    return matr


def binpow(a, n: int):
    res = 1
    while n:
        if (n & 1):
            res *= a
        a *= a
        n >>= 1
    return res


def bin_dec_param(m: int, x_min: np.ndarray, x_max: np.ndarray, eps: float):
    global bin_dec_param_called
    bin_dec_param_called = True
    flag = (len(x_min.shape) == 1) & (x_min.shape[0] == m) & (len(x_max.shape) == 1) & (x_max.shape[0] == m)
    if not flag:
        pass
        # raise exc.BadArgumentDimensionsException()
    nn = [] ## numebr of binary digits
    dd = [] ## smallest possible precision achievable with nn[i] binary digits
    NN = [] ## partial sums of nn[i]
    NN.append(0)

    global epsilon
    epsilon = eps
    tmp = 1
    global smallest_order
    smallest_order = 0
    while tmp > eps:
        tmp = tmp / 2
        smallest_order = smallest_order + 1
    # print(smallest_order)

    for i in range(m):
        t_max = x_max[i]
        t_min = x_min[i]
        if t_min >= t_max:
            pass
            # raise exc.BadArgument
        nn.append( int( math.log( (t_max-t_min)/eps , 2) ) + 1 )  # это формула из док-файла с лекций
        dd.append( (t_max - t_min) / binpow(2, nn[i]) )  # это формула из док-файла с лекций
        NN.append( NN[i] + nn[i] )
    global required_bin_length
    global partial_sums_of_bin_length
    global bin_representation_step
    required_bin_length = np.array(nn)
    partial_sums_of_bin_length = np.array(NN)
    bin_representation_step = np.array(dd)
    global xmin
    global xmax
    xmin = x_min
    xmax = x_max
    # global int_part_len
    # int_part_len = required_bin_length.max() - smallest_order
    return 0


def reset_called_flag():
    bin_dec_param_called = False


def cod_binary(x: float, col_index: int):
    if x < 0:
        pass
        #raise  exc.BadArgument
    if not bin_dec_param_called:
        print("ho")
        return 0
    res = int( (x-xmin[col_index]) / bin_representation_step[col_index])
    x_bin = np.zeros(required_bin_length[col_index])
    tmp = 1
    for i in range(required_bin_length[col_index]):
        if res % 2 == 1:
            x_bin[-i-1] = 1
        res = int(res/2)
    return x_bin


def cod_decimal(x: np.ndarray, col_index: int) -> float:
    res = xmin[col_index]
    tmp = bin_representation_step[col_index]
    s = ""
    for x0 in x:
        s += str(int(x0))
    res += bin_representation_step[col_index] * int(s,2)
    '''
    for i in range(required_bin_length[col_index]):
        if x[-i-1] == 1:
            res += tmp
        tmp *= 2
    #'''
    return res


def acod_binary(matr: np.ndarray):
    rows, cols = matr.shape[:]
    if not cols == xmin.size:
        pass
        # raise exc.BadArgument
    global partial_sums_of_bin_length
    global required_bin_length
    NN = partial_sums_of_bin_length
    nn = required_bin_length
    res = np.zeros((rows, NN[-1]))
    for c in range(cols):
        for r in range(rows):
            tmp = cod_binary(matr[r][c], c)
            # print(tmp)
            start_ind = NN[c]
            for j in range(nn[c]):
                res[r][start_ind+j] = tmp[j]
    return res


def acod_decimal(matr: np.ndarray):
    rows, total_cols = matr.shape[:]
    cols = xmin.shape[0]
    global partial_sums_of_bin_length
    if not total_cols == partial_sums_of_bin_length[-1]:
        pass
        # raise exc.BadArgument
    global bin_representation_step
    NN = partial_sums_of_bin_length
    nn = bin_representation_step
    res = np.zeros((rows, cols))
    for c in range(cols):
        for r in range(rows):
            tmp = np.array(matr[r][NN[c]:NN[c+1]])
            res[r][c] = cod_decimal(tmp,c)
    return res

