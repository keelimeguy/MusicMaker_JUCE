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

    std::string getName() const;

    static Note fromString(std::string);

private:
    Value value;
};
