import numpy as np
import methods as mt
import enc_dec_doc as md
import mut_cross_doc as mut
import format_doc as form



'''
def test_adapt():
    n = 5
    per = np.ones(n)
    print(per)
    res = form.Adapt(per, n)
    print(res)
    print(res.sum())

test_adapt()
#'''


'''
def test_list_gen():
    n = 5
    ml, fl = form.Parents(n)
    print(ml)
    print(fl)

test_list_gen()
#'''


'''
def test_cross():
    n = 2
    rows = 2*n
    cols = 5
    a = np.random.randint(low=0, high=2, size=(rows, cols))
    # m_list = np.random.randint(low=0, high=rows, size=(1,n))
    # f_list = np.random.randint(low=0, high=rows, size=(1,n))
    m_list = np.array([0, 2])
    f_list = np.array([1, 3])
    res = mut.crossover(a, m_list, f_list)
    print(a)
    print('\n', res)
    print('\n', a - res)

test_cross()
#'''

'''
def test_mut():
    a = np.random.randint(low=0,high=2,size=(4,4))
    p = 0.5
    res, num_of_changes = mut.mutation(a, p)
    print(a)
    print('\n', res)
    print('\n', a-res)
    print('\n', num_of_changes)

test_mut()
#'''


'''
def test_acods2():

    md.reset_globals()

    eps = 0.01
    m = 100
    xmin = np.array((1,m))
    xmin.fill(1)
    xmax = np.array((1,m))
    xmax.fill(1)
    md.bin_dec_param(m, xmin, xmax, eps)

    print(md.smallest_order)
    print(md.required_bin_length)
    print(md.bin_representation_step)

    m10 = md.gen_dec(m, m, xmin, xmax)
    print(m10)
    m2 = md.acod_binary(m10)
    # print(m2)
    print(m2.shape)
    m1 = md.acod_decimal(m2)
    # print(m1)
    error = m1-m10
    print(error)

test_acods2()
#'''

'''
def test_acods():

    md.reset_globals()

    eps = 0.01
    m = 2
    xmin = [1, 1]
    xmax = [2, 5]
    x_mi = np.array(xmin)
    x_ma = np.array(xmax)
    md.bin_dec_param(m, x_mi, x_ma, eps)

    print(md.smallest_order)
    print(md.required_bin_length)
    print(md.bin_representation_step)

    m10 = np.array([[1.54, 1.96], [1.02, 4.73]])
    print(m10)
    m2 = md.acod_binary(m10)
    print(m2)
    # print(m2.shape)
    m1 = md.acod_decimal(m2)
    print(m1)
    print(m1-m10)

test_acods()
#'''


'''
def test_bin_dec_param():

    md.reset_globals()

    eps = 0.01
    m = 1
    xmin = [1]
    xmax = [2]
    x_mi = np.array(xmin)
    x_ma = np.array(xmax)
    md.bin_dec_param(m, x_mi, x_ma, eps)

    print(md.smallest_order)
    print(md.required_bin_length)
    print(md.bin_representation_step)

    y = 1.56
    z = md.cod_binary(y,0)
    print(z)
    y0 = md.cod_decimal(z,0)
    print(y0)

test_bin_dec_param()
#'''

'''
print(mt.cod_binary(2.125, 0, call_bin_dec_param=True, eps=1/mt.binpow(2,6)))
print(mt.smallest_order)
print(mt.required_bin_length)
print(mt.bin_representation_step)
#'''

# print(mt.cod_decimal("-010.10100"))

'''
def test_bin_dec_param():

    eps = 0.3
    m = 1
    xmin = [1]
    xmax = [2]
    x_mi = np.array(xmin)
    x_ma = np.array(xmax)
    mt.bin_dec_param(m, x_mi, x_ma, eps)

    print(mt.smallest_order)
    print(mt.required_bin_length)
    print(mt.bin_representation_step)

    return 0

test_bin_dec_param()
#'''

# print(mt.float_bin(-2.125,5,7))
# print(mt.get_whole_bin_len(1023.234))

'''
a = 1

def f(x):
    global a
    a = [x, 1]
    return x+1

print(a)
f(2)
print(a)
#'''


'''
x_min = np.array([1,2])
x_max = np.array([3,7])
print(len(x_max.shape))
m = mt.gen_dec(3,2,x_min,x_max)
print(m)
#'''


'''
m = np.zeros([2, 3])
print(m)
#'''
