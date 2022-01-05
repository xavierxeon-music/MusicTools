#!/usr/bin/env python3

class ClockAbstract:

    class State:

        Stop = 0
        Start = 1
        Continue = 2

        names = {
            Stop: 'Stop',
            Start: 'Start',
            Continue: 'Continue'
        }

    def __init__(self):

        self.state = ClockAbstract.State.Stop
        self.position = 1

        self._stateCallbackList = list()
        self._positionCallbackList = list()
        self._tickCallbackList = list()

        self._tickCounter = 0
        self._last_time = None

    def onStateChange(self, callback):
        """
        callback must be foo(state)
        """
        self._stateCallbackList.append(callback)

    def onPositionChange(self, callback):
        """
        callback must be foo(position)
        """
        self._positionCallbackList.append(callback)

    def onTick(self, callback):
        """
        callback must be foo()
        """
        self._tickCallbackList.append(callback)

    def _setState(self, state):

        self.state = state
        for callback in self._stateCallbackList:
            callback(state)

    def _clockTick(self):

        self._tickCounter += 1

        if self._tickCounter >= 6:
            self._setSongPosition(self.position + 1)

        for callback in self._tickCallbackList:
            callback()

    def _setSongPosition(self, position):

        self.position = position
        self._tickCounter = 0

        for callback in self._positionCallbackList:
            callback(position)
