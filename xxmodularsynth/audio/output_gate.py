#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice


class OutputGate(AudioDevice.OutputChannel):

    def __init__(self, index, device):

        AudioDevice.OutputChannel.__init__(self, index, device)

        self._active = False
        self._triggerFrames = 0
        self.__maxTriggerFrames = device.sampleRate / 100.0  # 10 ms

    def setActive(self, active):

        self._active = active

    def setTrigger(self):

        self._triggerFrames = self.__maxTriggerFrames

    def process(self, outdata, frames):

        for index in range(frames):

            if self._active or self._triggerFrames > 0:
                outdata[index] = 0.5  # set to 5V
            else:
                outdata[index] = 0.0

            if self._triggerFrames > 0:
                self._triggerFrames -= 1
