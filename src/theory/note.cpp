#include "note.h"

std::string Note::get_name() const {
    switch (value_) {
        case C: return "C";
        case Db: return "Db";
        case D: return "D";
        case Eb: return "Eb";
        case E: return "E";
        case F: return "F";
        case Gb: return "Gb";
        case G: return "G";
        case Ab: return "Ab";
        case A: return "A";
        case Bb: return "Bb";
        case B: return "B";

        default:
            PRINT_CRITICAL("Unknown note value: {}", value_);
            assert(false);
            return "[UNKNOWN_NOTE]";
    }
}

Note Note::FromString(std::string name) {
    if      (name == "C" || name == "B#" || name == "Dbb")  return Note(Value::C);
    else if (name == "Db" || name == "C#" || name == "B##") return Note(Value::Db);
    else if (name == "D" || name == "Ebb" || name == "C##") return Note(Value::D);
    else if (name == "Eb" || name == "D#" || name == "Fbb") return Note(Value::Eb);
    else if (name == "E" || name == "Fb" || name == "D##")  return Note(Value::E);
    else if (name == "F" || name == "E#" || name == "Gbb")  return Note(Value::F);
    else if (name == "Gb" || name == "F#" || name == "E##") return Note(Value::Gb);
    else if (name == "G" || name == "Abb" || name == "F##") return Note(Value::G);
    else if (name == "Ab" || name == "G#")                  return Note(Value::Ab);
    else if (name == "A" || name == "Bbb" || name == "G##") return Note(Value::A);
    else if (name == "Bb" || name == "A#" || name == "Cbb") return Note(Value::Bb);
    else if (name == "B" || name == "Cb" || name == "A##")  return Note(Value::B);

    PRINT_CRITICAL("Unknown note: {}", name);
    assert(false);
    return Note();
}
