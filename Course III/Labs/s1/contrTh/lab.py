from __future__ import generators

import numpy as np
from scipy.integrate import odeint
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.gca(projection='3d')

# параметри моделі
a1_ = 0
a2_ = 0
b1_ = 1
b2_ = 1
myu = 1
sigma = 1
T = 10
count = 101
r = 1
slices = 5
line_plot_step = 0.01

a1 = lambda t: a1_
a2 = lambda t: a2_
b1 = lambda t: b1_
b2 = lambda t: b2_

#
def pend(y, t):
    p1, p2, p12 = y
    dydt = [1 + 2 * a1(t)*p1 - p1**2 + 2 * b1(t)*p12 - p12**2,
            1 + 2 * a2(t)*p2 - p2**2 + 2 * b2(t)*p12 - p12**2,
            b2(t)*p1 + b1(t)*p2 + p12 * (a1(t) + a2(t) - p1 - p2)]
    return dydt

#
y0 = [sigma**2, myu**2, 0.0]
t = np.linspace(0, T, count)
sol = odeint(pend, y0, t)


# plt.plot(t, sol[:, 0] * sol[:, 2], 'b', label='p1(t)')
# plt.plot(t, sol[:, 1] ** 2, 'g', label='p2(t)')
# # plt.plot(t, sol[:, 2], 'r', label='p3(t)')
# plt.legend(loc='best')
# plt.xlabel('t')
# plt.grid()
# plt.show()

#
p1 = sol[:, 0]
p2 = sol[:, 1]
p12 = sol[:, 2]

#
# print(len(sol[:, 0]))
z1_boundary = np.linspace(-r, r, 2*count-1)
z2_boundary = np.linspace(-r, r, 2*count-1)
t_boundary = np.linspace(0, T, count)

#
fig = [[[(t_boundary[t], z1, z2) for z2 in z2_boundary if p1[t]*z1**2 + 2*p12[t]*z1*z2 +
        p2[t]*z2**2 <= r**2] for z1 in z1_boundary] for t in range(count)]

# <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# convex hull (Graham scan by x-coordinate) and diameter of a set of points


def orientation(p, q, r):
    '''Return positive if p-q-r are clockwise, neg if ccw, zero if colinear.'''
    return (q[1] - p[1]) * (r[0] - p[0]) - (q[0] - p[0]) * (r[1] - p[1])


def hulls(Points):
    '''Graham scan to find upper and lower convex hulls of a set of 2d points.'''
    U = []
    L = []
    Points.sort()
    for p in Points:
        while len(U) > 1 and orientation(U[-2], U[-1], p) <= 0: U.pop()
        while len(L) > 1 and orientation(L[-2], L[-1], p) >= 0: L.pop()
        U.append(p)
        L.append(p)
    return U, L


def rotatingCalipers(Points):
    '''Given a list of 2d points, finds all ways of sandwiching the points
between two parallel lines that touch one point each, and yields the sequence
of pairs of points touched by each pair of lines.'''
    U, L = hulls(Points)
    i = 0
    j = len(L) - 1
    while i < len(U) - 1 or j > 0:
        yield U[i], L[j]
        # if all the way through one side of hull, advance the other side
        if i == len(U) - 1:
            j -= 1
        elif j == 0:
            i += 1
        # still points left on both lists, compare slopes of next hull edges
        # being careful to avoid divide-by-zero in slope calculation
        elif (U[i + 1][1] - U[i][1]) * (L[j][0] - L[j - 1][0]) > \
                (L[j][1] - L[j - 1][1]) * (U[i + 1][0] - U[i][0]):
            i += 1
        else:
            j -= 1


def diameter(Points):
    '''Given a list of 2d points, returns the pair that's farthest apart.'''
    diam, pair = max([((p[0] - q[0])** 2 + (p[1] - q[1])** 2, (p, q))
                      for p, q in rotatingCalipers(Points)])
    return pair
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

def line(x0, p10, p20):
    return ( p20[1] + (p20[0] - x0) * (p20[1] - p10[1]) / (p20[0] - p10[0]) )

def plot_slice(t):
    x1_t = []
    x2_t = []
    # p10 = np.array(p1)
    # p120 = np.array(p12)
    # p20 = np.array(p2)
    for z1_t in z1_boundary:
        for z2_t in z2_boundary:
            if (p1[t]*z1_t**2 + 2*p12[t]*z1_t*z2_t + p2[t]*z2_t**2 <= r**2):
                x1_t.append(z1_t)
                x2_t.append(z2_t)
    # x1_t = np.array(x1_t)
    # x2_t = np.array(x2_t)
    points = []
    for i in range(len(z1_boundary)):
        points.append([x1_t[i], x2_t[i]])
    # diam_points = diameter(points)
    # p11 = diam_points[0]
    # p22 = diam_points[1]
    # print(p11)
    # print(p22)
    plt.plot(x1_t, x2_t)
    # plt.plot(x1_t, x2_t, z1_boundary, line(z1_boundary, p11, p22))
    # alpha = np.arctan( (p11[1] - p22[1]) / (p11[0] - p22[0]) )
    capt = "t = " + str(t_boundary[t]) + '\n' # + "alpha = " + str(alpha)
    plt.title(capt)
    plt.show()


#
# '''
x1_ax = []
x2_ax = []
t_ax = []
# print(len(fig[0][0][0]))
for i in range(len(fig)):
    for j in range(len(fig[i])):
        for k in range(len(fig[i][j])):
            t_ax.append(fig[i][j][k][0])
            x1_ax.append(fig[i][j][k][1])
            x2_ax.append(fig[i][j][k][2])
# ax.plot(x1_ax, x2_ax, t_ax)
plt.plot(x1_ax, x2_ax, t_ax)
# plt.grid()
plt.show()
# '''

#
t_slices = []
tmp = 0
step = count // (slices - 1)
for i in range(slices - 1):
    t_slices.append(tmp)
    tmp += step
t_slices.append(count - 1)
# t_slices = np.array(t_slices, dtype=int)
for t_slice in t_slices:
    plot_slice(t_slice)

