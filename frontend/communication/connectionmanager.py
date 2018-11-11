import frontend.application.zonnescherm as zonnescherm
import serial.tools.list_ports


class ConnectionManager:
    def __init__(self):
        self.connections = []
        self.newconnections = []
        self.updated = False

    def check_ports(self):
        """
        Returns a list of COM devices identified as zeng screen
        """
        print("Checking for new devices")
        comlist = serial.tools.list_ports.comports()    # All connected COM ports
        connected = []                                  # All connected COM ports as Zonnescherm object

        for devices in comlist:
            try:
                # Check if device already exists and break if True
                flag = False
                for z in self.connections:
                    if z.port == devices.device:
                        connected.append(z)
                        flag = True
                        break
                if flag:
                    continue

                # Setup serial connection to device and add as Zonnescherm object
                item = zonnescherm.Zonnescherm(devices.device)
                connected.append(item)

                # Add device to connections if handshake succeeds
                if item not in self.connections:
                    if item.send("WHO_ARE_YOU") == "I AM GROOT\0":
                        item.set_defaults()
                        self.connections.append(item)
                        self.newconnections.append(item)
                        self.updated = True

            # If serial connection breaks during operations
            except serial.serialutil.SerialException:
                print("Lost connection to device")

        # Check if devices have been removed
        # By comparing active_list to all connected devices
        for scherm in self.connections:
            if scherm not in connected:
                self.updated = True
                self.connections.remove(scherm)

    def get_connections(self):
        return self.connections

    def get_new_connections(self):
        return self.newconnections

    def reset_new_connections(self):
        self.newconnections = []

    def hasUpdated(self):
        return self.updated

    def reset_hasUpdated(self):
        self.updated = False

    def get_single_connection(self, port):
        for device in self.connections:
            if device.get_port() == port:
                return device
        return "Device not found"
