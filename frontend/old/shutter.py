from datetime import *
from time import *


class Shutter:
    def __init__(self, name, state, temp, light, setting, max_out, max_in):
        self.name = name
        self.temp = temp
        self.state = state
        self.light = light

        self.setting = setting
        # (manual automatic --> print in page2)
        self.max_out = max_out
        # default values
        self.max_in = max_in

