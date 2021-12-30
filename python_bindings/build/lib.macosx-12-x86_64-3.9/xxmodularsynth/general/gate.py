#!/usr/bin/env python3

from .duration import Duration
from .note import Note


class Gate(Note):

    def __init__(self, pitchOffset, duration=Duration.Sixteenth, basePitch=60):

        Note.__init__(self, basePitch + pitchOffset, duration, 127)

    def __str__(self):

        return '(t)'
