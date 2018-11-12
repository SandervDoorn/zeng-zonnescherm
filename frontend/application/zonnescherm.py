import serial
import time


class Zonnescherm:
    def __init__(self, port):
        self.port = port
        self.connection = self.start_serial(port)

        # Define settings (set with proper values using set_defaults in connectionmanager.py)
        self.name = ""
        self.mode = 0
        self.state = 0
        self.ths_temp = 0
        self.ths_dist = 0

    def set_defaults(self):
        # Default settings
        # response = self.send("GET_SETTINGS")
        self.name = self.send("GET_NAME")
        self.mode = self.send("GET_MODE")
        self.state = self.send("GET_STATE")
        self.ths_temp = self.send("GET_THS_TEMP")
        self.ths_dist = self.send("GET_THS_DIST")

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
        try:
            decoded = response.decode()
        except UnicodeDecodeError:
            print("UnicodeDecodeError found")
            decoded = ""
        print("Receiving response: " + decoded)
        return decoded

    def parse(self, response):
        res = response.split(" ")
        if res[0] == "OK":
            return res[1]
        if res[0] == "ERROR":
            raise ValueError(res)

    def get_name(self):
        return self.name

    def set_name(self, value):
        response = self.send("SET_NAME " + str(value))
        self.name = self.parse(response)

    def get_mode(self):
        return self.mode

    def set_mode(self, value):
        self.send("SET_MODE " + str(value))
        response = self.send("GET_MODE")
        self.mode = self.parse(response)

    def get_state(self):
        return self.state

    def set_state(self, value):
        self.send("SET_STATE " + str(value))
        response = self.send("GET_STATE")
        self.state = self.parse(response)

    def get_temp(self):
        response = self.send("GET_SENSOR_TEMP")
        return self.parse(response)

    def get_light(self):
        response = self.send("GET_SENSOR_LIGHT")
        return self.parse(response)

    def get_ths_temp(self):
        return self.ths_temp

    def set_ths_temp(self, value):
        response = self.send("SET_THS_TEMP " + value)
        self.ths_temp = self.parse(response)

    def get_ths_dist(self):
        return self.ths_dist

    def set_ths_dist(self, value):
        response = self.send("SET_THS_DIST " + value)
        self.ths_dist = self.parse(response)
