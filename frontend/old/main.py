

class Main:
    def __init__(self, main):
        self.main = main

        main.title('Our Program')

        main.configure(background='grey')
        main.update_idletasks()
        width = 1150
        height = 650
        x = (main.winfo_screenwidth() // 2) - (width // 2)
        y = (main.winfo_screenheight() // 2) - (height // 2)
        main.geometry('{}x{}+{}+{}'.format(width, height, x, y))



