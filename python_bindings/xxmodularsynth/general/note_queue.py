#!usr/bin/env python3

class NoteQueue:

    def __init__(self):

        self._noteOnMap = dict()
        self._noteOnPositions = list()
        self._noteOffMap = dict()
        self._noteOffPositions = list()

    def addNote(self, startTimeCode, note, channel):

        def addEvent(position, eventMap):
            if not position in eventMap:
                eventMap[position] = list()

            eventList = eventMap[position]
            eventList.append([channel, note])

            orderList = list(eventMap.keys())
            orderList.sort()
            return orderList

        startPosition = startTimeCode.position()
        self._noteOnPositions = addEvent(startPosition, self._noteOnMap)

        endPosition = startPosition + note.duration
        self._noteOffPositions = addEvent(endPosition, self._noteOffMap)

    def lastNoteOff(self):

        if self._noteOffPositions:
            return self._noteOffPositions[-1]
        return 0
