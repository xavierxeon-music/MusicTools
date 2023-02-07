INCLUDEPATH += \
   $$PWD/Include \

include(_fourier/ffft.pri)
include(RememberDummy/Remember.pri)

HEADERS += \
   $$PWD/DoubleBuffer.h \
   $$PWD/Include/Abstract/AbstractChain.h \
   $$PWD/Include/Abstract/AbstractEffect.h \
   $$PWD/Include/Abstract/AbstractOscilator.h \
   $$PWD/Include/Abstract/AbstractSegmentCrawler.h \
   $$PWD/Include/Abstract/AbstractSoundSource.h \
   $$PWD/Include/Blocks/BioFeedbackDummy.h \
   $$PWD/Include/Blocks/ChainOnOff.h \
   $$PWD/Include/Blocks/ChainRandom.h \
   $$PWD/Include/Blocks/Contour.h \
   $$PWD/Include/Blocks/CvSwitch.h \
   $$PWD/Include/Blocks/Grooves.h \
   $$PWD/Include/Colour.h \
   $$PWD/Include/Debug.h \
   $$PWD/Include/Effect/Compressor.h \
   $$PWD/Include/Effect/StateVariableFilter.h \
   $$PWD/Include/Maths.h \
   $$PWD/Include/Midi/MidiCommon.h \
   $$PWD/Include/Midi/MidiFile.h \
   $$PWD/Include/Midi/MidiFileReader.h \
   $$PWD/Include/Midi/MidiFileWriter.h \
   $$PWD/Include/Midi/MidiInterfaceInput.h \
   $$PWD/Include/Midi/MidiInterfaceOutput.h \
   $$PWD/Include/Midi/MidiParser.h \
   $$PWD/Include/Midi/MidiToolGate.h \
   $$PWD/Include/Midi/MidiToolTempo.h \
   $$PWD/Include/Music/Note.h \
   $$PWD/Include/Music/Tempo.h \
   $$PWD/Include/Music/TimeCode.h \
   $$PWD/Include/MusicTools.h \
   $$PWD/Include/Sound/FunctionTable.h \
   $$PWD/Include/Sound/GateOscilator.h \
   $$PWD/Include/Sound/Noise.h \
   $$PWD/Include/Sound/Sample.h \
   $$PWD/Include/Sound/SampleOscilator.h \
   $$PWD/Include/Sound/SampleRecorder.h \
   $$PWD/Include/Sound/SoundMesh.h \
   $$PWD/Include/Sound/StandardTable.h \
   $$PWD/Include/Sound/WaveTable.h \
   $$PWD/Include/Sound/WaveTableMorpher.h \
   $$PWD/Include/Sound/WaveTableOscilator.h \
   $$PWD/Include/Tools/BoolField.h \
   $$PWD/Include/Tools/Counter.h \
   $$PWD/Include/Tools/DoubleBuffer.h \
   $$PWD/Include/Tools/FastRandom.h \
   $$PWD/Include/Tools/Flank.h \
   $$PWD/Include/Tools/File.h \
   $$PWD/Include/Tools/Glide.h \
   $$PWD/Include/Tools/Prompt.h \
   $$PWD/Include/Tools/Range.h \
   $$PWD/Include/Tools/RingBuffer.h \
   $$PWD/Include/Tools/SevenBit.h \
   $$PWD/Include/Tools/Text.h \
   $$PWD/Include/Tools/Variable.h \
   $$PWD/Include/Utility/RandomWalk.h \
   $$PWD/Include/Utility/Spectrum.h \
   $$PWD/Include/Utility/SquareSignal.h \
   $$PWD/Prompt.hpp
    
HEADERS += \
   $$PWD/Debug.hpp \
   $$PWD/BioFeedbackDummy.hpp \
   $$PWD/BoolField.hpp \
   $$PWD/ChainOnOff.hpp \
   $$PWD/ChainRandom.hpp \
   $$PWD/Compressor.hpp \
   $$PWD/Contour.hpp \
   $$PWD/Counter.hpp \
   $$PWD/CvSwitch.hpp \
   $$PWD/DoubleBuffer.hpp \
   $$PWD/FastRandom.hpp \
   $$PWD/Flank.hpp \
   $$PWD/File.hpp \
   $$PWD/FunctionTable.hpp \
   $$PWD/GateOscilator.hpp \
   $$PWD/Glide.hpp \
   $$PWD/Grooves.hpp \
   $$PWD/MidiFile.hpp \
   $$PWD/MidiFileReader.hpp \
   $$PWD/MidiFileWriter.hpp \
   $$PWD/MidiInterfaceInput.hpp \
   $$PWD/MidiInterfaceOutput.hpp \
   $$PWD/MidiParser.hpp \
   $$PWD/MidiToolGate.hpp \
   $$PWD/MidiToolTempo.hpp \
   $$PWD/MusicTools.hpp \
   $$PWD/Noise.hpp \
   $$PWD/RandomWalk.hpp \
   $$PWD/Range.hpp \
   $$PWD/RingBuffer.hpp \
   $$PWD/Sample.hpp \
   $$PWD/SampleOscilator.hpp \
   $$PWD/SampleRecorder.hpp \
   $$PWD/SevenBit.hpp \
   $$PWD/SoundMesh.hpp \
   $$PWD/SquareSignal.hpp \
   $$PWD/StandardTable.hpp \
   $$PWD/StateVariableFilter.hpp \
   $$PWD/Tempo.hpp \
   $$PWD/Text.hpp \
   $$PWD/TimeCode.hpp \
   $$PWD/Variable.hpp \
   $$PWD/WaveTable.hpp \
   $$PWD/WaveTableMorpher.hpp \
   $$PWD/WaveTableOscilator.hpp


SOURCES += \
    $$PWD/AbstractChain.cpp \
   $$PWD/AbstractSegmentCrawler.cpp \
   $$PWD/AbstractSoundSource.cpp \
   $$PWD/Colour.cpp \
   $$PWD/Spectrum.cpp \
   $$PWD/AbstractEffect.cpp \
   $$PWD/AbstractOscilator.cpp \
   $$PWD/Maths.cpp \
   $$PWD/Note.cpp \


