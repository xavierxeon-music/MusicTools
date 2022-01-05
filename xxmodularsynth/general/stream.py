#!/usr/bin/env python3

class Stream:

    def __init__(self, clock, output):

        clock.onPositionChange(self._positionChanged)

        self._output = output
        self._position = 1

        self._noteOnBuffer = list()
        self._noteOffMap = dict()

    def playNote(self, note, channel):

        self._noteOnBuffer.append([note, channel])

    def _positionChanged(self, position):

        if position < self._position:
            self._noteOnBuffer.clear()
            self._noteOffMap.clear()
            return
        else:
            self._position = position

        for entry in self._noteOnBuffer:
            note = entry[0]
            channel = entry[1]

            endPosition = position + note.duration
            if not endPosition in self._noteOffMap:
                self._noteOffMap[endPosition] = list()

            self._noteOffMap[endPosition].append([channel, note.pitch])
            self._output.noteOn(channel, note.pitch, note.velocity)
        self._noteOnBuffer.clear()

        if position in self._noteOffMap:
            for entry in self._noteOffMap[position]:
                self._output.noteOff(entry[0], entry[1])
            del self._noteOffMap[position]
