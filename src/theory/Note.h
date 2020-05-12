#pragma once

class Note {
public:
    enum Value {
        C = 12, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B,
    };

    Note() = default;
    constexpr Note(Value value) : value(value) { }

    operator Value() const { return value; } // Allow switch and comparisons.
    explicit operator bool() = delete; // Prevent usage: if(note)

    std::string getName() {
        switch (value) {
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
                PRINT_CRITICAL("Unknown note value: {}", value);
                assert(false);
                return "[UNKNOWN_NOTE]";
        }
    }

private:
    Value value;
};
