#!/usr/bin/env python3

import time

from ..midi_output import MidiOutput
from ..note import Note


class EricaTrigger(MidiOutput):

    Channel = 1

    class Port:

        One = Note.pitch('C4')
        Two = Note.pitch('D4')
        Three = Note.pitch('E4')
        Four = Note.pitch('F4')

        Five = Note.pitch('G4')
        Six = Note.pitch('A4')
        Seven = Note.pitch('B4')
        Eight = Note.pitch('C5')

    def __init__(self):

        MidiOutput.__init__(self, name='ESI M4U eX Port 7', virtual=False)

    def setup(self):

        for pitch in range(EricaTrigger.Port.One, EricaTrigger.Port.Eight + 1):

            self.noteOn(EricaTrigger.Channel, pitch, 127)
            time.sleep(0.5)

            self.noteOff(EricaTrigger.Channel, pitch)
            time.sleep(0.5)
