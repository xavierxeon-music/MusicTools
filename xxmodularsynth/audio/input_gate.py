#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice


class InputGate(AudioDevice.InputChannel):

    def __init__(self, index, device):

        AudioDevice.InputChannel.__init__(self, index, device)

        self._active = False

    def process(self, indata, frames):

        highCount = 0
        for index in range(frames):

            if indata[index] > 0.1:
                highCount += 1

        if 2 * highCount >= frames:
            self._active = True
        else:
            self._active = False

    def isActive(self):

        return self._active
