import kivy
# kivy.require('1.11.1')
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.graphics import Line , Color

first = 1
cordinates = []

def chill():
    cordinates = []
# cord = [100,100,200,200,500,500,700,700]

class MyFloatLayout(FloatLayout):
    # first = 1
    def start(self):
        print("Hi")
    def down(self,touch):
        print("first",first)
        if first == 1:
            with self.canvas:
                Color(1, 0, 0)
                d = 0
                if touch.x + 288 <= 290:
                    d = 290
                else:
                    d = touch.x + 288
                    touch.ud["line"] = Line(points = (d, touch.y),width=5)
                    cordinates.append(d)
                    cordinates.append(touch.y) 

    def move(self,touch):
        print("first",first)
        if first == 1:
            d = 0
            if touch.x + 288 <= 290:
                d = 290
            else:
                d = touch.x + 288
            touch.ud["line"].points += (d, touch.y)
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







class DrawingApp(App):
    def build(self):
        return MyFloatLayout()


DrawingApp().run()