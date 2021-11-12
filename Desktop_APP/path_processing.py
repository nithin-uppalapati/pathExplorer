import numpy as np

def euc_dist(a,b):
    res = (a[0]-b[0])**2 + (a[1]-b[1])**2
    res = np.sqrt(res)
    return res

def ang_calc(a,b,c):          # have to use complex numbers to do the sign angle thing | vectors won't work
    Y1 = b[1] - a[1]
    X1 = b[0] - a[0]
    Y2 = - b[1] + c[1]
    X2 = - b[0] + c[0]
    ang1 = np.degrees(np.arctan2(Y1,X1))
    ang2 = np.degrees(np.arctan2(Y2,X2))
    res = ang2 - ang1
    return res


def dist_ang_calctor(data, offset_angle):            # n-points has n-1 edges and n-2 turns
    dist_angl = []
    for i in range(len(data)-1):
        dist_angl.append(euc_dist(data[i],data[i+1]))
        if i <= len(in_data)-3
            dist_angl.append(ang_calc(data[i],data[i+1],data[i+2]))


    return dist_angl


def drunken_state():
    chaotic_motion = []
    return chaotic_motion
