import matplotlib
matplotlib.use('TkAgg')
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from datetime import datetime
from tkinter import *


class Details(Toplevel):
    def __init__(self, shutter=None):
        super().__init__()

        self.name = StringVar()
        self.name.set(shutter.get_name())

        self.title("Zonnescherm: " + self.name.get())
        self.config(bg="ghost white")

        testLabel = Label(self, textvariable=self.name, font=("Calibri", 20), bg="ghost white")
        testLabel.pack()

        # Temperature graph
        graph = Graph(self, shutter)
        graph.pack(side="left")

        # Settings menu
        settings = Settings(self, shutter)
        settings.config(bg="ghost white")
        settings.pack(side="left", padx=10)


class Graph(Frame):
    """
    Graph class that creates a linegraph and updates every 40 seconds
    Source: https://pythonprogramming.net/how-to-embed-matplotlib-graph-tkinter-gui/
    """
    def __init__(self, parent=None, shutter=None):
        super().__init__(parent)
        self.config(bg="ghost white")
        self.shutter = shutter

        f = Figure(figsize=(6, 6), dpi=100, facecolor='#f8f8ff')
        self.ax = f.add_subplot(111)

        # Sets for the plot
        self.timeset = []
        self.valueset = []

        self.ax.clear()
        self.ax.set_ylabel("Temperatuur in °C")
        self.ax.plot(self.timeset, self.valueset)

        # The graph magic
        self.canvas = FigureCanvasTkAgg(f, self)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side="bottom", fill="both", expand=True)

        # Start 40 second update loop
        self.update_graph()

    def update_graph(self):
        # Append new value to plots
        self.timeset.append(datetime.now().strftime('%H:%M:%S'))
        self.valueset.append(self.shutter.get_temp())

        # If there is more than 5 time entries, remove the oldest value
        if len(self.timeset) > 5:
            self.timeset.remove(self.timeset[0])
            self.valueset.remove(self.valueset[0])

        # Redraw the graph
        self.ax.clear()
        self.ax.set_title("Temperatuur over de tijd")
        self.ax.set_ylabel("Temperatuur in °C")
        self.ax.set_xticklabels(self.timeset, rotation='45')
        self.ax.plot(self.timeset, self.valueset)

        self.canvas.draw_idle()

        self.after(40000, self.update_graph)


class Settings(Frame):
    def __init__(self, parent=None, shutter=None):
        super().__init__(parent)
        self.parent = parent
        self.shutter = shutter

        # Current settings
        self.v_name = StringVar()
        self.v_name.set(shutter.get_name())
        self.v_ths_temp = StringVar()
        self.v_ths_temp.set(shutter.get_ths_temp())
        self.v_ths_dist = StringVar()
        self.v_ths_dist.set(shutter.get_ths_dist())

        # Create entry fields to write settings in
        e_name = Entry(self, textvariable=self.v_name)
        e_name.grid(row=0, column=1, pady=5)
        e_ths_temp = Entry(self, textvariable=self.v_ths_temp)
        e_ths_temp.grid(row=1, column=1, pady=5)
        e_ths_dist = Entry(self, textvariable=self.v_ths_dist)
        e_ths_dist.grid(row=2, column=1, pady=5)

        # Labels for entry fields
        l_name = Label(self, text="Zonnescherm naam", bg="ghost white")
        l_name.grid(row=0, column=0, padx=5, sticky="w")
        l_ths_temp = Label(self, text="Openingstemperatuur", bg="ghost white")
        l_ths_temp.grid(row=1, column=0, padx=5, sticky="w")
        l_ths_dist = Label(self, text="Openingsafstand", bg="ghost white")
        l_ths_dist.grid(row=2, column=0, padx=5, sticky="w")

        b_apply = Button(self, text="Opslaan", command=self.click)
        b_apply.grid(row=3, column=0)

    def click(self):
        if self.v_name.get() != self.shutter.get_name():
            self.shutter.set_name(self.v_name.get())
            self.parent.name.set(self.v_name.get())

        if self.v_ths_temp.get() != self.shutter.get_ths_temp():
            self.shutter.set_ths_temp(self.v_ths_temp.get())

        if self.v_ths_dist.get() != self.shutter.get_ths_dist():
            self.shutter.set_ths_dist(self.v_ths_dist.get())
