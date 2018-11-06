import serial
import serial.tools.list_ports
from time import sleep


def send_command(command, port):
    connection = serial.Serial(
        port=port,
        baudrate=9600,
        timeout=5,
    )

    if connection.isOpen():
        connection.close()

    connection.open()

    # Wait for arduino to wake up
    sleep(2)

    if connection.inWaiting() == 0:
        print("Command: " + command)
        line = command + "\r\n"
        connection.write(line.encode())

    response = connection.readline()
    print("Response: " + response.decode('utf-8'))

    # Return the response given by Arduino
    return response.decode()


def check_ports():
    """
    Returns a list of COM devices identified as zeng screen
    """

    comlist = serial.tools.list_ports.comports()    # All connected COM ports
    connected = []                                  # All connected COM ports by ID
    active_screens = []                             # All active COM ports identified as zeng screen
    for devices in comlist:
        # Add device to active_screens if handshake succeeds
        if devices.device not in active_screens:
            if send_command("WHO_ARE_YOU", devices.device) == "I AM GROOT":
                active_screens.append(devices.device)

        # Check if devices have been removed
        # By comparing active_list to all connected devices
        connected.append(devices.device)
        for screen in active_screens:
            if screen not in connected:
                active_screens.remove(screen)

    return active_screens


send_command("SET_THOLD_DIST 20", 'COM3')
