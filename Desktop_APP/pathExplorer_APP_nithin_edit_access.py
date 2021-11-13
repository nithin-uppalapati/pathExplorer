# kivy tutorial#1

from kivy.app import App
from kivy.uix.widget import Widget
from kivy.graphics import Line


# global_var = []

class DrawInput(Widget):
    def on_touch_down(self,touch):
        print(touch)
        with self.canvas:
            touch.ud["line"] = Line(points = (touch.x, touch.y), width=5)

    def on_touch_move(self,touch):
        # print(touch)
        touch.ud["line"].points += (touch.x, touch.y)

    def on_touch_up(self,touch):
        # print("RELEASED!",touch)
        print(touch.ud["line"].points)
        global global_var
        global_var = list(touch.ud["line"].points)
        # print(global_var)
        # print(type(global_var))
        # print(type(global_var[0]))
        # print("END-------!!!!!")

class SimpleKivy4(App):
    def build(self):
        # print("in build")
        return DrawInput()

if __name__ == "__main__":
    SimpleKivy4().run()


import polyprox
import numpy as np
import rdp
import time
import matplotlib.pyplot as plt

# ----- kivy exp
V=[]
# z= [316.0, 952.0, 330.0, 952.0, 364.0, 952.0, 380.0, 952.0, 416.0, 952.0, 454.0, 952.0, 496.0, 952.0, 538.0, 952.0, 596.0, 952.0, 648.0, 954.0, 684.0, 956.0, 726.0, 956.0, 744.0, 956.0, 760.0, 956.0, 770.0, 956.0, 774.0, 956.0, 776.0, 956.0, 778.0, 956.0, 778.0, 954.0, 778.0, 952.0, 778.0, 950.0, 782.0, 948.0, 784.0, 944.0, 792.0, 938.0000000000001, 796.0, 934.0, 806.0, 922.0, 808.0, 919.9999999999999, 814.0, 912.0, 818.0, 906.0, 830.0000000000001, 892.0000000000001, 836.0, 882.0, 840.0, 878.0, 856.0, 856.0, 864.0, 846.0000000000001, 874.0, 832.0, 884.0, 822.0000000000001, 896.0000000000001, 808.0, 903.9999999999999, 794.0, 911.9999999999999, 786.0, 918.0, 778.0, 924.0, 772.0, 927.9999999999999, 768.0, 930.0000000000001, 764.0, 932.0, 762.0, 934.0, 762.0, 934.0, 760.0, 936.0, 760.0, 936.0, 757.9999999999999, 936.0, 756.0, 936.0, 754.0000000000001, 936.0, 752.0, 936.0, 748.0, 936.0, 745.9999999999999, 936.0, 742.0000000000001, 936.0, 740.0, 936.0, 734.0, 936.0, 728.0, 938.0000000000001, 722.0, 938.0000000000001, 718.0000000000001, 938.0000000000001, 714.0, 938.0000000000001, 708.0000000000001, 938.0000000000001, 704.0, 938.0000000000001, 702.0, 938.0000000000001, 698.0, 938.0000000000001, 694.0, 938.0000000000001, 690.0, 938.0000000000001, 682.0, 938.0000000000001, 676.0, 938.0000000000001, 670.0, 938.0000000000001, 668.0, 938.0000000000001, 665.9999999999999, 938.0000000000001, 664.0, 938.0000000000001, 662.0000000000001, 938.0000000000001, 656.0, 938.0000000000001, 653.9999999999999, 936.0, 652.0, 936.0, 648.0, 936.0, 646.0, 934.0, 641.9999999999999, 932.0, 634.0, 930.0000000000001, 626.0000000000001, 930.0000000000001, 616.0, 927.9999999999999, 607.9999999999999, 926.0, 598.0, 926.0, 594.0, 924.0, 584.0, 919.9999999999999, 578.0, 918.0, 568.0000000000001, 914.0, 558.0, 910.0, 548.0, 906.0, 538.0, 900.0, 526.0, 894.0, 516.0000000000001, 884.0, 502.0, 876.0, 492.00000000000006, 869.9999999999999, 486.00000000000006, 858.0, 475.99999999999994, 850.0, 468.0, 842.0, 462.0, 834.0, 458.00000000000006, 827.9999999999999, 452.00000000000006, 818.0, 446.00000000000006, 811.9999999999999, 441.99999999999994, 808.0, 440.00000000000006, 798.0, 438.0, 792.0, 434.00000000000006, 782.0, 432.0, 774.0, 429.99999999999994, 762.0, 428.0, 758.0, 426.0, 750.0, 426.0, 742.0, 426.0, 732.0, 426.0, 720.0, 426.0, 710.0, 426.0, 698.0, 426.0, 690.0, 426.0, 682.0, 428.0, 674.0, 429.99999999999994, 666.0, 429.99999999999994, 658.0, 434.00000000000006, 648.0, 435.99999999999994, 638.0, 440.00000000000006, 630.0, 444.0, 620.0, 447.99999999999994, 612.0, 452.00000000000006, 604.0, 456.0, 596.0, 459.99999999999994, 588.0, 464.00000000000006, 578.0, 472.0, 570.0, 475.99999999999994, 562.0, 481.99999999999994, 554.0, 487.99999999999994, 548.0, 492.00000000000006, 544.0, 498.00000000000006, 540.0, 502.0, 536.0, 508.0, 532.0, 516.0000000000001, 530.0, 522.0000000000001, 526.0, 530.0, 524.0, 536.0, 522.0, 540.0, 522.0, 542.0, 522.0, 546.0, 520.0, 550.0, 520.0, 552.0, 518.0, 560.0, 516.0, 570.0, 514.0, 578.0, 514.0, 586.0, 514.0, 592.0, 514.0, 600.0, 514.0, 606.0, 514.0, 614.0, 514.0, 619.9999999999999, 516.0, 624.0, 518.0, 628.0, 520.0, 630.0, 524.0, 634.0, 528.0, 638.0000000000001, 532.0, 641.9999999999999, 536.0, 646.0, 540.0, 650.0000000000001, 542.0, 652.0, 546.0, 653.9999999999999, 548.0, 656.0, 552.0, 658.0, 556.0, 660.0, 560.0, 662.0000000000001, 566.0, 665.9999999999999, 568.0, 665.9999999999999, 574.0, 665.9999999999999, 580.0, 668.0, 584.0, 670.0, 590.0, 670.0, 596.0, 672.0000000000001, 600.0, 672.0000000000001, 608.0, 672.0000000000001, 614.0, 672.0000000000001, 622.0, 672.0000000000001, 630.0, 672.0000000000001, 636.0, 672.0000000000001, 644.0, 672.0000000000001, 650.0, 672.0000000000001, 656.0, 670.0, 658.0, 670.0, 664.0, 668.0, 670.0, 665.9999999999999, 680.0, 664.0, 688.0, 662.0000000000001, 696.0, 660.0, 706.0, 658.0, 712.0, 656.0, 718.0, 653.9999999999999, 724.0, 652.0, 732.0, 650.0000000000001, 740.0, 648.0, 750.0, 646.0, 756.0, 644.0, 758.0, 644.0, 762.0, 641.9999999999999, 768.0, 641.9999999999999, 770.0, 641.9999999999999, 772.0, 641.9999999999999, 774.0, 640.0, 776.0, 640.0, 780.0, 640.0, 784.0, 638.0000000000001, 788.0, 638.0000000000001, 792.0, 636.0, 798.0, 636.0, 803.9999999999999, 636.0, 814.0, 636.0, 824.0, 636.0, 836.0, 636.0, 848.0, 636.0, 858.0, 636.0, 868.0, 636.0, 880.0000000000001, 636.0, 894.0, 636.0, 906.0, 636.0, 914.0, 638.0000000000001, 926.0, 640.0, 936.0, 644.0, 946.0000000000001, 648.0, 958.0, 652.0, 972.0000000000001, 658.0, 982.0, 662.0000000000001, 996.0000000000001, 665.9999999999999, 1008.0, 668.0, 1019.9999999999999, 672.0000000000001, 1028.0, 677.9999999999999, 1038.0, 682.0, 1044.0, 684.0000000000001, 1050.0, 687.9999999999999, 1056.0, 692.0, 1062.0, 696.0000000000001, 1070.0, 704.0, 1076.0, 710.0, 1080.0, 716.0, 1082.0, 723.9999999999999, 1084.0, 730.0000000000001, 1088.0, 744.0, 1090.0, 748.0, 1092.0, 762.0, 1092.0, 768.0, 1092.0, 776.0000000000001, 1092.0, 784.0, 1092.0, 798.0, 1092.0, 808.0, 1090.0, 820.0, 1086.0, 832.0, 1082.0, 842.0, 1078.0, 849.9999999999999, 1072.0, 864.0, 1066.0, 873.9999999999999, 1060.0, 884.0, 1054.0, 894.0, 1050.0, 904.0, 1044.0, 912.0, 1038.0, 919.9999999999999, 1032.0, 928.0, 1022.0000000000001, 940.0, 1014.0, 952.0, 1010.0, 960.0, 1002.0, 970.0, 996.0000000000001, 980.0, 988.0000000000001, 988.0, 982.0, 996.0, 976.0, 1002.0, 969.9999999999999, 1006.0, 964.0, 1011.9999999999999, 960.0, 1018.0000000000001, 953.9999999999999, 1022.0, 950.0, 1026.0, 944.0, 1032.0, 936.0, 1038.0, 927.9999999999999, 1044.0, 918.0, 1050.0, 910.0, 1058.0, 902.0, 1064.0, 892.0, 1068.0, 882.0, 1074.0, 874.0, 1080.0, 864.0, 1084.0, 856.0, 1090.0, 842.0, 1094.0, 832.0, 1098.0, 816.0, 1102.0, 808.0, 1106.0, 803.9999999999999, 1108.0, 796.0, 1110.0, 784.0, 1112.0, 776.0, 1112.0, 766.0, 1112.0, 758.0, 1112.0, 748.0, 1112.0, 740.0, 1112.0, 734.0, 1112.0, 728.0, 1112.0, 722.0, 1112.0, 716.0, 1112.0, 710.0, 1110.0, 704.0, 1108.0, 700.0, 1104.0, 694.0, 1100.0, 686.0, 1094.0, 678.0, 1090.0, 672.0, 1084.0, 666.0, 1078.0, 662.0, 1072.0, 656.0, 1066.0, 652.0, 1062.0, 650.0, 1058.0, 646.0, 1052.0, 642.0, 1044.0, 638.0, 1034.0, 632.0, 1020.0, 626.0, 1006.0, 620.0, 988.0, 614.0, 974.0, 606.0, 956.0, 600.0, 942.0, 594.0, 922.0, 588.0, 907.9999999999999, 580.0, 892.0000000000001, 574.0, 870.0, 568.0, 852.0, 562.0, 836.0, 554.0, 814.0, 548.0, 798.0, 542.0, 776.0000000000001, 536.0, 754.0000000000001, 528.0, 730.0000000000001, 522.0, 708.0000000000001, 516.0, 686.0, 512.0, 665.9999999999999, 505.99999999999994, 650.0000000000001, 498.00000000000006, 626.0000000000001, 492.0, 604.0000000000001, 490.00000000000006, 594.0, 480.0, 556.0, 476.0, 533.9999999999999, 472.0, 510.00000000000006, 466.0, 487.99999999999994, 459.99999999999994, 462.0, 455.99999999999994, 435.99999999999994, 450.0, 412.00000000000006, 446.0, 392.0, 442.0, 374.0, 436.00000000000006, 355.99999999999994, 432.0, 336.00000000000006, 430.0, 320.00000000000006, 428.0, 302.00000000000006, 426.0, 288.0, 422.0, 278.0, 420.0, 262.00000000000006, 418.0, 254.0, 416.0, 245.99999999999994, 416.0, 238.00000000000003, 413.99999999999994, 236.0, 413.99999999999994, 232.00000000000003, 412.0, 232.00000000000003]
z = global_var

