import numpy as np
import matplotlib.pyplot as plt
from math import cos, pi, sqrt
from typing import List

def f(x: list()) -> float:
    return sum(x0 ** 2 for x0 in x)

# y = [1,2,3]
# print(f(y))

# Parameter init

# x = [1 2]
# y = f(x)

dims = 2        # number of dimensions
min_val = -10   # lower bound
max_val = 10    # upper bound

iters = 1000        # maximum number of iterations
swarm = 50          # population (swarm size)
inert = 1           # intertia coefficient
inert_damp = 0.99   # damping ratio of inertia coefficient
phi_p = 2           # personal acceleration coefficient - phi_p
phi_g = 2           # social acceleration coefficient - phi_g
show_iters = True   # flag for showing iteration info

# for normalization - so that phi_p and _g do not influence speed that much

param_k = 0.5  # another parameter - should be between 0 and 1
phi = phi_p + phi_g
normalization_coeff = 2 * param_k / abs(2 - phi - sqrt(phi ** 2 - 4 * phi))

