import methods as md
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as ani
import scipy.integrate as intgr
# import test0


#'''
# animated heart with sin()
val = 1.8
nodes = 400
pi = math.pi
frames_num = 200
param_step = 10 / frames_num

def init():
    line.set_data([], [])
    return line,


def heart(x, a):
    # return x ** (2.0/3) + 0.9 * math.sqrt(3.3 - x**2) * np.sin(a * pi * x)
    return (x ** 2) ** (1.0 / 3) + 0.9 * math.sqrt(3.3 - x ** 2) * np.sin(a * pi * x)


def get_frame(a):
    x = np.linspace(-val, val, nodes)
    y = np.zeros(x.size)
    for i in range(x.size):
        y[i] = heart(x[i], a * param_step)
    line.set_data(x, y)
    return line,


fig = plt.figure(figsize=(7, 7))
# plt.xlim([-2.5, 2.5])
# plt.ylim([-1.5, 4])
ax = plt.axes(xlim=(-2.5, 2.5), ylim=(-1.5, 4))
line, = ax.plot([], [], lw=2)
anim = ani.FuncAnimation(fig, get_frame, init_func=init, frames=frames_num, interval=20, blit=True)
plt.show()
#'''



'''
param = 8.0
val = 1.8
nodes = 400
pi = math.pi


def heart(x, a):
    # return x ** (2.0/3) + 0.9 * math.sqrt(3.3 - x**2) * np.sin(a * pi * x)
    return (x ** 2) ** (1.0 / 3) + 0.9 * math.sqrt(3.3 - x ** 2) * np.sin(a * pi * x)


def plot_heart(a):
    x = np.linspace(-val, val, nodes)
    y = np.zeros(x.size)
    for i in range(x.size):
        y[i] = heart(x[i],a)
    plt.plot(x, y)
    plt.xlim([-5, 5])
    plt.ylim([-5, 5])
    return 0


plt.figure()
plot_heart(param)
plt.show()
#'''


#'''
def main_it(myfunc, iterations):
    res = md.runge(func=myfunc, bot=md.new_bot, top=md.new_top, iters=iterations)
    print(6*res)
    res2 = np.log(4) / 3
    print(res2)
    print(abs(6*res - res2))


def main_eps(myfunc, epsilon):
    res = md.runge(func=myfunc, bot=md.new_bot, top=md.new_top, eps=epsilon)
    print(6*res)
    res2 = np.log(4) / 3
    print(res2)
    print(abs(6*res - res2))


def main_all_1(myfunc, global_eps):
    int_eps = global_eps / 2
    int_bot = 2
    eps_top = math.ceil(1 + 1 / int_eps) + 1
    print("\n A_eps \n", eps_top)
    res1, h_simp = md.simpsons_mod(func=myfunc, bot=int_bot, top=eps_top, eps=int_eps)
    print("\n Simpson: \t ", res1)
    res21, h_runge = md.runge2(func=myfunc, bot=int_bot, top=eps_top, eps=int_eps, use_Richardson=False)
    res22, h_rich = md.runge2(func=myfunc, bot=int_bot, top=eps_top, eps=int_eps, use_Richardson=1)
    # res21 = md.runge(func=myfunc, bot=md.new_bot, top=top, eps=0.001, use_Richardson=False)
    # res22 = md.runge2(func=myfunc, bot=md.new_bot, top=top, eps=0.001, use_Richardson=1)
    # res2 = md.runge2(func=myfunc, bot=md.new_bot, top=md.new_top, eps=1e-10, use_Richardson=1)
    # res2 = md.runge2(func=myfunc, bot=md.new_bot, top=md.new_top, iters=1, use_Richardson=1)
    print(" Runge: \t ", res21)
    print(" Richardson: ", res22)
    real = np.log(4) / 3
    print(" Real value: ", real)

    print("\n h-step (Simp):  ", h_simp)
    print(" h-step (Runge): ", h_runge)
    print(" h-step (Rich):  ", h_rich)

    print("\n Error (ariori): \t\t ", 33.0*(eps_top - int_bot)*md.binpow(h_simp, 4)/(32*2880))
    print(" |Simpson - Runge|: \t ", abs(res1 - res21))
    print(" |Simpson - Richardson|: ", abs(res1 - res22))
    print(" |Runge - Richardson|:   ", abs(res21 - res22))
    print(" |Simpson - Real|:  \t ", abs(res1 - real))
    print(" |Runge - Real|:  \t\t ", abs(res21 - real))
    print(" |Richardson - Real|: \t ", abs(res22 - real))


