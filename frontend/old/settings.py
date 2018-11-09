from frontend.old.main import Main
from tkinter import *


class Settings(Main):

    def __init__(self, main):
        super().__init__(main)
        self.main = main

        label_in = Label(main, text='INROLOPTIES', bg='grey')
        label_in.grid(column=0, row=1, pady=5)

        light_in_setting = Label(main, text='START LICHTWAARDE', bg='grey')
        light_in_setting.grid(column=0, row=2, pady=10, padx=(10, 0))

        modes = [
            '100',
            '500',
            '900'
        ]

        i = 3

        for mode in modes:
            b = Radiobutton(main, text=mode, value=mode, bg='grey')
            b.grid(column=0, row=i, pady=5)
            i += 1

        max_in_label = Label(main, text='MAX INROLSTAND (CM)', bg='grey')
        max_in_label.grid(column=0, row=i+modes.__len__(), pady=(10, 0))
        max_in_full = Entry(main, highlightbackground='grey')
        max_in_full.grid(column=1, row=i+modes.__len__())

        temp_in_label = Label(main, text='START TEMPERATUUR (°C)', bg='grey')
        temp_in_label.grid(column=0, row=i + modes.__len__()+1, pady=(10, 0))
        temp_in_full = Entry(main, highlightbackground='grey')
        temp_in_full.grid(column=1, row=i + modes.__len__()+1)

        # //

        label_out = Label(main, text='UITROLOPTIES', bg='grey')
        label_out.grid(column=2, row=1, pady=5, padx=100)

        light_out_setting = Label(main, text='STOP LICHTWAARDE', bg='grey')
        light_out_setting.grid(column=2, row=2, pady=10, padx=100)

        j = 3
        for mode in modes:
            b = Radiobutton(main, text=mode, value=mode, bg='grey')
            b.grid(column=2, row=j, pady=5, padx=20)
            j += 1

        max_out_label = Label(main, text='MAX UITROLSTAND (CM)', bg='grey')
        max_out_label.grid(column=2, row=j + modes.__len__(), pady=(10, 0), padx=(100, 0))
        max_out_full = Entry(main, highlightbackground='grey')
        max_out_full.grid(column=3, row=j + modes.__len__())

        temp_out_label = Label(main, text='START TEMPERATUUR (°C)', bg='grey')
        temp_out_label.grid(column=2, row=j + modes.__len__() + 1, pady=(10, 0), padx=(100, 0))
        temp_out_full = Entry(main, highlightbackground='grey')
        temp_out_full.grid(column=3, row=j + modes.__len__() + 1)

        # //

        change_mode = Button(main, text='DEFAULT', highlightbackground='grey')
        change_mode.grid(column=3, row=1, sticky='e', padx=(330, 0))

        def helpButton():
            # deze moet ook ff worden aangepast
            main.update_idletasks()
            width = 1150
            height = 650
            x = (main.winfo_screenwidth() // 2) - (width // 2)
            y = (main.winfo_screenheight() // 2) - (height // 2)
            pop = Toplevel()
            pop.title('Help')
            pop.geometry('{}x{}+{}+{}'.format(200, 200, x + 950, y))

        button = Button(main, text='?', highlightbackground='grey', command=helpButton)
        button.grid(column=3, row=0, sticky='e', padx=(330, 0))

        save = Button(main, text='OPSLAAN', highlightbackground='grey')
        save.grid(column=3, row=j+modes.__len__() + 2, sticky='e', padx=(330, 0), pady=(100, 10))