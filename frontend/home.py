from tkinter import *
from main import Main
from page2 import Page2
from shutter import Shutter


class Home(Main):
    def __init__(self, main):
        super().__init__(main)
        self.main = main
        self.active_shutters = []

        def open(event, shutter):
            root2 = Toplevel(main)
            my = Page2(root2, shutter)

        def helpButton():
            # fix, aparte functie
            main.update_idletasks()
            width = 1150
            height = 650
            x = (main.winfo_screenwidth() // 2) - (width // 2)
            y = (main.winfo_screenheight() // 2) - (height // 2)
            top = Toplevel(main)
            top.title('Help')
            top.geometry('{}x{}+{}+{}'.format(200, 200, x + 950, y))

        def up():
            if self.active_shutters.__len__() > 0:
                print('Up:' + str(self.active_shutters))
            else:
                print('Er zijn geen schermen geselecteerd')

        def down():
            if self.active_shutters.__len__() > 0:
                print('Up:' + str(self.active_shutters))
            else:
                error = Label(main, text='*Er zijn geen schermen geselecteerd', bg='grey')
                error.grid(row=1, column=1, sticky='e', padx=10)

        def all_up():
            print('All up:')
            for shutter in shutters:
                print(shutter.name)

        def all_down():
            print('All up:')
            for shutter in shutters:
                print(shutter.name)

        def myfunction(event):
            canvas.configure(scrollregion=canvas.bbox("all"), width=1075, height=500)

        shutters = [
            Shutter('1', 'DICHT', 21, 188, 'Automatisch', 10, 10),
            Shutter('2', 'DICHT', 22, 250, 'Automatisch', 10, 10),
            Shutter('3', 'DICHT', 23, 175, 'Automatisch', 10, 10),
            Shutter('4', 'DICHT', 20, 200, 'Automatisch', 10, 10),
            Shutter('5', 'DICHT', 20, 220, 'Automatisch', 10, 10),
            Shutter('6', 'DICHT', 19, 180, 'Automatisch', 10, 10),
            Shutter('7', 'DICHT', 23, 190, 'Automatisch', 10, 10),
            Shutter('8', 'DICHT', 22, 195, 'Automatisch', 10, 10),
            Shutter('9', 'DICHT', 21, 200, 'Automatisch', 10, 10),
            Shutter('10', 'DICHT', 20, 210, 'Automatisch', 10, 10)
            ]

        # Page2.temp_list()

        def data():
            # column
            i = 0
            # row
            j = 2
            x = 3

            for shutter in shutters:
                if i == x:
                    j += 5
                    i = 0
                label = Checkbutton(frame, bg='grey', text="Zonnescherm " + str(shutter.name))
                label.grid(column=i, row=j, padx=100, pady=(30, 10))
                label.bind('<Button-1>', lambda event, arg=shutter: state(event, arg))
                box = Label(frame, bg='white', text='Status:' + str(shutter.state) + '\n Temperatuur:' + str(shutter.temp) + '°C' + '\n Lichtsterkte:' + str(shutter.light) + '\n')
                box.grid(row=j+3, column=i, ipadx=100, ipady=100, padx=(20, 10))
                box.bind('<Button-1>', lambda event, arg=shutter: open(event, arg))
                i += 1

        def state(event, shutter):
            self.active_shutters.append(shutter.name)
            # return self.active_shutters

        myframe = Frame(main, relief=GROOVE, width=50, height=100, bd=1)
        myframe.place(x=25, y=100)

        canvas = Canvas(myframe)
        frame = Frame(canvas, bg='grey')
        myscrollbar = Scrollbar(myframe, orient="vertical", command=canvas.yview)
        canvas.configure(yscrollcommand=myscrollbar.set, background='grey', highlightbackground='grey')

        myscrollbar.pack(side="right", fill="y")
        canvas.pack(side="left")
        canvas.create_window((0, 0), window=frame, anchor='nw')
        frame.bind("<Configure>", myfunction)
        data()

        self.button = Button(main, text='?', highlightbackground='grey', command=helpButton)
        self.button.grid(row=0, column=4, padx=350)

        self.up = Button(main, text='↑', highlightbackground='grey', command=up)
        self.up.grid(row=0, column=1, sticky='e', padx=70)

        self.up = Button(main, text='↓', highlightbackground='grey', command=down)
        self.up.grid(row=0, column=1, sticky='w', padx=200)

        self.all_up = Button(main, text='All up',  highlightbackground='grey', command=all_up)
        self.all_up.grid(row=0, sticky='e', padx=10)

        self.all_down = Button(main, text='All down',  highlightbackground='grey', command=all_down)
        self.all_down.grid(row=0, sticky='w', padx=100)

