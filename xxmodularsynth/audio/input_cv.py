#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice


class InputCV(AudioDevice.InputChannel):

    """
    voltages from -10V to +10V
    """

    def __init__(self, index, device):

        AudioDevice.InputChannel.__init__(self, index, device)

        self._value = 0.0

    def process(self, indata, frames):

        self._value = 0.0
        for index in range(frames):
            self._value += 10.0 * indata[index]

        self._value /= frames

    def getValue(self):

        return self._value
