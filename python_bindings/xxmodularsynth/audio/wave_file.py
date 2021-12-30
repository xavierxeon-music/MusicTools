#!/usr/bin/env python3

import wave
import os
import struct


class WaveFile:

    byteFormat = {1: 'b', 2: 'h', 4: 'i'}

    @staticmethod
    def read_mono(fileName):

        center = list()

        if not os.path.exists(fileName):
            return center

        print(fileName)
        with wave.open(fileName, 'rb') as wavfile:
            if 1 != wavfile.getnchannels():
                return center

            frameCount = wavfile.getnframes()
            raw = wavfile.readframes(frameCount)
            sampleWidth = wavfile.getsampwidth()
            maxSize = float(128**sampleWidth)
            format = '<' + str(frameCount) + WaveFile.byteFormat[wavfile.getsampwidth()]
            data = struct.unpack(format, raw)

        for index in range(frameCount):
            centerData = float(data[index]) / maxSize
            center.append(centerData)

        return center

    @staticmethod
    def read_stereo(fileName):

        left = list()
        right = list()

        if not os.path.exists(fileName):
            return [left, right]

        print(fileName)
        with wave.open(fileName, 'rb') as wavfile:
            if 2 != wavfile.getnchannels():
                return [left, right]

            frameCount = wavfile.getnframes()
            raw = wavfile.readframes(frameCount)
            sampleWidth = wavfile.getsampwidth()
            maxSize = float(128**sampleWidth)
            format = '<' + str(2 * frameCount) + WaveFile.byteFormat[sampleWidth]
            data = struct.unpack(format, raw)

        for index in range(frameCount):
            leftIndex = (2 * index) + 0
            leftData = float(data[leftIndex]) / maxSize
            left.append(leftData)

            rightIndex = (2 * index) + 1
            rightData = float(data[rightIndex]) / maxSize
            right.append(rightData)

        return [left, right]

    @staticmethod
    def write_stereo(fileName, left, right, sampleWidth=2):

        if len(left) != len(right):
            return

        frameCount = len(left)
        maxSize = float(128**sampleWidth)

        data = list()
        for index in range(frameCount):
            leftValue = int(left[index] * maxSize)
            data.append(leftValue)

            rigthValue = int(right[index] * maxSize)
            data.append(rigthValue)

        format = '<' + str(2 * frameCount) + WaveFile.byteFormat[sampleWidth]
        data = struct.pack(format, *data)

        with wave.open(fileName, 'wb') as wavfile:
            wavfile.setnchannels(2)
            wavfile.setsampwidth(sampleWidth)
            wavfile.setframerate(48000)
            wavfile.setnframes(frameCount)
            wavfile.writeframesraw(data)
