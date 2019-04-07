import math

PI = math.pi
left_edge = -1.
right_edge = 1.
top_edge = 1.1
bot_edge = -0.06
mini_top_edge = 0.5
mini_bot_edge = 0.
nodes = 11
num_of_plot_nodes = 0
plot_step = 0.001

# our function f(x) = 1/(1+25x^2)
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