def main_all_0(myfunc, global_eps):
    myfunc = md.ft
    res1 = md.simpsons(func=myfunc, bot=md.new_bot, top=md.new_top)
    print(" Simpson: \t ", res1)
    res21 = md.runge(func=myfunc, bot=md.new_bot, top=md.new_top, eps=0.001, use_Richardson=False)
    res22 = md.runge2(func=myfunc, bot=md.new_bot, top=md.new_top, eps=0.001, use_Richardson=1)
    # res2 = md.runge2(func=myfunc, bot=md.new_bot, top=md.new_top, eps=1e-10, use_Richardson=1)
    # res2 = md.runge2(func=myfunc, bot=md.new_bot, top=md.new_top, iters=1, use_Richardson=1)
    print(" Runge: \t ", res21)
    print(" Richardson: ", res22)
    real = np.log(4) / 3
    print(" Real value: ", real)
    print("\n Error (ariori): \t\t ", 33.0/(32*2880))
    print(" |Simpson - Runge|: \t ", abs(res1 - res21))
    print(" |Simpson - Richardson|: ", abs(res1 - res22))
    print(" |Runge - Richardson|:   ", abs(res21 - res22))
    print(" |Simpson - Real|:  \t ", abs(res1 - real))
    print(" |Runge - Real|:  \t\t ", abs(res21 - real))
    print(" |Richardson - Real|: \t ", abs(res22 - real))


def myf(x):
    return x


# main_eps(md.ft, 0.001)
# main_it(md.ft, 10)
# main_all_1(md.f, 0.002)
# main_all_0(md.ft)
# main_all(myf)

# print(max(abs(math.inf - 1), 2))
# print(abs(math.inf - 1) > 2)
# print(abs(math.inf - 1) > math.inf)
# print((math.inf - 1) == (math.inf-2))
#'''


'''
md.runge(0.1, 5, 5)
#'''

'''
n = 2
pi = math.pi

syst = [(lambda y: lambda x: np.sin(y * x))(i) for i in range(n+1)]
# syst2 = [lambda x: np.sin(i * x) for i in range(n+1)]
# a = np.linspace(0, 2 * pi, 2 * n+1)
a = np.linspace(0, 2, 2 * n+1) * pi
print(a)
print([syst[1](a0) for a0 in a])
# print(syst[0](pi/2))
# print(math.sin(pi/2))
coefs = [0]*(n+1)
coefs[1] = 1


def pol1(coef, sys):
    return ( lambda x: sum( [(lambda y: coef[y]*sys[y](x))(i) for i in range(n+1)] ) )

def pol2(coef, sys):
    return ( lambda x: sum( [coef[i]*sys[i](x) for i in range(n+1)] ) )

my_pol = pol1(coefs, syst)
print(my_pol(a))
#'''

'''
a = [1, 2, 3]
print(a)
a.append(4)
print(a)
# a.append([5, 6][:])
# a.append([i for i in [5, 6]])
# (a.append(i) for i in [5, 6])
[a.append(i) for i in [5, 6]]
print(a)
# b = [a.append(i) for i in [5, 6]]
# print(b)
#'''

'''
def f(x):
    return 2*x

def g(x):
    return x+1

def inner_prod(f, g):
    return intgr.quad(lambda x: f(x)*g(x), -1, 1)

# res = intgr.quad(lambda x: f(x)*g(x), -1, 1)
res = inner_prod(f, g)
print(res)
#'''


'''
def test():
    bot, top = [1, 2]
    n = 100
    res = md.simpsons(bot, top, n)
    print(res)
    print(intgr.quad(lambda x: md.f(x), bot, top))

test()
#'''

