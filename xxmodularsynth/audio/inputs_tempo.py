#!/usr/bin/env python3

from xxmodularsynth.base import Tempo

from .input_gate import InputGate


class InputsTempo(Tempo):

    def __init__(self, indexTick, indexReset, device):

        Tempo.__init__(self)

        self._clockTickGate = InputGate(indexTick, device)
        self._clockResetGate = InputGate(indexReset, device)

        self._tickActive = False

    def isRunning(self):

        return self.isRunningOrFirstTick()

    def advance(self, audioRate):

        #print('tempo advance')
        if self._clockResetGate.isActive():
            Tempo.clockReset(self)
            self._tickActive = False
        elif self._clockTickGate.isActive():
            if not self._tickActive:
                Tempo.clockTick(self)
            self._tickActive = True
        else:
            Tempo.advance(self, audioRate)
            self._tickActive = False
