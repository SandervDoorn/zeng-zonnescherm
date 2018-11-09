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
        response = self.send("GET_SETTINGS").split(" ")
        self.name = response[0]
        self.mode = response[1]
        self.state = response[2]
        self.ths_temp = response[3]
        self.ths_dist = response[4]

    def get_port(self):
        return self.port

    def start_serial(self, port):
        connection = serial.Serial(
            port=port,
            baudrate=19200,
            timeout=2,
        )

        # Wait for arduino to wake up before returning the connection
        time.sleep(2)

        return connection

    def send(self, command):
        if self.connection.inWaiting() == 0:
            line = command + "\r"
            print("Sending command: " + command + " on device: " + self.port)
            self.connection.write(line.encode())

        response = self.connection.readline()

        # Return the response given by Arduino
        print("Receiving response: " + response.decode())
        return response.decode()

    def parse(self, response):
        res = response.split(" ")
        if res[0] == "OK":
            return res[1]
        if res[0] == "ERROR":
            raise ValueError(res[1])

    def get_name(self):
        return self.name

    def get_state(self):
        val = self.send("GET_STATE")
        return self.parse(val)[0]

    def get_temp(self):
        val = self.send("GET_SENSOR_TEMP")
        return self.parse(val)

    def get_light(self):
        val = self.send("GET_SENSOR_LIGHT")
        return self.parse(val)

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

