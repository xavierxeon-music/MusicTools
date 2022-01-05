#!usr/bin/env python3

from .note_queue import NoteQueue


class Sequencer(NoteQueue):

    def __init__(self, clock, output):

        NoteQueue.__init__(self)
        clock.onPositionChange(self._songPostion)

        self._output = output
        self._finsihedCallbackList = list()

    def set(self, noteQueue):

        self._noteOnMap = noteQueue._noteOnMap
        self._noteOnPositions = noteQueue._noteOnPositions
        self._noteOffMap = noteQueue._noteOffMap
        self._noteOffPositions = noteQueue._noteOffPositions

    def onFinished(self, callback):

        self._finsihedCallbackList.append(callback)

    def _songPostion(self, position):

        if position > self.lastNoteOff():
            for callback in self._finsihedCallbackList:
                callback()
            return

        if position in self._noteOffMap:
            for entry in self._noteOffMap[position]:
                self._output.noteOff(entry[0], entry[1].pitch)

        if position in self._noteOnMap:
            for entry in self._noteOnMap[position]:
                self._output.noteOn(
                    entry[0], entry[1].pitch, entry[1].velocity)
