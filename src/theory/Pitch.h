#pragma once

enum Note {
    C = 12, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B,
};

static double find_equal_temperament_frequency(int n, double base_freq) {
    return base_freq * std::pow(2.0, (((double) n - 69.0) / 12.0));
}

class Pitch {
public:
    Pitch(Note note, uint8_t octave) {
        this->note = note;
        this->octave = octave;
    }

    ~Pitch() {}

    Note get_note() { return note; }
    uint8_t get_octave() { return octave; }
    double get_frequency() { return find_equal_temperament_frequency(note + 12 * octave, tuning); }

private:
    Note note;
    uint8_t octave;
    double tuning = 440.0;
};
