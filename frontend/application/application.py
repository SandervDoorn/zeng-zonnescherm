import tkinter as tk
from frontend.communication.connectionmanager import ConnectionManager


class Application(tk.Frame):
    def __init__(self, master=None, serial=None):
        super().__init__(master)
        self.serial = serial
        self.active_shutters = []
        self.pack()

        # Load all shutters that are connected
        self.update_shutterlist()

        for s in self.active_shutters:
            self.shutter = Shutter(s, self)
            self.shutter.pack(fill="both")

    def update_shutterlist(self):
        self.serial.check_ports()
        self.active_shutters = self.serial.get_connections()
        self.after(10000, self.update_shutterlist)


class Shutter(tk.Frame):
    def __init__(self, shutter, parent=None):
        super().__init__(parent)
        # Define parent frame (Application) and prevent child widgets from adjusting size
        self.parent = parent
        self.shutter = shutter
        self.pack_propagate(False)
        self.config(bg='ghost white', width=200, height=250)

        # Create labels containing values to display
        self.temp_value = tk.StringVar()
        self.temp_value.set("None")

        self.temp_label = tk.Label(self, text="Temperatuur: " + self.temp_value.get())
        self.temp_label.pack()

        self.update_values()

    def update_values(self):
        self.temp_value.set(self.shutter.send("GET_SENSOR_TEMP"))
        self.temp_label.config(text="Temperatuur: " + self.temp_value.get())
        self.after(40000, self.update_values)


# Setup application window
root = tk.Tk()
root.geometry("800x800+0+0")
root.configure(background="white smoke")

# Setup and start application
com = ConnectionManager()
app = Application(master=root, serial=com)
app.mainloop()
