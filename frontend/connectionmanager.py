import frontend.zonnescherm as zonnescherm
import serial.tools.list_ports


def check_ports():
    """
    Returns a list of COM devices identified as zeng screen
    """
    comlist = serial.tools.list_ports.comports()    # All connected COM ports
    connected = []                                  # All connected COM ports as Zonnescherm
    zonneschermen = []                              # All connected COM ports as Zonnescherm identified as Groot

    for devices in comlist:

        # Setup serial connection to device
        item = zonnescherm.Zonnescherm(devices.device)

        # Add device to zonneschermen if handshake succeeds
        if item.port not in zonneschermen:
            if item.send("WHO_ARE_YOU") == "I AM GROOT\0":
                item.set_defaults()
                zonneschermen.append(item)

        # Check if devices have been removed
        # By comparing active_list to all connected devices
        connected.append(item)
        for scherm in zonneschermen:
            if scherm not in connected:
                zonneschermen.remove(scherm)

        return zonneschermen


check_ports()
