#!/usr/bin/env python3

from random import randrange

from xxmodularsynth.audio import AudioDevice
from xxmodularsynth.audio.hardware import ES8


class OutputRandomRamp(AudioDevice.OutputChannel):

    def __init__(self, index, device, segmentLength, strength, tempo=None):

        AudioDevice.OutputChannel.__init__(self, index, device)

        self._segmentLength = segmentLength * ES8.defaultSampleRate
        self._segmentIndex = 0
        self._strength = strength
        self._tempo = tempo

        self._startValue = 2.0
        self._stopValue = self._selectNewStopValue()
        #print(self._startValue, self._stopValue)

    def process(self, outdata, frames):

        if self._tempo and not self._tempo.isRunning():
            for index in range(frames):
                outdata[index] = 0.0
            return

        for index in range(frames):
            self._segmentIndex += 1
            if self._segmentIndex == self._segmentLength:
                self._segmentIndex = 0
                self._startValue = self._stopValue
                self._stopValue = self._selectNewStopValue()
                #print(self._startValue, self._stopValue)

            percent = self._segmentIndex / self._segmentLength
            diff = self._stopValue - self._startValue
            value = self._startValue + (diff * percent)

            outdata[index] = value

    def _selectNewStopValue(self):

        random = randrange(50)
        choice = 0
        if 0 < random:
            index = int(self._startValue * 10)
            choice = 2 if index > random else 1

        if 1 == choice:  # up
            value = self._startValue + self._strength
        elif 2 == choice:  # down
            value = self._startValue - self._strength
        else:
            value = self._startValue

        if 0.0 > value:
            value = 0.0
        elif 5.0 < value:
            value = 5.0

        return value
