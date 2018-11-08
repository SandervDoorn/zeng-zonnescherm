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

    def get_temp(self):
        return self.send("GET_SENSOR_TEMP")

    def get_light(self):
        return self.send("GET_SENSOR_LIGHT")

    def get_ths_temp(self):
        return self.ths_temp

    def get_ths_dist(self):
        return self.ths_dist

    def set_ths_temp(self, value):
        self.ths_temp = self.send("SET_THOLD_TEMP " + str(value))

    def set_ths_dist(self, value):
        if isinstance(value, int) and value in range(2, 71):
            self.ths_dist = self.send("SET_THOLD_DIST" + str(value))
        else:
            return "Value is not a valid number"

