#!/usr/bin/env python3

from sounddevice import Stream, query_devices


class AudioDevice:

    class InputChannel:

        def __init__(self, callbackFunction=None):

            self._callbackFunction = callbackFunction

        def process(self, indata, frames):

            if not self._callbackFunction:
                raise NotImplementedError

            self._callbackFunction(indata, frames)

    class OutputChannel:

        def __init__(self, callbackFunction=None):

            self._callbackFunction = callbackFunction

        def process(self, outdata, frames):

            if not self._callbackFunction:
                raise NotImplementedError

            self._callbackFunction(outdata, frames)

    def __init__(self, deviceName, noOfInputs=None, noOfOutputs=None):

        self._deviceIndex = None
        self._noOfInputs = noOfInputs
        self._noOfOutputs = noOfOutputs

        self._inputChannels = dict()
        self._outputChannels = dict()

        self.sampleRate = None
        self.blockSize = None

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
            raise ValueError(f'device {deviceName} not found')

        print(f'device {deviceName} has index {self._deviceIndex}: {self._noOfInputs} inputs, {self._noOfOutputs} outputs')

    def addInput(self, index, inputChannel):

        if not isinstance(inputChannel, AudioDevice.InputChannel):
            raise TypeError('inputChannel must be of type InputChannel')

        if index < 0 or index >= self._noOfInputs:
            return

        self._inputChannels[index] = inputChannel

    def addOutput(self, index, outputChannel):

        if not isinstance(outputChannel, AudioDevice.OutputChannel):
            raise TypeError('outputChannel must be of type OutputChannel')

        if index < 0 or index >= self._noOfOutputs:
            return

        self._outputChannels[index] = outputChannel

    def audioLoop(self, callbackFunction=None):

        print('start audio loop')

        if None == self.blockSize:
            blockSize = int(self.sampleRate / 1000.0)
        else:
            blockSize = self.blockSize

        if not callbackFunction:
            callbackFunction = self._callback
        try:
            with Stream(samplerate=self.sampleRate, blocksize=blockSize, device=self._deviceIndex, channels=(self._noOfInputs, self._noOfOutputs), callback=callbackFunction):
                print('#' * 80)
                print('press Return to quit')
                print('#' * 80)
                input()
        except KeyboardInterrupt:
            print('\nInterrupted by user')
        except Exception as e:
            print(type(e).__name__ + ': ' + str(e))

    def _callback(self, indata, outdata, frames, time, status):

        noOfInputChannels = indata.shape[1]
        for index in range(noOfInputChannels):
            if not index in self._inputChannels:
                continue

            data = indata[:, index]
            self._inputChannels[index].process(data, frames)

        noOfOutputChannels = outdata.shape[1]
        for index in range(noOfOutputChannels):
            if not index in self._outputChannels:
                continue

            data = outdata[:, index]
            self._outputChannels[index].process(data, frames)
