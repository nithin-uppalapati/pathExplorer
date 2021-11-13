import kivy
import polyprox
import rdp
import time
from kivy.core.window import Window
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.graphics import Line , Color
import numpy as np

first = 1
cordinates = []


def approximation(z):
    V = []
    for i in range(0, len(z)):
        if (i%2)==0:
            V.append([z[i],z[i+1]])

    V=np.array(V)
    G=V.copy()
    epsilon = 50.0
    t_start = time.time()
    G_pp = polyprox.min_num(G, epsilon)
    t_exec_pp = time.time() - t_start
    t_start = time.time()
    G_rdp = rdp.rdp(G, epsilon)
    t_exec_rdp = time.time() - t_start
    return G_pp

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
        if i <= len(data)-3 :
            dist_angl.append(ang_calc(data[i],data[i+1],data[i+2]))


    return dist_angl

def chill():
    global cordinates
    cordinates = []
    print("length",len(cordinates))


    # cord = [100,100,200,200,500,500,700,700]

class MyFloatLayout(FloatLayout):

    def slide(self,*args):
        print("speed",args[1])
    # first = 1
    def start(self):
        print("length cord" , len(cordinates))
        cord = approximation(cordinates)
        res = dist_ang_calctor(cord,0)
        print("len and angles")
        print(res)
    def down(self,touch):
        print("first",first)
        if first == 1:
            with self.canvas:
                Color(1, 0, 0)
                d = 0
                if touch.x + int(Window.size[0])*0.2  >= int(Window.size[0])*0.2 + 2:
                    d = touch.x + int(Window.size[0])*0.2 
                    touch.ud["line"] = Line(points = (d, touch.y),width=5)
                    cordinates.append(d)
                    cordinates.append(touch.y) 

    def move(self,touch):
        print("first",first)
        flag = 0
        if first == 1:
            d = 0
            if touch.x + int(Window.size[0])*0.2 <= int(Window.size[0])*0.2 + 2:
                d = int(Window.size[0])*0.2 + 2
            else:
                d = touch.x + int(Window.size[0])*0.2 
            try:
                touch.ud["line"].points += (d, touch.y)
            except:
                print("error")
                flag = 1
            if flag == 0:
                cordinates.append(d)
                cordinates.append(touch.y)


    def up(self,touch):
        print("RELEASED!",touch)
        first = 0
        print("first",first)
        # cordinates = touch.ud["line"].points
        # touch.ud["line"].points = []
        # first = 0

    def clear(self):
        print("len",len(cordinates))
        with self.canvas:
            Color(1, 1, 1)
            Line(points = cordinates,width=5)
        chill()
        print("length",len(cordinates))







class DrawingApp(App):
    def build(self):
        return MyFloatLayout()


DrawingApp().run()