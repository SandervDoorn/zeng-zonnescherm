import serial
from time import sleep


def sendCommand(command, port):
    connection = serial.Serial(
        port=port,
        baudrate=9600,
    )

    if connection.isOpen():
        connection.close()

    connection.open()

    # Wait for arduino to wake up
    sleep(2)

    if connection.inWaiting() == 0:
        line = command + "\r\n"
        connection.write(line.encode())

    endchar = '>'
    inchar = ''
    response = ''
    while endchar is not inchar:
        inchar = connection.read().decode()

        if endchar is not inchar:
            response += inchar

    # Trim the original command of response
    return response.split('\n')[1]


print(sendCommand("1", 'COM3'))
