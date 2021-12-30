#!/usr/bin/env python3

import collections


class Rhythm:

    @staticmethod
    def euclidian(pulses, steps, rotation=0):

        if pulses > steps:
            return list()

        rhythm = list()
        bucket = (steps - pulses)

        for _ in range(steps):

            bucket += pulses

            if bucket >= steps:
                bucket -= steps
                rhythm.append(True)
            else:
                rhythm.append(False)

        if rotation != 0:
            rhythm2 = collections.deque(rhythm)
            rhythm2.rotate(rotation)
            rhythm = list(rhythm2)

        return rhythm
