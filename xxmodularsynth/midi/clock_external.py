#!/usr/bin/env python3

from rtmidi.midiconstants import SONG_POSITION_POINTER, TIMING_CLOCK, SONG_START, SONG_CONTINUE, SONG_STOP

from .clock_abstract import ClockAbstract
from .midi_input import MidiInput


class ClockExternal(ClockAbstract, MidiInput):

    def __init__(self, name=None, port=None):

        ClockAbstract.__init__(self)
        MidiInput.__init__(self, name, port)

        self.midiin.ignore_types(timing=False)

    def _callback(self, event, _):

        message, _ = event
        midiEvent = message[0]
        if midiEvent == SONG_POSITION_POINTER:
            front = message[1]
            back = message[2]
            position = 1 + (128 * front) + back
            self._setSongPosition(position)
        elif midiEvent == TIMING_CLOCK:
            self._clockTick()
        elif midiEvent == SONG_START:
            self._setState(ClockAbstract.State.Start)
        elif midiEvent == SONG_CONTINUE:
            self._setState(ClockAbstract.State.Continue)
        elif midiEvent == SONG_STOP:
            self._setState(ClockAbstract.State.Stop)
