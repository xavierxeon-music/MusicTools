#include <Tools/Colour.h>

const Color::NoteMap Color::noteMap = {{Note::C, Color{255, 255, 255}},
                                       {Note::Cs, Color{90, 90, 90}},
                                       {Note::D, Color{255, 0, 0}},
                                       {Note::Ds, Color{90, 0, 0}},
                                       {Note::E, Color{255, 30, 200}},
                                       {Note::F, Color{0, 0, 255}},
                                       {Note::Fs, Color{0, 0, 90}},
                                       {Note::G, Color{0, 255, 0}},
                                       {Note::Gs, Color{0, 90, 0}},
                                       {Note::A, Color{255, 255, 0}},
                                       {Note::As, Color{90, 90, 0}},
                                       {Note::B, Color{0, 0, 0}}};
