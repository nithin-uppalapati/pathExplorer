import kivy
# import polyprox
import rdp
import time
from kivy.core.window import Window
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.graphics import Line , Color
import serial
import numpy as np
ser = serial.Serial('COM3',9600,timeout=1)
# ser = serial.Serial('/dev/cu.pathExplorer',9600,timeout=1)
size = 1024
first = 1
cordinates = []
cord = []
manual = 0

def approximation(z):
    V = []
    for i in range(0, len(z)):
        if (i%2)==0:
            V.append([z[i],z[i+1]])

    V=np.array(V)
    G=V.copy()
    epsilon = 50.0
    G_rdp = rdp.rdp(G, epsilon)
    # print(G_rdp)
    return G_rdp
    # return 0

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
    global cord
    cord = []
    cordinates = []
    print("length",len(cordinates))



class MyFloatLayout(FloatLayout):

    def top(self):
        if(manual == 1):
            # send("MF")
            ser.write(b"MF")
            # send(["M","F"])
    def buttonrelease(self):
        if(manual == 1):
            # send("MC")
            ser.write(b"MC")
            # send(["M","C"])

    def botm(self):
        if(manual == 1):
            ser.write(b"MB")
            # send(["M","B"])

    def left(self):
        if(manual == 1):
            # send("ML")
            ser.write(b"ML")
            # send(["M","L"])

    def right(self):
        if(manual == 1):
            # send("MR")
            ser.write(b"MR")
            # send(["M","R"])

    def manualset(self):
        global manual
        if manual == 0:
            manual = 1
            ser.write(b"M")
        else:
            manual = 0
            ser.write(b"Q")



    def stop(self):
        ser.write(b"Q")

    def testing(self):
        global cord
        cord=[]
        # print("length cord" , len(cordinates))
        cordi = approximation(cordinates)
        for i in cordi:
            cord.append(i[0])
            cord.append(i[1])
        with self.canvas:
            Color(1, 0, 0)
            Line(points = cord,width=2)
        return

    def slide(self,*args):
        spd = int(args[1])+120
        ch = 'S'+ str(spd)
        ser.write(bytes(ch,"utf-8"))
        # print("speed",args[1])
    # first = 1

    def start(self):
        global cord
        cord=[]
        print("length cord" , len(cordinates))
        cordi = approximation(cordinates)
        for i in cordi:
            cord.append(i[0])
            cord.append(i[1])
        # cord = list(cordi)
        res = dist_ang_calctor(cordi,0)
        print("res = ",res)
        ser.write(b"P")
        time.sleep(2)
        # tempt(self,cord)
        # res = [b"P258",b"P81",b"P216"]
        sord = []
        track = 0
        for j,i in enumerate(res):
            i = int(i)
            print(i)
            i ="P" + str(i)
            ser.write(bytes(i,"utf-8"))
            # ser.write(b"P101")
            while(1):
                data = ser.readline(size)
                if(data):
                    print("data: ",data)
                    if(int(data.decode().strip()) == j):
                        track = j
                        # time.sleep(0.5)
                        break
                    if(int(data.decode().strip()) == -1):
                        track = int(track /2) 
                        for i in range(0,track+2):
                            sord.append(cordi[i][0])
                            sord.append(cordi[i][1])
                        with self.canvas:
                            Color(0, 1, 0)
                            Line(points = sord,width=2)
                            ser.write(b"Q")
                            return
            time.sleep(0.5)

        with self.canvas:
            Color(0, 1, 0)
            Line(points = cord,width=2, close=False)
        ser.write(b"Q")
        return




    def down(self,touch):
        # print("first",first)
        if first == 1:
            with self.canvas:
                Color(0, 0, 0)
                d = 0
                if touch.x + int(Window.size[0])*0.2  >= int(Window.size[0])*0.2 + 2:
                    d = touch.x + int(Window.size[0])*0.2 
                    touch.ud["line"] = Line(points = (d, touch.y),width=3.5)
                    cordinates.append(d)
                    cordinates.append(touch.y) 

    def move(self,touch):
        # print("first",first)
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
                # print("error")
                flag = 1
            if flag == 0:
                cordinates.append(d)
                cordinates.append(touch.y)


    def up(self,touch):
        print("RELEASED!",touch)
        first = 0
        # print("first",first)
        # cordinates = touch.ud["line"].points
        # touch.ud["line"].points = []
        # first = 0

    def clear(self):
        print("len",len(cordinates))
        with self.canvas:
            Color(1, 1, 1)
            Line(points = cordinates,width=3.5)
        with self.canvas:
            Color(1, 1, 1)
            Line(points = cord,width=2)
        chill()
        print("length",len(cordinates))







class DrawingApp(App):
    def build(self):
        return MyFloatLayout()


DrawingApp().run()