#ifndef MidiCommonH
#define MidiCommonH

#include <MusicTools.h>

namespace Midi
{
   using Channel = uint8_t;
   using Velocity = uint8_t;

   // see https://ccrma.stanford.edu/~gary/controllers/midi.html
   const static float msPerByte = 31250.0 / (8.0 * 1000.0); //31250 bits per second

   struct Event
   {
      enum Type : uint8_t
      {
         Unknown = 0x00,
         NoteOff = 0x80,
         NoteOn = 0x90,
         ControlChange = 0xB0,
         SysExStart = 0xF0,
         SysExEnd = 0xF7
      };
   };

   struct ControllerMessage
   {
      enum Type : uint8_t
      {
         BankSelect = 0x00,
         ModWheel = 0x01,
         BreathController = 0x02,
         FootController = 0x04,
         PortamentoTime = 0x05,
         ChannelVolume = 0x07,
         Balance = 0x08,
         // START undefined in standard
         RememberBlock = 0x14,
         RememberApply = 0x15,
         RememberRequest = 0x16,
         Undefined04 = 0x17,
         Undefined05 = 0x18,
         Undefined06 = 0x19,
         Undefined07 = 0x1A,
         Undefined08 = 0x1B,
         Undefined09 = 0x1C,
         Undefined10 = 0x1D,
         Undefined11 = 0x1E,
         Undefined12 = 0x1F,
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
         // END undefined in standard
         AllNotesOff = 0x78
      };
   };

} // namespace Midi

#include "MidiCommon.hpp"

#endif // MidiCommonH
