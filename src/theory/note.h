#pragma once

class Note {
public:
    enum Value {
        C = 12, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B,
    };

    Note() = default;
    constexpr Note(Value value) : value_(value) { }

    operator Value() const { return value_; } // Allow switch and comparisons.
    explicit operator bool() = delete; // Prevent usage: if(note)

    std::string get_name() const;

    static Note FromString(std::string);

private:
    Value value_;
};
