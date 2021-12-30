#!/usr/bin/env python3

from rtmidi.midiconstants import MODULATION


class CVTool:

    def __init__(self, output, channel, controller=MODULATION):

        self._output = output
        self._channel = channel
        self._controller = controller

        self._pitch = 24  # minimium pitch of A190-5
        self._velocity = 0
        self._controllerValue = 0

    def __del__(self):

        self._output.noteOff(self._channel, self._pitch)

    def pitch(self, value):

        self._pitch = value
        self._update()

    def cv2(self, value):

        self._velocity = value
        self._update()

    def cv3(self, value):

        self._controllerValue = value
        self._update()

    def _update(self):

        self._output.noteOff(self._channel, self._pitch)
        self._output.noteOn(self._channel, self._pitch, self._velocity)
        self._output.controllerChange(
            self._channel, self._controllerValue, self._controller)
