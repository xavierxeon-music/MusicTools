#!/usr/bin/env python3

# realtive to song position
class Duration:

    Sixteenth = 1
    Eighth = 2
    Quarter = 4
    Half = 8
    Full = 16

    @staticmethod
    def isSixteenth():

        return True

    @staticmethod
    def isEighth(position):

        return Duration._test(position, Duration.Eighth)

    @staticmethod
    def isQuarter(position):

        return Duration._test(position, Duration.Quarter)

    @staticmethod
    def isHalf(position):

        return Duration._test(position, Duration.Half)

    @staticmethod
    def isFull(position):

        return Duration._test(position, Duration.Full)

    @staticmethod
    def _test(position, division):

        test = (position - 1) % division
        return (0 == test)
