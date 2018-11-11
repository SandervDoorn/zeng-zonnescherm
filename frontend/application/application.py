from tkinter import *
from serial import SerialException as SerialException
from frontend.communication.connectionmanager import ConnectionManager
from frontend.application.details import Details


class Application(Frame):
    def __init__(self, master=None, serial=None):
        super().__init__(master)
        self.pack()
        self.config(bg="ghost white")

        topframe = Frame(self)
        title = Label(topframe, bg="ghost white", text="Zeng Shutter Control System", height=2)
        title.config(font=("Calibri", 20))
        title.pack()
        topframe.config(bg="ghost white")
        topframe.pack(fill=X, side="top")

        # Shuttergroup
        group = ShutterGroup(self, serial)
        group.config(bd=1, width=800, height=300, bg='gray90')
        group.pack_propagate(False)


class ShutterGroup(Frame):
    def __init__(self, parent=None, serial=None):
        super().__init__(parent)
        self.pack()
        self.serial = serial

        self.active_shutters = []
        self.new_shutters = []

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

        self.after(5000, self.update_shutterlist)

    def draw_shutters(self):
        x = 0  # Column
        y = 1  # Row
        for s in self.new_shutters:
            if x == 3:
                y += 1
                x = 0
            shutter = Shutter(s, self)
            shutter.grid(row=y, column=x, padx=10, pady=5)

            # Bind left mouseclick on shutter in GUI. Opens new window and passes Shutter object to that window
            shutter.bind('<1>',
                         lambda event, val=s: self.onclick(val))
            x += 1

    def onclick(self, val):
        # On click of a shutter
        Details(val)


class Shutter(Frame):
    def __init__(self, shutter, parent=None):
        super().__init__(parent)
        # Define parent frame (ShutterGroup) and prevent child widgets from adjusting size
        self.parent = parent
        self.shutter = shutter
        self.pack_propagate(False)
        self.config(bg='gray95', width=200, height=250)

        # Create values for the display
        self.temp_value = StringVar()
        self.temp_value.set("None")
        self.state_value = IntVar()
        self.state_value.set(0)

        self.title = Label(self, text=shutter.get_name())
        self.title.pack()

        # Create labels to display the values
        self.temp_label = Label(self, text="Temperatuur: " + self.temp_value.get() + "°C")
        self.temp_label.pack(pady=10)
        self.state_label = Label(self, text="Status: Dicht" if self.state_value.get() == 0 else "Status: Open")
        self.state_label.pack(pady=10)

        self.update_values()

    def update_values(self):
        """
        Updates values that are displayed in the labels
        Upon disconnection of shutter, updates are skipped and device is removed from GUI
        :return:
        """
        skipUpdate = False
        try:
            self.temp_value.set(self.shutter.get_temp())
            self.state_value.set(self.shutter.get_state())
        except SerialException:
            skipUpdate = True
            self.parent.forceupdate = True
            self.pack_forget()
        if not skipUpdate:
            self.temp_label.config(text="Temperatuur: " + self.temp_value.get() + "°C")
            self.state_label.config(text="Status: Dicht" if self.state_value.get() == 0 else "Status: Open")

            self.after(10000, self.update_values)


# Setup application window
root = Tk()
root.geometry("1280x720+50+50")
root.configure(background="ghost white")
root.title("Zeng Shutter Control System")

# Setup and start application
com = ConnectionManager()
app = Application(master=root, serial=com)
app.mainloop()
