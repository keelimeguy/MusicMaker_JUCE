#include "pitch_bank.h"

#include "mode.h"

PitchBank::PitchBank() {
}

PitchBank::~PitchBank() {
}

void PitchBank::AddPitch(Pitch pitch) {
    if (std::find(pitches_.begin(), pitches_.end(), pitch) == pitches_.end()) {
        pitches_.push_back(pitch);
    }
}

void PitchBank::RemovePitch(Pitch pitch) {
    pitches_.erase(std::remove(pitches_.begin(), pitches_.end(), pitch), pitches_.end());
}

void PitchBank::Reorder(Pitch bass) {
    bool is_bass_added = false;

    auto bass_position = std::find(pitches_.begin(), pitches_.end(), bass);
    if (bass_position == pitches_.end()) {
        pitches_.push_back(bass);
        is_bass_added = true;
    }

    std::sort(pitches_.begin(), pitches_.end());

    auto next = pitches_.front();
    while (next != bass) {
        pitches_.pop_front();
        pitches_.push_back(next);
        next = pitches_.front();
    }

    auto octave = bass.get_octave();
    for (size_t i = 0; i < pitches_.size(); ++i) {
        pitches_[i].set_octave(octave);
        if ((i + 1 < pitches_.size()) && (pitches_[i + 1].get_note() <= pitches_[i].get_note())) {
            ++octave;
        }
    }

    if (is_bass_added) pitches_.pop_front();
}

std::regex PitchBank::chord_regex_(
    "([A-G](?:##?|bb?)?)"                                                // key
    "((?:maj|mM|m|M|dim|aug)?)"                                          // kind
    "((?:[1-9]\\d*)?)"                                                   // add
    "((?:(?:(?:(?:##?|bb?)|(?:add|no)(?:##?|bb?)?)[1-9]\\d*)|sus[24]?)*)" // adjust
    "((?:/(?:[A-G](?:##?|bb?)?|(?:##?|bb?)?[1-9]\\d*))?)"                // bass
    "((?:(?:(?:##?|bb?)|(?:add|no)(?:##?|bb?)?)[1-9]\\d*|sus[24]?)*)",    // adjust2
    std::regex::optimize
);

std::regex PitchBank::noadjust_regex_(
    "no(##?|bb?)?[1-9][0-9]*", // noadjust
    std::regex::nosubs | std::regex::optimize
);

std::regex PitchBank::addadjust_regex_(
    "add(##?|bb?)?[1-9][0-9]*", // addadjust
    std::regex::nosubs | std::regex::optimize
);

std::regex PitchBank::susadjust_regex_(
    "sus[24]?", // susadjust
    std::regex::nosubs | std::regex::optimize
);

std::regex PitchBank::addnoadjust_regex_(
    "(add|no)(##?|bb?)?[1-9][0-9]*", // addnoadjust
    std::regex::nosubs | std::regex::optimize
);

std::regex PitchBank::sharpflatadjust_regex_(
    "(##?|bb?)[1-9][0-9]*", // sharpflatadjust
    std::regex::nosubs | std::regex::optimize
);

