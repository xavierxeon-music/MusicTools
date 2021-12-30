#!/usr/bin/env python3

# https://mido.readthedocs.io/en/latest/
import mido
# help(mido.midifiles.tracks.MidiTrack)

from .timecode import TimeCode
from .note import Note
from .duration import Duration
from .note_queue import NoteQueue as NoteQueue


class MidiFileWriter:

    def __init__(self, bpm):

        self.mid = mido.MidiFile()

        master = mido.MidiTrack()
        self.mid.tracks.append(master)

        uSeecsPerMinute = 60000000
        tempo = int(uSeecsPerMinute / bpm)
        master.append(mido.MetaMessage('set_tempo', tempo=tempo, time=0))

    def addTrack(self, queue):

        endPosition = queue.lastNoteOff()
        if endPosition <= 0:
            return

        track = mido.MidiTrack()
        self.mid.tracks.append(track)

        delta = [0, 0]

        def getDelta(position):
            nonlocal delta
            if position != delta[0]:
                delta[1] = position - delta[0]
                delta[0] = position
                return delta[1]
            else:
                return 0

        for position in range(endPosition + 1):

            if position in queue._noteOffMap:
                for entry in queue._noteOffMap[position]:
                    dt = getDelta(position) * 120
                    note = entry[1]
                    #print('off', position, dt, note)
                    track.append(mido.Message(
                        'note_off', note=note.pitch, velocity=note.velocity, time=dt))

            if position in queue._noteOnMap:
                for entry in queue._noteOnMap[position]:
                    dt = getDelta(position) * 120
                    note = entry[1]
                    #print('on', position, dt, note)
                    track.append(mido.Message(
                        'note_on', note=note.pitch, velocity=note.velocity, time=dt))

    def save(self, fileName):

        self.mid.save(fileName)
