import time
from tkinter import *

from matplotlib.dates import minutes

from frontend.main import Main
from frontend.settings import Settings

from time import *
from datetime import *

import matplotlib
matplotlib.use('TkAgg')
from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib import style
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg)
from matplotlib.figure import Figure

import warnings
import matplotlib.cbook
warnings.filterwarnings("ignore", category=matplotlib.cbook.mplDeprecation)


class Page2(Main):

    def __init__(self, main, shutter):
        super().__init__(main)
        self.main = main
        self.shutter = shutter

        def newpage(event):
            root3 = Toplevel(main)
            my2 = Settings(root3)

        main.configure(background='grey')

        title = Label(main, bg='grey', text='Zonnescherm-' + shutter.name)
        title.grid(column=1, row=0)

        label = Label(main, bg='grey', text='TEMPERATUUR')
        label.grid(column=0, row=1, padx=100, pady=(100, 10))

        label = Label(main, bg='grey', text='STATUS')
        label.grid(column=1, row=1, padx=100, pady=(100, 10))

        box = Label(main, bg='white', text='DICHT \n GAAT DICHT.. \n GAAT OPEN.. \n OPEN')
        box.grid(column=1, row=4, ipadx=105, ipady=105, padx=30)

        box = Label(main, bg='white', text='ZONNIG \n BEWOLKT \n LUX:' + str(shutter.light))
        box.grid(column=2, row=4, ipadx=115, ipady=115, padx=30)

        label = Label(main, bg='grey', text='LICHT')
        label.grid(column=2, row=1, padx=100, pady=(100, 10))

        self.up = Button(main, text='↑', highlightbackground='grey')
        self.up.grid(row=1, column=1, sticky='e', padx=140, pady=(0, 100))

        self.up = Button(main, text='↓', highlightbackground='grey')
        self.up.grid(row=1, column=1, sticky='w', padx=140, pady=(0, 100))

        self.settings = Button(main, text='INSTELLINGEN', highlightbackground='grey')
        self.settings.grid(row=5, column=2)
        self.settings.bind('<Button-1>', newpage)

        self.setting = Label(main, bg='grey', text='Het zonnescherm werkt op dit moment: ' + shutter.setting)
        self.setting.grid(row=5, column=0)

        fig = plt.figure(figsize=(3, 3), dpi=100)
        # fig = Figure(figsize=(3, 3), dpi=100)

        # now = datetime.now()
        # start = datetime.now()

        # def temp_list():
        #     while True:
        #         sleep(1)
        #         next_second = datetime.now()
        #         print(start.second, next_second.second)
        #         if next_second.second == start.second:
        #             print('pulse')
        #             file = open('example.txt', 'a')
        #             file.writelines(str(next_second) + str(shutter.temp))
        #             break
        #
        # temp_list()

        # def temp_list(secondCnt):
        #     startTime = time.clock()
        #     ellapsed = 0
        #     for x in range(0, secondCnt, 1):
        #         print("loop cycle time: %f, seconds cnt: %02d" % (ellapsed, x))
        #         ellapsed = 1 - (time.clock() - startTime)
        #         time.sleep(ellapsed)
        #         startTime = time.clock()
        #
        # temp_list(60)

        # def temp_list():
        #     file = open('example.txt', 'a')
        #     while True:
        #         sleep(1)
        #         file.writelines(str(datetime.now()))
        # temp_list()

        def animate(i):
            style.use('fivethirtyeight')
            ax1 = fig.add_subplot(1, 1, 1)
            # 1,2,1
            graph_data = open('example.txt', 'r').read()
            # graph_data = temp_list
            lines = graph_data.split('\n')
            xs = []
            ys = []
            for line in lines:
                if len(line) > 1:
                    x, y = line.split(',')
                    xs.append(x)
                    ys.append(y)
            ax1.clear()
            ax1.plot(xs, ys)

            canvas = FigureCanvasTkAgg(fig, main)
            canvas.get_tk_widget().grid(row=4, padx=(55, 30))
            ani = FuncAnimation(fig, animate, interval=1000)
            fig.show()







