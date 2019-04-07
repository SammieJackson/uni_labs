import numpy as np
import methods as mt
import enc_dec_doc as md


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

    m10 = np.array([[1.54, 1.96],[1.02, 4.73]])
    print(m10)
    m2 = md.acod_binary(m10)
    print(m2)
    # print(m2.shape)
    m1 = md.acod_decimal(m2)
    print(m1)
    print(m1-m10)

test_acods()