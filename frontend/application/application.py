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

        # Create values for the display, proper values are added in first update_values
        self.v_temp = StringVar()
        self.v_temp.set("None")
        self.v_state = IntVar()
        self.v_state.set(0)
        self.v_mode = IntVar()
        self.v_mode.set(0)

        self.title = Label(self, text=shutter.get_name())
        self.title.pack()

        # Create labels to display the values
        self.l_temp = Label(self, text="Temperatuur: " + self.v_temp.get() + "°C")
        self.l_temp.pack(pady=10)
        self.l_state = Label(self, text="Status: Dicht" if self.v_state.get() == 0 else "Status: Open")
        self.l_state.pack(pady=10)
        self.l_mode = Label(self, text="Modus: Handmatig" if self.v_mode.get() == 0 else "Modus: Automatisch")
        self.l_mode.pack(pady=10)

        self.b_mode = Button(self, text="Automatisch" if self.v_mode.get() == 0 else "Handmatig", command=self.update_mode)
        self.b_mode.pack(side="bottom", fill='x', padx=5, pady=5)
        self.b_state = Button(self, text="Openen" if self.v_state.get() == 0 else "Sluiten", command=self.update_state)
        self.b_state.pack(side="bottom", fill='x', padx=5, pady=5)

        self.update_values()

    def update_values(self):
        """
        Updates values that are displayed in the labels every 40 seconds
        Upon disconnection of shutter, updates are skipped and device is removed from GUI
        :return:
        """
        skipUpdate = False
        try:
            self.v_temp.set(self.shutter.get_temp())
            self.v_state.set(self.shutter.get_state())
            self.v_mode.set(self.shutter.get_mode())
        except SerialException:
            skipUpdate = True
            self.parent.forceupdate = True
            self.pack_forget()
        if not skipUpdate:
            self.l_temp.config(text="Temperatuur: " + self.v_temp.get() + "°C")
            self.l_state.config(text="Status: Dicht" if self.v_state.get() == 0 else "Status: Open")
            self.l_mode.config(text="Modus: Handmatig" if self.v_mode.get() == 0 else "Modus: Automatisch")

            self.after(40000, self.update_values)

    def update_state(self):
        """
        Sends a command to change the screen state
        Updates state label and button content
        Sets screen mode to manual to prevent man vs machine conflict
        :return:
        """
        if self.v_state.get() == 1:
            self.shutter.set_state("CLOSED")
            self.v_state.set(0)
            self.l_state.config(text="Status: Dicht")
            self.b_state.config(text="Openen")

        elif self.v_state.get() == 0:
            self.shutter.set_state("OPEN")
            self.v_state.set(1)
            self.l_state.config(text="Status: Open")
            self.b_state.config(text="Sluiten")

    def update_mode(self):
        """
        Sends a command to change the screen mode
        Updates mode label and button content
        :return:
        """
        if self.v_mode.get() == 1:
            self.shutter.set_mode("MANUAL")
            self.v_mode.set(0)
            self.l_mode.config(text="Modus: Handmatig")
            self.b_mode.config(text="Automatisch")

        elif self.v_mode.get() == 0:
            self.shutter.set_mode("AUTO")
            self.v_mode.set(1)
            self.l_mode.config(text="Modus: Automatisch")
            self.b_mode.config(text="Handmatig")


# Setup application window
root = Tk()
root.geometry("1280x720+50+50")
root.configure(background="ghost white")
root.title("Zeng Shutter Control System")

# Setup and start application
com = ConnectionManager()
app = Application(master=root, serial=com)
app.mainloop()
