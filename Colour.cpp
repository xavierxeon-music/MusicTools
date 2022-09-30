#include <Tools/Colour.h>

const Colour::NoteMap Colour::noteMap = {{Note::C, Colour{255, 255, 255}},
                                         {Note::Cs, Colour{90, 90, 90}},
                                         {Note::D, Colour{255, 0, 0}},
                                         {Note::Ds, Colour{90, 0, 0}},
                                         {Note::E, Colour{255, 30, 200}},
                                         {Note::F, Colour{0, 0, 255}},
                                         {Note::Fs, Colour{0, 0, 90}},
                                         {Note::G, Colour{0, 255, 0}},
                                         {Note::Gs, Colour{0, 90, 0}},
                                         {Note::A, Colour{255, 255, 0}},
                                         {Note::As, Colour{90, 90, 0}},
                                         {Note::B, Colour{0, 0, 0}}};
