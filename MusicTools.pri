INCLUDEPATH += \
   $$PWD/Include \

include(ffft/ffft.pri)

HEADERS += \
   $$PWD/RememberDummy/Remember.h \
   $$PWD/RememberDummy/RememberArray.h \
   $$PWD/RememberDummy/RememberList.h \
   $$PWD/Include/Blocks/TrackerProject.h \
   $$PWD/Include/Blocks/Trapezoid.h \
   $$PWD/Include/Blocks/PolyRamp.h \
   $$PWD/Include/Blocks/CvSwitch.h \
   $$PWD/Include/Blocks/BioFeedbackDummy.h \
   $$PWD/Include/Blocks/Sequencer.h \
   $$PWD/Include/Blocks/TrackerLane.h \
   $$PWD/Include/Abstract/AbstractEffect.h \
   $$PWD/Include/Abstract/AbstractOscilator.h \
   $$PWD/Include/Abstract/AbstractSoundSource.h \
   $$PWD/Include/Music/TimeCode.h \
   $$PWD/Include/Music/Tempo.h \
   $$PWD/Include/Music/Note.h \
   $$PWD/Include/Tools/BoolField.h \
   $$PWD/Include/Tools/Range.h \
   $$PWD/Include/Tools/Glide.h \
   $$PWD/Include/Tools/Text.h \
   $$PWD/Include/Tools/Counter.h \
   $$PWD/Include/Tools/FastRandom.h \
   $$PWD/Include/Tools/SevenBit.h \
   $$PWD/Include/Tools/File.h \
   $$PWD/Include/Tools/Variable.h \
   $$PWD/Include/Tools/DoubleBuffer.h \
   $$PWD/Include/Tools/RingBuffer.h \
   $$PWD/Include/Midi/MidiFile.h \
   $$PWD/Include/Midi/MidiFileWriter.h \
   $$PWD/Include/Midi/MidiToolGate.h \
   $$PWD/Include/Midi/MidiTargetDoepferQuad.h \
   $$PWD/Include/Midi/MidiToolTempo.h \
   $$PWD/Include/Midi/MidiInterfaceOutput.h \
   $$PWD/Include/Midi/MidiFileReader.h \
   $$PWD/Include/Midi/MidiInterfaceInput.h \
   $$PWD/Include/Midi/MidiCommon.h \
   $$PWD/Include/Midi/MidiTargetFlameCC.h \
   $$PWD/Include/MusicTools.h \
   $$PWD/Include/Effect/StateVariableFilter.h \
   $$PWD/Include/Effect/Compressor.h \
   $$PWD/Include/Maths.h \
   $$PWD/Include/Sound/WaveTableMorpher.h \
   $$PWD/Include/Sound/Noise.h \
   $$PWD/Include/Sound/WaveTable.h \
   $$PWD/Include/Sound/WaveTableOscilator.h \
   $$PWD/Include/Sound/SampleRecorder.h \
   $$PWD/Include/Sound/FunctionTable.h \
   $$PWD/Include/Sound/GateOscilator.h \
   $$PWD/Include/Sound/SoundMesh.h \
   $$PWD/Include/Sound/SampleOscilator.h \
   $$PWD/Include/Sound/Sample.h \
   $$PWD/Include/Sound/StandardTable.h \
   $$PWD/Include/Utility/RandomWalk.h \
   $$PWD/Include/Utility/Spectrum.h \
   $$PWD/Include/Utility/SquareSignal.h \
   $$PWD/DoubleBuffer.h \
 
    
HEADERS += \
   $$PWD/BioFeedbackDummy.hpp \
   $$PWD/BoolField.hpp \
   $$PWD/Compressor.hpp \
   $$PWD/Counter.hpp \
   $$PWD/CvSwitch.hpp \
   $$PWD/DoubleBuffer.hpp \
   $$PWD/FastRandom.hpp \
   $$PWD/File.hpp \
   $$PWD/FunctionTable.hpp \
   $$PWD/GateOscilator.hpp \
   $$PWD/Glide.hpp \
   $$PWD/MidiFile.hpp \
   $$PWD/MidiFileReader.hpp \
   $$PWD/MidiFileWriter.hpp \
   $$PWD/MidiInterfaceInput.hpp \
   $$PWD/MidiInterfaceOutput.hpp \
   $$PWD/MidiTargetDoepferQuad.hpp \
   $$PWD/MidiTargetFlameCC.hpp \
   $$PWD/MidiToolGate.hpp \
   $$PWD/MidiToolTempo.hpp \
   $$PWD/MusicTools.hpp \
   $$PWD/Noise.hpp \
   $$PWD/PolyRamp.hpp \
   $$PWD/RandomWalk.hpp \
   $$PWD/Range.hpp \
   $$PWD/RememberDummy/Remember.hpp \
   $$PWD/RememberDummy/RememberArray.hpp \
   $$PWD/RememberDummy/RememberList.hpp \
   $$PWD/RingBuffer.hpp \
   $$PWD/Sample.hpp \
   $$PWD/SampleOscilator.hpp \
   $$PWD/SampleRecorder.hpp \
   $$PWD/Sequencer.hpp \
   $$PWD/SevenBit.hpp \
   $$PWD/SoundMesh.hpp \
   $$PWD/SquareSignal.hpp \
   $$PWD/StandardTable.hpp \
   $$PWD/StateVariableFilter.hpp \
   $$PWD/Tempo.hpp \
   $$PWD/Text.hpp \
   $$PWD/TimeCode.hpp \
   $$PWD/TrackerLane.hpp \
   $$PWD/TrackerProject.hpp \
   $$PWD/Trapezoid.hpp \
   $$PWD/Variable.hpp \
   $$PWD/WaveTable.hpp \
   $$PWD/WaveTableMorpher.hpp \
   $$PWD/WaveTableOscilator.hpp \


SOURCES += \
   $$PWD/AbstractSoundSource.cpp \
   $$PWD/Spectrum.cpp \
   $$PWD/AbstractEffect.cpp \
   $$PWD/AbstractOscilator.cpp \
   $$PWD/Maths.cpp \
   $$PWD/Note.cpp \

