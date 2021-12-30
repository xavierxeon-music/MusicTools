#!/usr/bin/env python3

from time import time_ns, sleep
from threading import Thread

from .clock_abstract import ClockAbstract


class ClockInternal(ClockAbstract):

    verbose = False

    class _Clock(Thread):

        def __init__(self, bpm: int, callback):

            Thread.__init__(self)
            self._bpm = bpm
            self._callback = callback
            self._running = False

        def run(self):

            self._running = True
            nsPerTick = 60 * 1000 * 1000 * 1000 / (self._bpm * 4 * 6)

            if ClockInternal.verbose:
                print('start timer loop, bpm = ', self._bpm)

            def usleep(uSecs): return sleep(uSecs/1000000.0)

            start = time_ns()
            while self._running:
                now = time_ns()
                usleep(1)
                duration = now - start
                if duration >= nsPerTick:
                    waitedTooMuch = duration - nsPerTick
                    start = now - waitedTooMuch
                    self._callback()

            if ClockInternal.verbose:
                print('end timer loop')

        def stop(self):

            self._running = False

    def __init__(self, beatsPerMinute: int):

        ClockAbstract.__init__(self)
        self.beatsPerMinute = beatsPerMinute
        self._clock = None

    def __del__(self):

        if self._clock:
            self._clock.stop()
            del self._clock

    def start(self):

        self._setState(ClockAbstract.State.Start)
        self._setSongPosition(1)

        self._clock = ClockInternal._Clock(self.beatsPerMinute, self._clockTick)
        self._clock.start()

    def stop(self):

        self._setState(ClockAbstract.State.Stop)
        if self._clock:
            self._clock.stop()
            del self._clock
            self._clock = None
