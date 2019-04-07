import numpy as np
import exceptions as exc


def Parents(N):
    mlist = np.random.randint(low=0, high=2*N, size=N)
    flist = np.random.randint(low=0, high=2*N, size=N)
    for i in range(N):
        while mlist[i] == flist[i]:
            flist[i] = int(np.random.randint(1, 2*N))
    return mlist, flist

def Adapt(periodic, N):
    if periodic.size != N:
        pass
        # raise exc.BadArgument()
    periodic2 = np.zeros(N)
    s = sum(periodic)
    #print(s)
    for i in range(N):
        periodic2[i] = periodic[i]/s
    #print(periodic2)
    #print(sum(periodic2))
    adaptability = np.zeros(N+1)
    adaptability[0] = 0
    for i in range(N):
        adaptability[i+1] = adaptability[i] + periodic2[i]
    adaptability[N] = 1
    # print("adaptability " + str(adaptability))
    num = np.zeros(N)
    for i in range(N):
        roll = np.random.random()
        # print("roll " + str(roll))
        j = 0
        while roll >= adaptability[j+1]:
            j += 1
        num[j] += 1
    return num