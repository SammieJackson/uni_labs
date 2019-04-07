# import math as m
import numpy as np
import exceptions as exc


required_bin_length = []
partial_sums_of_bin_length = []
bin_representation_step = []
bin_dec_param_called = False
epsilon = 0
smallest_order = 0
int_part_len = 0


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

'''
# Python program to convert float
# decimal to binary number
# Function returns octal representation
def float_bin(number: float, places=3):
    # split() seperates whole number and decimal
    # part and stores it in two seperate variables
    whole, dec = str(number).split(".")

    # Convert both whole number and decimal
    # part from string type to integer type
    whole = int(whole)
    dec = int(dec)

    # Convert the whole number part to it's
    # respective binary form and remove the
    # "0b" from it.
    res = bin(whole).lstrip("0b") + "."

    # Iterate the number of times, we want
    # the number of decimal places to be
    for x in range(places):
        # Multiply the decimal value by 2
        # and seperate the whole number part
        # and decimal part
        whole, dec = str((decimal_converter(dec)) * 2).split(".")

        # Convert the decimal part
        # to integer again
        dec = int(dec)

        # Keep adding the integer parts
        # receive to the result variable
        res += whole

    return res


# Function converts the value passed as
# parameter to it's decimal representation
def decimal_converter(num):
    while num > 1:
        num /= 10
    return num
#'''


def float_bin(x: float, whole_len: int, decimal_len: int):
    res = ""
    if x < 0:
        res += '-'
    x = abs(x)
    whole, dec = str(x).split(".")
    whole = int(whole)
    x = x - whole
    tmp_res = bin(whole).lstrip("0b") + "."
    if (whole_len >= len(tmp_res)):
        for i in range(whole_len - len(tmp_res) + 1):
            res += '0'
    res += tmp_res
    count = 0
    tmp = 1
    while (count < decimal_len):
        tmp /= 2
        count += 1
        if x >= tmp:
            res += '1'
            x -= tmp
        else:
            res += '0'
        '''
        # or
        x *= 2
        whole = int(x)
        x = x - whole
        res += bin(whole).lstrip("0b")
        #'''
    return res


# returns number of digits in the binary representation of the whole part of x
def get_whole_bin_len(x: float)->int:
    whole = int(abs(x))
    res = len(bin(whole).lstrip("0b"))
    return res


def bin_dec_param(m: int, x_min: np.ndarray, x_max: np.ndarray, eps: float):
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
        # nn[i] = int(m.log( (t_max-t_min)/eps , 2)) + 1  # это формула из док-файла с лекций
        nn.append( max(get_whole_bin_len(t_max), get_whole_bin_len(t_min)) + smallest_order )
        # dd.append( (t_max - t_min) / binpow(2, nn[i]) )  # это формула из док-файла с лекций
        dd.append(1 / binpow(2, smallest_order))
        NN.append( NN[i] + nn[i] )
    global required_bin_length
    global partial_sums_of_bin_length
    global bin_representation_step
    required_bin_length = np.array(nn)
    partial_sums_of_bin_length = np.array(NN)
    bin_representation_step = np.array(dd)
    global int_part_len
    int_part_len = required_bin_length.max() - smallest_order
    return 0


def reset_called_flag():
    bin_dec_param_called = False


def cod_binary(x: float, x_min: float, call_bin_dec_param = False, decimal_len=smallest_order, whole_len=int_part_len, eps=0.5):
    if call_bin_dec_param:
        bin_dec_param(1, np.array([x_min]), np.array([x]), eps)
        decimal_len = smallest_order
        whole_len = int_part_len
    res = float_bin(x, whole_len, decimal_len)
    x_bin = [c for c in str(res)]
    return x_bin


def cod_decimal(x: "list of chars") -> float:
    if len(x) == 0:
        return 0
    if x[0] == '-':
        negative = True
        x = x[1:]
    whole_bin, dec_bin = str(x).split(".")
    res = int(whole_bin,2)
    tmp = 1.
    for i in range(len(dec_bin)):
        tmp /= 2
        if dec_bin[i] == '1':
            res += tmp
    if negative:
        res *= -1
    return res


def acod_binary(matr: np.ndarray):
    return 0


def acod_decimal():
    return 0

