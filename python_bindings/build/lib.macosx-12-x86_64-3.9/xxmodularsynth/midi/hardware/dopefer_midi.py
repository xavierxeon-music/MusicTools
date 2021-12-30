#!/usr/bin/env python3

import math

from ..midi_output import MidiOutput


class DoepferMidi(MidiOutput):

    def __init__(self):

        MidiOutput.__init__(self,  name='ESI M4U eX Port 5', virtual=False)

    @staticmethod
    def compileTrigonomicTables():

        sinTable = list()
        cosTable = list()

        step = math.pi / 64
        scale = 127 / 128

        for index in range(128):
            angle = index * step

            s = math.sin(angle)
            s = (s + 1) * 64 * scale
            sinTable.append(s)

            c = math.cos(angle)
            c = (c + 1) * 64 * scale
            cosTable.append(c)

        return [sinTable, cosTable]
