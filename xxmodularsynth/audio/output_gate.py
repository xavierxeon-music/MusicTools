#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice


class OutputGate(AudioDevice.OutputChannel):

    def __init__(self, index, device):

        AudioDevice.OutputChannel.__init__(self, index, device)

        self._active = False

    def setActive(self, active):

        self._active = active

    def process(self, outdata, frames):

        for index in range(frames):

            if self._active:
                outdata[index] = 0.5
            else:
                outdata[index] = 0.0
