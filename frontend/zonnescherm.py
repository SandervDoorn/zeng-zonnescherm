import serial
import time


class Zonnescherm:
    def __init__(self, port, name="Zonnescherm"):
        self.port = port
        self.name = name
        self.connection = self.start_serial(port)

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
