#ifndef MidiCommonH
#define MidiCommonH

#include <MusicTools.h>

namespace Midi
{
   using Channel = uint8_t; // channels from 1 to 16
   using Velocity = uint8_t;
   using SongPosition = uint16_t;

   // see https://ccrma.stanford.edu/~gary/controllers/midi.html
   const static float msPerByte = 1000.0 / 3125.0; // -> 3125 bytes per second

   enum Event : uint8_t
   {
      Unknown = 0x00,
      // non system events
      NoteOff = 0x80,
      NoteOn = 0x90,
      PolyKeyPressure = 0xA0,
      ControlChange = 0xB0,
      ProgrammChange = 0xC0,
      ChannelPressure = 0xD0,
      PitchBend = 0xE0,
      // system common
      System = 0xF0,
      TimeCode = 0xF1,
      SongPositionPointer = 0xF2,
      SongSelect = 0xF3,
      TuneRequest = 0xF6,
      SysExEnd = 0xF7,
      // system real time
      Clock = 0xF8,
      UndefinedA = 0xF9,
      Start = 0xFA,
      Continue = 0xFB,
      Stop = 0xFC,
      UndefinedB = 0xFD,
      ActiveSensinig = 0xFE,
      Reset = 0xFF,
      Meta = 0xFF // for midi files
   };

   struct Manufacturer
   {
      const static uint8_t EducationalUse = 0x7D;
   };

   enum MetaEvent : uint8_t // for midi files
   {
      MetaUnkown = 0x00,
      Text = 0x01,
      Copyright = 0x02,
      TrackName = 0x03,
      InstrumentName = 0x04,
      Lyric = 0x05,
      Marker = 0x06,
      CuePoint = 0x07,
      ChannelPrefix = 0x20,
      MidiPort = 0x21,
      EndOfTrack = 0x2f,
      LiveTag = 0x48,
      Tempo = 0x51,
      SMPTEOffset = 0x54,
      TimeSignature = 0x58,
      KeySignature = 0x59
   };

   enum ControllerMessage : uint8_t
   {
      BankSelect = 0x00,
      ModWheel = 0x01,
      BreathController = 0x02,
      FootController = 0x04,
      PortamentoTime = 0x05,
      ChannelVolume = 0x07,
      Balance = 0x08,
      Pan = 0x0A,
      ExpressionController = 0x0B,
      EffectControl1 = 0x0C,
      EffectControl2 = 0x0D,
      // START undefined in standard
      RememberInit = 0x14,
      RememberBlock = 0x15,
      RememberApply = 0x16,
      RememberRequest = 0x17,
      DataInit = 0x18,
      DataBlock = 0x19,
      DataApply = 0x1A,
      Undefined08 = 0x1B,
      Undefined09 = 0x1C,
      Undefined10 = 0x1D,
      Undefined11 = 0x1E,
      Undefined12 = 0x1F,
      // END undefined in standard
      DamperPedal = 0x40,
      Portamento = 0x41,
      Sostenuto = 0x42,
      SoftPedal = 0x42,
      LegatoSwitch = 0x44,
      // START undefined in standard
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
      AllSoundsOff = 0x78,
      ResetAllControlers = 0x79,
      AllNotesOff = 0x78
   };

   enum class Playback : uint8_t
   {
      Start,
      Continue,
      Stop
   };

   struct Device
   {
      enum Channel : uint8_t
      {
         Splitter = 0,
         DopeferQuad1 = 1,
         DopeferQuad2 = 2,
         DopeferQuad3 = 3,
         DopeferQuad4 = 4,
         KeyStep1 = 5,
         KeyStep2 = 6,
         KeyStep3 = 7,
         KeyStep4 = 8,
         Daisy = 9,
         DrumTrigger = 10,
         VCVRack = 11,
         FlameCC = 12,
         BitBox = 13,
         BitBoxMicro = 14,
         UnusedA = 15,
         UnusedB = 16
      };
   };

} // namespace Midi

#endif // MidiCommonH
