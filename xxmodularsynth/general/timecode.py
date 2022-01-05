#!/usr/bin/env python3

class TimeCode:

    def __init__(self, bar=1, quarter=1, subDivision=1):

        self.bar = bar
        self.quarter = quarter
        self.subDivision = subDivision

    def set(self, position):

        position -= 1

        back = position % 4
        mid = ((position - back) / 4) % 4
        front = (((position - back) / 4) - mid) / 4

        self.bar = int(front) + 1
        self.quarter = int(mid) + 1
        self.subDivision = int(back) + 1

    def position(self):

        front = (self.bar - 1) * 16
        mid = (self.quarter - 1) * 4
        back = (self.subDivision - 1)

        position = 1 + front + mid + back
        return position

    @staticmethod
    def fromPosition(position):

        timeCode = TimeCode()
        timeCode.set(position)

        return timeCode

    def __str__(self):

        return '[{0}.{1}.{2}]'.format(self.bar, self.quarter, self.subDivision)
