#!/usr/bin/env python3

from rtmidi import MidiOut
from rtmidi.midiconstants import NOTE_ON, NOTE_OFF, CONTROLLER_CHANGE, MODULATION


class MidiOutput:

    def __init__(self, name, virtual=True):

        self.midiout = MidiOut()
        if virtual:
            print('virtual output', name)
            self.midiout.open_virtual_port(name)
        else:
            portNames = self.midiout.get_ports()
            if not name in portNames:
                print('available ports')
                for portIndex, portName in enumerate(portNames):
                    print(portIndex, portName)
                raise ValueError

            port = portNames.index(name)
            print('real output {0} = {1}'.format(port, portNames[port]))

            self.midiout.open_port(port)
            if not self.midiout.is_port_open():
                print('not open')

    def __del__(self):

        print('close port')
        self.midiout.close_port()
        del self.midiout  # to remove virtual port

    def noteOn(self, channel, pitch, velocity):

        data = [NOTE_ON | (channel - 1), pitch, velocity]
        self.midiout.send_message(data)

    def noteOff(self, channel, pitch):

        data = [NOTE_OFF | (channel - 1), pitch, 0]
        self.midiout.send_message(data)

    def controllerChange(self, channel, controller, value):

        data = [CONTROLLER_CHANGE | (channel - 1), controller, value]
        self.midiout.send_message(data)

    @staticmethod
    def available():

        return MidiOut().get_ports()
