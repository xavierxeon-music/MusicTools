#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice


class OutputCV(AudioDevice.OutputChannel):

    def __init__(self, index, device):

        AudioDevice.OutputChannel.__init__(self, index, device)

        self._value = 0.0

    def setValue(self, value):

        self._value = value

    def process(self, outdata, frames):

        for index in range(frames):

            outdata[index] = 0.1 * self._value
