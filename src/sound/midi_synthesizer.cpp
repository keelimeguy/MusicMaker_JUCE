#include "midi_synthesizer.h"

MidiSynthesizer::MidiSynthesizer(int numVoices)
    : numVoices_(numVoices), synthAudioSource_(keyboardState_, numVoices) {
    auto xml = juce::parseXML("<DEVICESETUP deviceType=\"DirectSound\" audioOutputDeviceName=\"Primary Sound Driver\"/>");
    setAudioChannels(0, 2, xml.get());

    dumpDeviceInfo();
}

MidiSynthesizer::~MidiSynthesizer() {
    shutdownAudio();
}

void MidiSynthesizer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    PRINT_DEBUG("Preparing to play audio...");
    synthAudioSource_.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MidiSynthesizer::releaseResources() {
    PRINT_DEBUG("Releasing audio resources");
    synthAudioSource_.releaseResources();
}

void MidiSynthesizer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    synthAudioSource_.getNextAudioBlock(bufferToFill);
}

static juce::String getListOfActiveBits(const juce::BigInteger &b) {
    juce::StringArray bits;

    for (int i = 0; i <= b.getHighestBit(); ++i)
        if (b[i])
            bits.add(juce::String(i));

    return bits.joinIntoString(", ");
}

void MidiSynthesizer::dumpDeviceInfo() {

    PRINT_LOG("--------------------------------------");
    for (auto &dev_type : deviceManager.getAvailableDeviceTypes()) {
        PRINT_LOG("TYPE: {}", dev_type->getTypeName());
        for (auto &name : dev_type->getDeviceNames()) {
            PRINT_LOG("\tDEVICE: {}", name);
        }
    }

    PRINT_LOG("--------------------------------------");
    PRINT_LOG("Current audio device type: " + (deviceManager.getCurrentDeviceTypeObject() != nullptr
              ? deviceManager.getCurrentDeviceTypeObject()->getTypeName()
              : "<none>"));

    if (auto *device = deviceManager.getCurrentAudioDevice()) {
        PRINT_LOG("Current audio device: "   + device->getName().quoted());
        PRINT_LOG("Sample rate: "            + juce::String(device->getCurrentSampleRate()) + " Hz");
        PRINT_LOG("Block size: "             + juce::String(device->getCurrentBufferSizeSamples()) + " samples");
        PRINT_LOG("Bit depth: "              + juce::String(device->getCurrentBitDepth()));
        PRINT_LOG("Input channel names: "    + device->getInputChannelNames().joinIntoString(", "));
        PRINT_LOG("Active input channels: "  + getListOfActiveBits(device->getActiveInputChannels()));
        PRINT_LOG("Output channel names: "   + device->getOutputChannelNames().joinIntoString(", "));
        PRINT_LOG("Active output channels: " + getListOfActiveBits(device->getActiveOutputChannels()));
    } else {
        PRINT_LOG("No audio device open");
    }
    PRINT_LOG("--------------------------------------");
}
