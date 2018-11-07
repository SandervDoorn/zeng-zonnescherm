import serial
import time


class Zonnescherm:
    def __init__(self, port):
        self.port = port
        self.connection = self.start_serial(port)

        # Define settings (set with proper values using set_defaults in connectionmanager.py)
        self.name = ""
        self.mode = ""
        self.state = ""
        self.ths_temp = 0
        self.ths_dist = 0

    def set_defaults(self):
        # Default settings
        self.name = self.send("GET_NAME")
        self.mode = self.send("GET_MODE")
        self.state = self.send("GET_STATE")
        self.ths_temp = self.send("GET_THOLD_TEMP")
        self.ths_dist = self.send("GET_THOLD_DIST")
        print(  "Name: " + self.name + "\r\n"
                "Mode: " + self.mode + "\r\n"
                "State: " + self.state + "\r\n"
                "Ths_temp: " + self.ths_temp + "\r\n"
                "Ths_dist: " + self.ths_dist + "\r\n")

    def get_port(self):
        return self.port

    def start_serial(self, port):
        connection = serial.Serial(
            port=port,
            baudrate=9600,
            timeout=2,
        )

        # Wait for arduino to wake up before returning the connection
        time.sleep(2)

        return connection

    def send(self, command):
        if self.connection.inWaiting() == 0:
            line = command + "\r"
            self.connection.write(line.encode())

        response = self.connection.readline()

        # Return the response given by Arduino
        return response.decode()

