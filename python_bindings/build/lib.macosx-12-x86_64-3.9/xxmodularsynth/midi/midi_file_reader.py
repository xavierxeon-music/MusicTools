#!/usr/bin/env python3

# https://mido.readthedocs.io/en/latest/
import mido
# help(mido.midifiles.tracks.MidiTrack)

from .timecode import TimeCode
from .note import Note
from .duration import Duration
from .note_queue import NoteQueue


class MidiFileReader:

    def __init__(self):

        self.tracks = dict()

        self._uSecPerBeat = 5000
        self._noteBuffer = dict()

    def load(self, fileName):

        mid = mido.MidiFile(fileName)

        functionDict = {
            mido.midifiles.meta.MetaMessage: self._metaMessage,
            mido.messages.messages.Message: self._message
        }

        for i, track in enumerate(mid.tracks):
            self._noteBuffer = dict()
            time = 0
            for msg in track:
                time += msg.time
                f = functionDict[type(msg)]
                f(msg, i, time)

    def bpm(self):

        uSeecsPerMinute = 60000000
        return uSeecsPerMinute / self._uSecPerBeat

    def _metaMessage(self, msg, trackId, time):

        # print(msg.dict())

        if msg.type == 'set_tempo':
            self._uSecPerBeat = msg.tempo
        if msg.type == 'end_of_track':
            pass

    def _message(self, msg, trackId, time):

        if msg.type == 'note_on':
            self._noteBuffer[msg.note] = msg
        elif msg.type == 'note_off':
            on_msg = self._noteBuffer[msg.note]

            startTimeCode = TimeCode()
            startTimeCode.set((on_msg.time / 120) + 1)

            duration = (msg.time - on_msg.time) / 120
            note = Note(on_msg.note, duration, on_msg.velocity)

            channel = on_msg.channel

            if not trackId in self._tracks:
                self._tracks[trackId] = NoteQueue()

            self._tracks[trackId].addNote(startTimeCode, note, channel)
