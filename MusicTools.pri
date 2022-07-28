INCLUDEPATH += \
   $$PWD/Include

include(ffft/ffft.pri)

HEADERS += \
   $$PWD/AudioFile.hpp \
   $$PWD/DoubleBuffer.hpp \
   $$PWD/Include/Abstract/AbstractEffect.h \
   $$PWD/Include/Abstract/AbstractOscilator.h \
   $$PWD/Include/Blocks/CvSwitch.h \
   $$PWD/Include/Blocks/PolyRamp.h \
   $$PWD/Include/Blocks/Trapezoid.h \
   $$PWD/Include/Effect/Compressor.h \
   $$PWD/Include/Effect/Revoice.h \
   $$PWD/Include/Effect/StateVariableFilter.h \
   $$PWD/Include/Maths.h \
   $$PWD/Include/Midi/MidiCommon.h \
   $$PWD/Include/Midi/MidiInterfaceInput.h \
   $$PWD/Include/Midi/MidiInterfaceOutput.h \
   $$PWD/Include/Midi/MidiTargetDoepferQuad.h \
   $$PWD/Include/Midi/MidiTargetFlameCC.h \
   $$PWD/Include/Midi/MidiToolGate.h \
   $$PWD/Include/Midi/MidiToolTempo.h \
   $$PWD/Include/Music/Note.h \
   $$PWD/Include/Music/Tempo.h \
   $$PWD/Include/Music/TimeCode.h \
   $$PWD/Include/MusicTools.h \
   $$PWD/Include/MusicTools.h \
   $$PWD/Include/Sound/AudioFile.h \
   $$PWD/Include/Sound/FunctionTable.h \
   $$PWD/Include/Sound/GateOscilator.h \
   $$PWD/Include/Sound/SoundMesh.h \
   $$PWD/Include/Sound/Spectrum.h \
   $$PWD/Include/Sound/StandardTable.h \
   $$PWD/Include/Sound/WaveTable.h \
   $$PWD/Include/Sound/WaveTableMorpher.h \
   $$PWD/Include/Tools/BoolField.h \
   $$PWD/Include/Tools/Convert.h \
   $$PWD/Include/Tools/Counter.h \
   $$PWD/Include/Tools/DoubleBuffer.h \
   $$PWD/Include/Tools/FastRandom.h \
   $$PWD/Include/Tools/Glide.h \
   $$PWD/Include/Tools/Range.h \
   $$PWD/Include/Tools/RingBuffer.h \
   $$PWD/Include/Tools/SevenBit.h \
   $$PWD/Include/Tools/SquareSignal.h \
   $$PWD/Include/Tools/Variable.h \
    $$PWD/Revoice.hpp

    
HEADERS += \   
   $$PWD/BoolField.hpp \
   $$PWD/Compressor.hpp \
   $$PWD/Convert.hpp \
   $$PWD/Counter.hpp \
   $$PWD/CvSwitch.hpp \
   $$PWD/FastRandom.hpp \
   $$PWD/FunctionTable.hpp \
   $$PWD/GateOscilator.hpp \
   $$PWD/Glide.hpp \
   $$PWD/MidiInterfaceInput.hpp \
   $$PWD/MidiInterfaceOutput.hpp \
   $$PWD/MidiTargetDoepferQuad.hpp \
   $$PWD/MidiTargetFlameCC.hpp \
   $$PWD/MidiToolGate.hpp \
   $$PWD/MidiToolTempo.hpp \
   $$PWD/MusicTools.hpp \
   $$PWD/PolyRamp.hpp \
   $$PWD/Range.hpp \
   $$PWD/RingBuffer.hpp \
   $$PWD/SevenBit.hpp \
   $$PWD/SoundMesh.hpp \
   $$PWD/SquareSignal.hpp \
   $$PWD/StandardTable.hpp \
   $$PWD/StateVariableFilter.hpp \
   $$PWD/Tempo.hpp \
   $$PWD/TimeCode.hpp \
   $$PWD/Trapezoid.hpp \
   $$PWD/Variable.hpp   \
   $$PWD/WaveTable.hpp \
   $$PWD/WaveTableMorpher.hpp \


SOURCES += \
   $$PWD/AbstractEffect.cpp \
   $$PWD/AbstractOscilator.cpp \
   $$PWD/Maths.cpp \
   $$PWD/Note.cpp \
   $$PWD/Spectrum.cpp \
