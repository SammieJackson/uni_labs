import numpy as np
import matplotlib.pyplot as plt
from math import cos, pi
from typing import List

n = 2


def f1(x: np.array, n: int = 2) -> float:
    """ Rastrigin function """
    return 10 * n + sum(x[i] ** 2 - 10 * cos(2 * pi * x[i]) for i in range(n))


# def f2(x: np.array, n: int=2) -> float:
# 	""" Rosenbrock's function """
# 	return sum(100 * (x[i + 1] - x[i]**2)**2 + (1 - x[i])**2 for i in range(n - 1))


a, b = -5, 5  # bounds

# plot of Rastrigin function
dx = .1


def plot_f1():
    xs = np.arange(a, b + dx, dx)

    x1s, x2s = np.meshgrid(xs, xs)

    f1s = np.array([[f1([x1s[i, j], x2s[i, j]]) for j in range(len(xs))] \
                    for i in range(len(xs))])

    plt.contourf(x1s, x2s, f1s)
    plt.contour(x1s, x2s, f1s, colors='k')


# plt.figure(figsize=(10, 10))
# plt.axis([a, b + dx, a, b + dx])
# plot_f1()
# plt.show()

# # plot of Rosenbrock's function

# f2s = np.array([[f2([x1s[i, j], x2s[i, j]]) for j in range(len(xs))] for i in range(len(xs))])

# plt.contourf(x1s, x2s, f2s)
# plt.contour(x1s, x2s, f2s, colors='k')
# plt.show()


# generate particles

def get_random_particle(n: int = 2):
    return np.random.random(n) * (b - a) + a


l = 30  # swarm size

x = np.array([get_random_particle() for j in range(l)])

f = np.array([f1(x[j]) for j in range(l)])

xl = np.copy(x)

xg = np.copy(x[np.argmin(f)])

eps = 0.01


def get_random_velocity(n: int = 2):
    return np.random.random(n) * (2 * eps) - eps


v = np.array([get_random_velocity() for j in range(l)])


def plot_x_v():
    plt.scatter(x[:, 0], x[:, 1], c='k')
    plt.quiver(x[:, 0], x[:, 1], v[:, 0], v[:, 1])


# optimizing Rastrigin function

step = .1

omega, a1, a2 = 5 * step, step, 2 * step

max_iter = 30


def is_position_valid(x: np.array) -> bool:
    return np.all(a < x) and np.all(x < b)


def k(i):
    return 1 - i / (2 * max_iter)


for i in range(max_iter):
    rand1, rand2 = np.random.rand(l, n), np.random.rand(l, n)
    v = k(i) * (omega * v + a1 * rand1 * (xl - x) + a2 * rand2 * (xg - x))

    plt.figure(figsize=(10, 10))
    plt.axis([a, b + dx, a, b + dx])
    plot_f1()
    plot_x_v()
    plt.draw()
    plt.pause(1)
    # plt.savefig(f'images/{i}.png')
    plt.close()

    print(xg, f1(xg))

    x += v

    x = np.array([x[j] if is_position_valid(x[j]) else xl[j] for j in range(l)])

    xl = np.array([xl[j] if f1(xl[j]) < f1(x[j]) else x[j] for j in range(l)])

    f = np.array([f1(x[j]) for j in range(l)])

    xg = xg if f1(xg) < np.min(f) else np.copy(x[np.argmin(f), :])

