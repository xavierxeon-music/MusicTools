#!/usr/bin/env python3

import sys

from sounddevice import Stream, query_devices


class AudioDevice:

    """
    override 

    def audioLoop(self, indata, outdata, frames, audioRate):

        self.processInputs(indata, frames)
        self.processOutputs(outdata, frames)
    """

    class InputChannel:

        def __init__(self, index, device):

            device.addInput(index, self.process)

        def process(self, indata, frames):

            raise NotImplementedError

    class OutputChannel:

        def __init__(self, index, device):

            device.addOutput(index, self.process)

        def process(self, outdata, frames):

            raise NotImplementedError

    def __init__(self, deviceName, noOfInputs=None, noOfOutputs=None):

        self._deviceIndex = None
        self._noOfInputs = noOfInputs
        self._noOfOutputs = noOfOutputs

        self.sampleRate = None
        self.blockSize = None

        self._setup(deviceName, noOfInputs, noOfOutputs)

    def addInput(self, index, inputCallback):

        if index < 0 or index >= self._noOfInputs:
            return

        self._inputCallbacks[index] = inputCallback

    def addOutput(self, index, outputCallback):

        if index < 0 or index >= self._noOfOutputs:
            return

        self._outputCallbacks[index] = outputCallback

    def audioLoop(self, indata, outdata, frames, audioRate):

        self.processInputs(indata, frames)
        self.processOutputs(outdata, frames)

    def processInputs(self, indata, frames):

        noOfInputChannels = indata.shape[1]
        for index in range(noOfInputChannels):
            if not index in self._inputCallbacks:
                continue

            data = indata[:, index]
            self._inputCallbacks[index](data, frames)

    def processOutputs(self, outdata, frames):

        noOfOutputChannels = outdata.shape[1]
        for index in range(noOfOutputChannels):
            if not index in self._outputCallbacks:
                continue

            data = outdata[:, index]
            self._outputCallbacks[index](data, frames)

    def start(self):

        print('start audio loop')

        if None == self.blockSize:
            self.blockSize = int(self.sampleRate / 1000.0)

        try:
            with Stream(samplerate=self.sampleRate, blocksize=self.blockSize, device=self._deviceIndex, channels=(self._noOfInputs, self._noOfOutputs), callback=self._callback):
                print('#' * 80)
                print('press Return to quit')
                print('#' * 80)
                input()
        except KeyboardInterrupt:
            print('\nInterrupted by user')
        except Exception as e:
            print(type(e).__name__ + ': ' + str(e))

    def _callback(self, indata, outdata, frames, time, status):

        audioRate = self.sampleRate / self.blockSize
        self.audioLoop(indata, outdata, frames, audioRate)

    def _setup(self, deviceName, noOfInputs, noOfOutputs):

        self._inputCallbacks = dict()
        self._outputCallbacks = dict()

        for index, device in enumerate(query_devices()):
            if not device['name'].startswith(deviceName):  # names may differ accross OS's
                continue

            self._deviceIndex = index
            self.sampleRate = device['default_samplerate']

            maxInputs = device['max_input_channels']
            if None == noOfInputs:
                self._noOfInputs = maxInputs
            elif noOfInputs > maxInputs:
                raise ValueError(f'No enogh inputs on device {deviceName}')

            maxOutputs = device['max_output_channels']
            if None == noOfOutputs:
                self._noOfOutputs = maxOutputs
            elif noOfOutputs > maxOutputs:
                raise ValueError(f'No enogh outputs on device {deviceName}')

            break

        if None == self._deviceIndex:
            print(f'device {deviceName} not found')
            sys.exit()

        print(f'device {deviceName} has index {self._deviceIndex}: {self._noOfInputs} inputs, {self._noOfOutputs} outputs')