# loop_len = int(len(z)/2)
for i in range(0, len(z)):
    if (i%2)==0:
        V.append([z[i],z[i+1]])

V=np.array(V)
G=V.copy()

    
# -----


## Min-num problem
# Set maximum allowable error
epsilon = 100.0

# Time execution of min_num method provided in this package
t_start = time.time()
G_pp = polyprox.min_num(G, epsilon)
t_exec_pp = time.time() - t_start

# Time execution of Hirschmann's implementation
t_start = time.time()
G_rdp = rdp.rdp(G, epsilon)
t_exec_rdp = time.time() - t_start

print("Same result as rdp: {}".format(np.array_equal(G_rdp, G_pp)))
print("Speedup: {:.2f}%".format((t_exec_rdp - t_exec_pp) / t_exec_rdp * 100.0))

plt.plot(G[:, 0], G[:, 1], label="Groundtruth")
plt.plot(G_pp[:, 0], G_pp[:, 1], "g--o", label="Approximation")
# plt.scatter(G[:, 0], G[:, 1], label="Groundtruth")
plt.legend()
plt.show()

## Min-e problem
# Number of points by which to approximate
# m = 10
# G_pp = polyprox.min_e(G, m)
# t_exec_pp = time.time() - t_start

# print("Requested: {} Got: {}".format(m, len(G_pp) - 2))

# plt.plot(G[:, 0], G[:, 1], label="Groundtruth")
# plt.plot(G_pp[:, 0], G_pp[:, 1], "r--o", label="Approximation")
# plt.legend()
# plt.show()