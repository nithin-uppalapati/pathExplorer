import numpy as np

def euc_dist(a,b):
    res = (a[0]-b[0])**2 + (a[1]-b[1])**2
    res = np.sqrt(res)
    return res

def ang_calc(a,b):          # have to use complex numbers to do the sign angle thing | vectors won't work
    res = np.dot(a,b)
    A = np.linalg.norm(a)
    B = np.linalg.norm(b)
    res = res / (A*B)
    return res



def dist_ang_calctor(data_points, offset_angle):            # n-points has n-1 edges and n-2 turns
    dist_angl = []

    for i in range(len(in_data)-1):
        dist_angl.append()


    return dist_angl


def drunken_state():
    chaotic_motion = []
    return chaotic_motion