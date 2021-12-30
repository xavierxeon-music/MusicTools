#!/usr/bin/env python3

import time

from .clock_internal import ClockInternal
from .clockprinter import ClockPrinter
from .sequencer import Sequencer


class Performance:

    def __init__(self, bpm, output, clock=None):

        self.masterClock = clock if clock else ClockInternal(bpm)

        self.sequencer = Sequencer(self.masterClock, output)
        self.sequencer.onFinished(self._finshed)

        self._running = False
        self._clockPrinter = None

    def addNote(self, startTimeCode, note, channel):

        self.sequencer.addNote(startTimeCode, note, channel)

    def printClock(self, resolution=ClockPrinter.Resolution.Quarter):

        if self._clockPrinter:
            del self._clockPrinter

        self._clockPrinter = ClockPrinter(self.masterClock, resolution)

    def run(self):

        if not isinstance(self.masterClock, ClockInternal):
            print('not an internal clock')
            return

        self.masterClock.start()
        self.waitForFinished()
        self.masterClock.stop()

    def waitForFinished(self):

        self._running = True

        try:
            while self._running:
                time.sleep(1)    # time here does not matter for clock timimg
        except KeyboardInterrupt:
            self._running = False
            print()
            print('user interruption')

    def _finshed(self):

        self._running = False
