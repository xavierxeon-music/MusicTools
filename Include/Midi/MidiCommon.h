#ifndef MidiCommonH
#define MidiCommonH

#include <Global.h>

namespace Midi
{
   using Channel = uint8_t;
   using Velocity = uint8_t;

   enum class Event
   {
      Unkown = 0x00,
      NoteOff = 0x80,
      NoteOn = 0x90,
      ControlChange = 0xB0,
      SysExStart = 0xF0,
      SysExEnd = 0xF7
   };

   enum class ControllerMessage
   {
      BankSelect = 0x00,
      ModWheel = 0x01,
      BreathController = 0x02,
      FootController = 0x04,
      PortamentoTime = 0x05,
      ChannelVolume = 0x07,
      Balance = 0x08,
      User01 = 0x66,
      User02 = 0x67,
      User03 = 0x68,
      User04 = 0x69,
      User05 = 0x6A,
      User06 = 0x6B,
      User07 = 0x6C,
      User08 = 0x6D,
      User09 = 0x6E,
      User10 = 0x6F,
      User11 = 0x70,
      User12 = 0x71,
      User13 = 0x72,
      User14 = 0x73,
      User15 = 0x74,
      User16 = 0x75,
      User17 = 0x76,
      User18 = 0x77,
      AllNotesOff = 0x78
   };

   using Buffer = std::vector<uint8_t>;

} // namespace Midi

#include "MidiCommon.hpp"

#endif // MidiCommonH
