#!usr/bin/env python3

from rtmidi import MidiIn
from rtmidi.midiconstants import NOTE_ON, NOTE_OFF, CONTROLLER_CHANGE, SYSTEM_EXCLUSIVE


class MidiInput:

    def __init__(self, name, virtual=True):

        self.midiin = MidiIn()
        if virtual:
            print('virtual input', name)
            self.midiin.open_virtual_port(name)
        else:
            portNames = self.midiin.get_ports()
            if not name in portNames:
                print('available ports')
                for portIndex, portName in enumerate(portNames):
                    print(portIndex, portName)
                raise ValueError

            port = portNames.index(name)
            print('real input {0} = {1}'.format(port, portNames[port]))

            self.midiin.open_port(port)
            if not self.midiin.is_port_open():
                print('not open')

        self.midiin.set_callback(self._callback)

        self._noteOnCallbackList = list()
        self._noteOffCallbackList = list()
        self._controllerMessageCallbackList = list()

    def __del__(self):

        print('close port')
        self.midiin.close_port()
        del self.midiin  # to remove virtual port

    def onNoteOn(self, callback):

        self._noteOnCallbackList.append(callback)

    def onNoteOff(self, callback):

        self._noteOffCallbackList.append(callback)

    def onControllerMessage(self, callback):

        self._controllerMessageCallbackList.append(callback)

    @staticmethod
    def available():

        return MidiIn().get_ports()

    def _callback(self, event, data):

        message, _ = event
        midiEvent = message[0] & SYSTEM_EXCLUSIVE
        if not midiEvent:  # was system event
            return

        if midiEvent == NOTE_ON:
            status, pitch, velocity = message
            channel = (status & 0x0F) + 1
            for callback in self._noteOnCallbackList:
                callback(channel, pitch, velocity)
        elif midiEvent == NOTE_OFF:
            status, pitch, _ = message
            channel = (status & 0x0F) + 1
            for callback in self._noteOffCallbackList:
                callback(channel, pitch)
        elif midiEvent == CONTROLLER_CHANGE:
            status, controller, value = message
            channel = (status & 0x0F) + 1
            for callback in self._controllerMessageCallbackList:
                callback(channel, controller, value)
