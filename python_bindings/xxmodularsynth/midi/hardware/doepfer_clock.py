#!/usr/bin/env python3

from ..midi_output import MidiOutput
from ..clock_abstract import ClockAbstract

from rtmidi.midiconstants import SONG_POSITION_POINTER, TIMING_CLOCK, SONG_START, SONG_CONTINUE, SONG_STOP


class DoepferClock(MidiOutput):

    def __init__(self, masterClock: ClockAbstract):

        MidiOutput.__init__(self,  name='ESI M4U eX Port 6', virtual=False)

        masterClock.onStateChange(self._stateChange)
        masterClock.onPositionChange(self._positionChanged)
        masterClock.onTick(self._tick)

    def _stateChange(self, state):

        if state == ClockAbstract.State.Start:
            data = [SONG_START]
        elif state == ClockAbstract.State.Stop:
            data = [SONG_STOP]
        elif state == ClockAbstract.State.Continue:
            data = [SONG_CONTINUE]

        self.midiout.send_message(data)

    def _positionChanged(self, position):

        back = position % 128
        front = (position - back) / 128
        data = [SONG_POSITION_POINTER, front, back]
        self.midiout.send_message(data)

    def _tick(self):

        data = [TIMING_CLOCK]
        self.midiout.send_message(data)
