import numpy as np
import scipy.integrate
import matplotlib.pyplot as pp
import mpl_toolkits.mplot3d

a=2 #prey's growth coeff in case of predator's absence
b=4 #prey's mortality rate in case of interaction with predator
c=3 #predator's mortality rate
d=6 #predator's growth coef
e=1
# N[0] prey population size, N[1] predator  population size
def df_dt (f,t,a,b,c,d):
    x,y=f
    return np.array([a * x - b * x * y, -c * y + d * x * y])

#equillibrium points -- solution constant in time
trivial_eq = np.array([0, 0])
non_trivial_eq = np.array([c/d, a/b])

#stability


def jacoby_system(f):
    x,y=f
    return np.array([[a-b*y, -b*x], [d*y, -c+d*x]])

#trivial state is unstable
l1, l2 = np.linalg.eigvals(jacoby_system(trivial_eq))
print(l1, l2)

#both eigenvalues are complex, ths we cant establish stability of nontrivial solution
p1, p2 = np.linalg.eigvals(jacoby_system(non_trivial_eq))
print(p1, p2)

t=np.linspace(0,30,1500)
Solution=scipy.integrate.odeint(df_dt,[5,2], t,args=(a,b,c,d))


pp.plot(t, Solution[:,0],label="x(t)")
pp.plot(t,Solution[:,1],label="y(t)")
pp.xlabel('time')
pp.ylabel('population')
pp.legend()
pp.title('Evolution of density of both population')
pp.show()

eps_nbhood=np.linspace(0.1,0.5,7)
for i in eps_nbhood:
    Initial=non_trivial_eq*i;
    Solution = scipy.integrate.odeint(df_dt, Initial, t, args=(a, b, c, d))
    pp.plot(Solution[:,0],Solution[:,1])

density=60
x_sp=np.linspace(0,4,density)
y_sp=np.linspace(0,4,density)
x_pr,y_pr=np.meshgrid(x_sp, y_sp)
dx_pr,dy_pr=df_dt([x_sp,y_sp],t, a,b,c,d)
pp.quiver(x_pr,y_pr,dx_pr,dy_pr)

pp.show()

pp.figure()
pp.axes(projection='3d');
for i in eps_nbhood:
    Initial=non_trivial_eq*i;
    Solution = scipy.integrate.odeint(df_dt, Initial, t, args=(a, b, c, d))
    pp.plot(Solution[:,0],Solution[:,1],t)
pp.show()


#with interaction among preys
def df_dt (f,t,a,b,c,d):
    x,y=f
    return np.array([a * x - b * x * y-e*x**2, -c * y + d * x * y])


