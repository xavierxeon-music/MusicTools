#!/usr/bin/env python3

class Note:

    def __init__(self, pitch, duration, velocity=127):

        self.pitch = pitch
        self.duration = duration
        self.velocity = velocity

    @staticmethod
    def pitch(note):

        noteValues = {
            'C': 0,
            'C#': 1,
            'D': 2,
            'D#': 3,
            'E': 4,
            'F': 5,
            'F#': 6,
            'G': 7,
            'G#': 8,
            'A': 9,
            'A#': 10,
            'B': 11
        }

        root = note[:-1]
        # 60 equals C4
        octave = int(note[-1:]) + 1
        value = noteValues[root] + (12 * octave)
        return value

    @staticmethod
    def note(pitch):

        relPitchValues = {
            0: 'C',
            1: 'C#',
            2: 'D',
            3: 'D#',
            4: 'E',
            5: 'F',
            6: 'F#',
            7: 'G',
            8: 'G#',
            9: 'A',
            10: 'A#',
            11: 'B'
        }

        relPitch = pitch % 12
        root = pitch - relPitch
        # 60 equals C4
        octave = int(root / 12) - 1
        text = relPitchValues[relPitch] + str(octave)
        return text

    def __str__(self):

        return '(p{0} &{1} @{2} )'.format(Note.note(self.pitch), self.duration, self.velocity)
