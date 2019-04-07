import numpy as np
import copy
import exceptions as exc


def mutation(G, p: float):
    if (p < 0) | (p > 1):
        pass
        # raise exc.BadArgument()
    s_mut = 0
    r, c = G.shape
    '''
    g_mut = np.empty(G.shape, dtype=int)
    for i in range(r):
        for j in range(c):
            g_mut[i, j] = G[i, j]
    # '''
    g_mut = copy.deepcopy(G)

    for i in range(r):
        for j in range(c):
            tmp = np.random.rand()
            if tmp < p:
                g_mut[i][j] = 1 - g_mut[i][j]
                s_mut += 1
    return g_mut, s_mut


def crossover(G, Mlist, Flist):
    r, c = G.shape
    m = Mlist.size
    if r % 2 == 1 or 2 * m != r or Flist.size != m:
        return G
    Gcros = np.empty((r, c), dtype=int)
    for i in range(r):
        for j in range(c):
            Gcros[i, j] = G[i, j]
    for i in range(m):
        tmp = np.random.randint(1, c+1)
        for j in range(tmp):
            Gcros[Mlist[i], j] = G[Flist[i], j]
            Gcros[Flist[i], j] = G[Mlist[i], j]

    return Gcros