PitchBank PitchBank::FromString(std::string chord_str) {
    PitchBank chord;

    std::smatch re_match;
    if (std::regex_match(chord_str, re_match, chord_regex_) && re_match.size() == 7) {

        std::string key = re_match.str(1);
        std::string kind = re_match.str(2);
        std::string add = re_match.str(3);
        std::string adjust = re_match.str(4) + re_match.str(6);
        std::string bass = re_match.str(5);

        Pitch root(Note::FromString(key));
        chord.AddPitch(root);

        // Add the appropriate third
        if (kind == "m" || kind == "dim" || kind == "mM") {
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(3) - 1));
        } else {
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(3)));
        }

        // Seventh will get one flat by default
        int flats_on_7th = 1;

        // Don't flatten seventh if major
        if (kind == "M" || kind == "mM" || kind == "maj") {
            flats_on_7th = 0;
#ifdef FORCE_SEVENTH_ON_MAJOR_CHORD
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(7)));
#endif
        }

        // Add the appropriate fifth
        if (kind == "dim") {
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(5) - 1));

            // Flatten seventh twice if diminished
            flats_on_7th = 2;

        } else if (kind == "aug") {
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(5) + 1));

        } else {
            chord.AddPitch(root.Transpose(Mode::Major.FindStep(5)));
        }

        // Handle chord addendum (usually it is the number 7, e.g. Ebm7)
        if (!add.empty()) {
            int add_id = std::stoi(add);

#ifdef FORCE_SEVENTH_ON_CHORD_WHERE_HIGHER_IS_ADDED
            if (add_id >= 7) {
#else
            if (add_id == 7) {
#endif
                chord.AddPitch(root.Transpose(Mode::Major.FindStep(7) - flats_on_7th));
            }

            if (add_id != 7) {
                chord.AddPitch(root.Transpose(Mode::Major.FindStep(add_id)));
            }
        }

        // Handle initial chord adjustments
        if (!adjust.empty()) {

            // First deal with omissions so that we don't overwrite other adjustments
            {
                std::string subject(adjust);
                while (std::regex_search(subject, re_match, noadjust_regex_)) {
                    std::string noadjust = re_match.str(0);

                    int step_adjust = 0;

                    step_adjust += (int)std::count(noadjust.begin(), noadjust.end(), '#');
                    step_adjust -= (int)std::count(noadjust.begin(), noadjust.end(), 'b');
                    noadjust.erase(std::remove(noadjust.begin(), noadjust.end(), '#'), noadjust.end());
                    noadjust.erase(std::remove(noadjust.begin(), noadjust.end(), 'b'), noadjust.end());
                    noadjust.erase(0, 2); // remove the preceding "no" string

                    chord.RemovePitch(root.Transpose(Mode::Major.FindStep(std::stoi(noadjust)) + step_adjust));

                    subject = re_match.suffix().str();
                }
            }

            // Next deal with the suspended third so that thirds added later aren't overwritten
            {
                std::string subject(adjust);
                while (std::regex_search(subject, re_match, susadjust_regex_)) {
                    std::string susadjust = re_match.str(0);

                    susadjust.erase(0, 3);
                    int sus_step = 4; // Default to sus4 if just "sus" is given
                    if (!susadjust.empty()) {
                        sus_step = std::stoi(susadjust);
                    }

                    // Remove existing third to be suspended
                    if (kind == "m" || kind == "dim") {
                        chord.RemovePitch(root.Transpose(Mode::Major.FindStep(3) - 1));
                    } else {
                        chord.RemovePitch(root.Transpose(Mode::Major.FindStep(3)));
                    }

                    chord.AddPitch(root.Transpose(Mode::Major.FindStep(sus_step)));

                    subject = re_match.suffix().str();
                }
            }

            // Deal with sharps and flats
            {
                std::string subject(std::regex_replace(adjust, addnoadjust_regex_, ""));
                while (std::regex_search(subject, re_match, sharpflatadjust_regex_)) {
                    std::string sharpflatadjust = re_match.str(0);

                    int step_adjust = 0;

                    step_adjust += (int)std::count(sharpflatadjust.begin(), sharpflatadjust.end(), '#');
                    step_adjust -= (int)std::count(sharpflatadjust.begin(), sharpflatadjust.end(), 'b');
                    sharpflatadjust.erase(std::remove(sharpflatadjust.begin(), sharpflatadjust.end(), '#'), sharpflatadjust.end());
                    sharpflatadjust.erase(std::remove(sharpflatadjust.begin(), sharpflatadjust.end(), 'b'), sharpflatadjust.end());

                    auto adjusted_pitch = root.Transpose(Mode::Major.FindStep(std::stoi(sharpflatadjust)));
                    chord.RemovePitch(adjusted_pitch);
                    chord.AddPitch(adjusted_pitch.Transpose(step_adjust));

                    subject = re_match.suffix().str();
                }
            }
        }


        // Handle chord bass note
        if (!bass.empty()) {
            int step_adjust = 0;

            step_adjust += (int)std::count(bass.begin(), bass.end(), '#');
            step_adjust -= (int)std::count(bass.begin(), bass.end(), 'b');
            bass.erase(std::remove(bass.begin(), bass.end(), '#'), bass.end());
            bass.erase(std::remove(bass.begin(), bass.end(), 'b'), bass.end());
            bass.erase(0, 1); // remove the preceding '/' character

            int bass_num = 0;
            try {
                bass_num = std::stoi(bass);
            } catch (std::invalid_argument) {}

            std::unique_ptr<Pitch> bass_pitch;
            if (bass_num == 0) {
                bass_pitch = std::make_unique<Pitch>(Note::FromString(bass), root.get_octave());
                if (bass_pitch->get_value() < root.get_value()) {
                    step_adjust += 12;
                }

                bass_pitch.reset(new Pitch(bass_pitch->Transpose(step_adjust)));

            } else {
                bass_pitch = std::make_unique<Pitch>(root.Transpose(Mode::Major.FindStep(bass_num) + step_adjust));
            }

            chord.AddPitch(*bass_pitch.get());
            chord.Reorder(*bass_pitch.get());
        }

        // Handle final chord adjustments
        if (!adjust.empty()) {

            // Deal with additions last, so other modifications don't affect them
            {
                std::string subject(adjust);
                while (std::regex_search(subject, re_match, addadjust_regex_)) {
                    std::string addadjust = re_match.str(0);

                    int step_adjust = 0;

                    step_adjust += (int)std::count(addadjust.begin(), addadjust.end(), '#');
                    step_adjust -= (int)std::count(addadjust.begin(), addadjust.end(), 'b');
                    addadjust.erase(std::remove(addadjust.begin(), addadjust.end(), '#'), addadjust.end());
                    addadjust.erase(std::remove(addadjust.begin(), addadjust.end(), 'b'), addadjust.end());
                    addadjust.erase(0, 3); // remove the preceding "add" string

                    chord.AddPitch(root.Transpose(Mode::Major.FindStep(std::stoi(addadjust)) + step_adjust));

                    subject = re_match.suffix().str();
                }
            }
        }

        chord.Reorder(chord.pitches_[0]);

    } else {
        PRINT_ERROR("Error matching chord regex: {}", chord_str);
        assert(false);
        return chord;
    }

    return chord;
}
