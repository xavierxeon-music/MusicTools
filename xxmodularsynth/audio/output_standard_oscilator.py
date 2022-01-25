#!/usr/bin/env python3

from xxmodularsynth.audio import AudioDevice
from xxmodularsynth.audio.hardware import ES8
from xxmodularsynth.base import TableOscilator, Standard, Note


class OutputStandardOscilator(AudioDevice.OutputChannel, TableOscilator):

    def __init__(self, index, device, waveform):

        AudioDevice.OutputChannel.__init__(self, index, device)
        TableOscilator.__init__(self)

        self._table = Standard.getTable(waveform)
        self.init(self._table, ES8.defaultSampleRate)

        self.frequency = 0.0

    def mute(self):

        self.frequency = 0.0

    def setPitchFromCV(self, voltage):

        note = Note.fromVoltage(voltage)
        self.frequency = note.frequency

    def setPitchFromWavelength(self, wavelength):

        self.frequency = 1.0 / wavelength

    def process(self, outdata, frames):

        for index in range(frames):
            outdata[index] = self.createSound()
