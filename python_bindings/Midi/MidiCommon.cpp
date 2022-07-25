#include <pybind11/pybind11.h>

#include <Midi/MidiCommon.h>

void init_MidiCommon(pybind11::module_& module)
{
   pybind11::enum_<Midi::Event> eventType(module, "MidiEvent");
   eventType.value("Unknown", Midi::Event::Unknown);
   eventType.value("NoteOff", Midi::Event::NoteOff);
   eventType.value("NoteOn", Midi::Event::NoteOn);
   eventType.value("ControlChange", Midi::Event::ControlChange);
   eventType.value("System", Midi::Event::System);
   eventType.value("TimeCode", Midi::Event::TimeCode);
   eventType.value("SongPositionPointer", Midi::Event::SongPositionPointer);
   eventType.value("Clock", Midi::Event::Clock);
   eventType.value("Start", Midi::Event::Start);
   eventType.value("Continue", Midi::Event::Continue);
   eventType.value("Stop", Midi::Event::Stop);
   eventType.export_values();

   pybind11::enum_<Midi::ControllerMessage> controllMessageType(module, "MidiControllerMessage");
   controllMessageType.value("BankSelect", Midi::ControllerMessage::BankSelect);
   controllMessageType.value("ModWheel", Midi::ControllerMessage::ModWheel);
   controllMessageType.value("BreathController", Midi::ControllerMessage::BreathController);
   controllMessageType.value("FootController", Midi::ControllerMessage::FootController);
   controllMessageType.value("PortamentoTime", Midi::ControllerMessage::PortamentoTime);
   controllMessageType.value("ChannelVolume", Midi::ControllerMessage::ChannelVolume);
   controllMessageType.value("Balance", Midi::ControllerMessage::Balance);
   // START undefined in standard
   controllMessageType.value("RememberInit", Midi::ControllerMessage::RememberInit);
   controllMessageType.value("RememberBlock", Midi::ControllerMessage::RememberBlock);
   controllMessageType.value("RememberApply", Midi::ControllerMessage::RememberApply);
   controllMessageType.value("RememberRequest", Midi::ControllerMessage::RememberRequest);
   controllMessageType.value("DataInit", Midi::ControllerMessage::DataInit);
   controllMessageType.value("DataBlock", Midi::ControllerMessage::DataBlock);
   controllMessageType.value("DataApply", Midi::ControllerMessage::DataApply);
   controllMessageType.value("Undefined08", Midi::ControllerMessage::Undefined08);
   controllMessageType.value("Undefined09", Midi::ControllerMessage::Undefined09);
   controllMessageType.value("Undefined10", Midi::ControllerMessage::Undefined10);
   controllMessageType.value("Undefined11", Midi::ControllerMessage::Undefined11);
   controllMessageType.value("Undefined12", Midi::ControllerMessage::Undefined12);
   controllMessageType.value("User01", Midi::ControllerMessage::User01);
   controllMessageType.value("User02", Midi::ControllerMessage::User02);
   controllMessageType.value("User03", Midi::ControllerMessage::User03);
   controllMessageType.value("User04", Midi::ControllerMessage::User04);
   controllMessageType.value("User05", Midi::ControllerMessage::User05);
   controllMessageType.value("User06", Midi::ControllerMessage::User06);
   controllMessageType.value("User07", Midi::ControllerMessage::User07);
   controllMessageType.value("User08", Midi::ControllerMessage::User08);
   controllMessageType.value("User09", Midi::ControllerMessage::User09);
   controllMessageType.value("User10", Midi::ControllerMessage::User10);
   controllMessageType.value("User11", Midi::ControllerMessage::User11);
   controllMessageType.value("User12", Midi::ControllerMessage::User12);
   controllMessageType.value("User13", Midi::ControllerMessage::User13);
   controllMessageType.value("User14", Midi::ControllerMessage::User14);
   controllMessageType.value("User15", Midi::ControllerMessage::User15);
   controllMessageType.value("User16", Midi::ControllerMessage::User16);
   controllMessageType.value("User17", Midi::ControllerMessage::User17);
   controllMessageType.value("User18", Midi::ControllerMessage::User18);
   // END undefined in standard
   controllMessageType.value("AllNotesOff", Midi::ControllerMessage::AllNotesOff);
   controllMessageType.export_values();
}