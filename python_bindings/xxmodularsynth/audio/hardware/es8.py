#!/usr/bin/env python3

from ..audio_device import AudioDevice


class ES8(AudioDevice):

    defaultSampleRate = 0

    def __init__(self, extendedInputs = False, extendedOutputs = False):

        noOfInputs = 12 if extendedInputs else 4
        noOfOutputs = 16 if extendedOutputs else 8
        AudioDevice.__init__(self, 'ES-8', noOfInputs, noOfOutputs)

        ES8.defaultSampleRate = self.sampleRate

