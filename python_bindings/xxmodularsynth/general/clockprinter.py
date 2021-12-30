#!/usr/bin/env python3

from .clock_abstract import ClockAbstract
from .timecode import TimeCode


class ClockPrinter:

    class Resolution:

        Full = 1
        Quarter = 4
        Bar = 16

    def __init__(self, clock, resolution=Resolution.Quarter):

        clock.onStateChange(self.stateChange)
        clock.onPositionChange(self.songPostion)

        self._resolution = resolution
        self._posCount = resolution

    def stateChange(self, state: ClockAbstract.State):

        print(ClockAbstract.State.names[state])

    def songPostion(self, position):

        if self._posCount == self._resolution:
            timeCode = TimeCode.fromPosition(position)
            if ClockPrinter.Resolution.Full == self._resolution:
                print(timeCode)
            elif ClockPrinter.Resolution.Quarter == self._resolution:
                text = '[{0}.{1}._]'.format(timeCode.bar, timeCode.quarter)
                print(text)
            elif ClockPrinter.Resolution.Bar == self._resolution:
                text = '[ {0}._._]'.format(timeCode.bar, timeCode.quarter)
                print(text)
            self._posCount = 1
        else:
            self._posCount += 1
