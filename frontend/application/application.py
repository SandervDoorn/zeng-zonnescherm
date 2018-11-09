import tkinter as tk
from serial import SerialException as SerialException
from frontend.communication.connectionmanager import ConnectionManager


class Application(tk.Frame):
    def __init__(self, master=None, serial=None):
        super().__init__(master)
        self.serial = serial
        self.active_shutters = []
        self.new_shutters = []
        self.pack()

        # Load all shutters that are connected
        self.update_shutterlist()

    def update_shutterlist(self):
        self.serial.check_ports()
        # Store all open connections and new connections seperatly
        self.active_shutters = self.serial.get_connections()
        self.new_shutters = self.serial.get_new_connections()

        if self.serial.hasUpdated():
            # Reset the update flag in the connection manager
            # Draw the new shutters and empty new shutters list
            self.serial.reset_hasUpdated()
            self.draw_shutters()
            self.serial.reset_new_connections()

        self.after(10000, self.update_shutterlist)

    def draw_shutters(self):
        for s in self.new_shutters:
            shutter = Shutter(s, self)
            shutter.pack()
            shutter.bind('<1>',
                         lambda event, val=s: self.onclick(val))

    def onclick(self, val):
        # On click of a shutter
        Details(val)


class Details(tk.Toplevel):
    def __init__(self, shutter=None):
        super().__init__()

        # Set size of new window
        self.config(width=1000, height=1000)

        testLabel = tk.Label(self, text=shutter.get_port())
        testLabel.pack()


class Shutter(tk.Frame):
    def __init__(self, shutter, parent=None):
        super().__init__(parent)
        # Define parent frame (Application) and prevent child widgets from adjusting size
        self.parent = parent
        self.shutter = shutter
        self.pack_propagate(False)
        self.config(bg='ghost white', width=200, height=250)

        # Create values for the display
        self.temp_value = tk.StringVar()
        self.temp_value.set("None")
        self.counter = tk.IntVar()
        self.counter.set(1)

        # Create labels to display the values
        self.title = tk.Label(self, text=shutter.get_port())
        self.title.pack()
        self.temp_label = tk.Label(self, text="Temperatuur: " + self.temp_value.get())
        self.temp_label.pack()
        self.counter_label = tk.Label(self, text="Counter: " + str(self.counter.get()))
        self.counter_label.pack()

        self.update_values()

    def update_values(self):
        skipUpdate = False
        try:
            self.temp_value.set(self.shutter.send("GET_SENSOR_TEMP"))
        except SerialException:
            skipUpdate = True
            self.parent.forceupdate = True
            self.pack_forget()
        if not skipUpdate:
            self.temp_label.config(text="Temperatuur: " + self.temp_value.get())
            i = self.counter.get() + 1
            self.counter.set(i)
            self.counter_label.config(text="Counter: " + str(self.counter.get()))

            self.after(20000, self.update_values)


# Setup application window
root = tk.Tk()
root.geometry("800x800+0+0")
root.configure(background="white smoke")

# Setup and start application
com = ConnectionManager()
app = Application(master=root, serial=com)
app.mainloop()
