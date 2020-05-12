#include "MidiSynthesizer.h"
#include "Logger.h"

MidiSynthesizer::MidiSynthesizer(int numVoices)
    : numVoices(numVoices), synthAudioSource(keyboardState, numVoices) {
    auto xml = juce::parseXML("<DEVICESETUP deviceType=\"DirectSound\" audioOutputDeviceName=\"Primary Sound Driver\"/>");
    setAudioChannels(0, 2, xml.get());

    dumpDeviceInfo();
}

MidiSynthesizer::~MidiSynthesizer() {
    shutdownAudio();
}

void MidiSynthesizer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    PRINT_TRACE("Preparing to play audio...");
    synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MidiSynthesizer::releaseResources() {
    PRINT_TRACE("Releasing audio resources");
    synthAudioSource.releaseResources();
}

void MidiSynthesizer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    synthAudioSource.getNextAudioBlock(bufferToFill);
}

static juce::String getListOfActiveBits(const juce::BigInteger &b) {
    juce::StringArray bits;

    for (int i = 0; i <= b.getHighestBit(); ++i)
        if (b[i])
            bits.add(juce::String(i));

    return bits.joinIntoString(", ");
}

void MidiSynthesizer::dumpDeviceInfo() {

    PRINT_INFO("--------------------------------------");
    for (auto &dev_type : deviceManager.getAvailableDeviceTypes()) {
        PRINT_INFO("TYPE: {}", dev_type->getTypeName());
        for (auto &name : dev_type->getDeviceNames()) {
            PRINT_INFO("\tDEVICE: {}", name);
        }
    }

    PRINT_INFO("--------------------------------------");
    PRINT_INFO("Current audio device type: " + (deviceManager.getCurrentDeviceTypeObject() != nullptr
               ? deviceManager.getCurrentDeviceTypeObject()->getTypeName()
               : "<none>"));

    if (auto *device = deviceManager.getCurrentAudioDevice()) {
        PRINT_INFO("Current audio device: "   + device->getName().quoted());
        PRINT_INFO("Sample rate: "            + juce::String(device->getCurrentSampleRate()) + " Hz");
        PRINT_INFO("Block size: "             + juce::String(device->getCurrentBufferSizeSamples()) + " samples");
        PRINT_INFO("Bit depth: "              + juce::String(device->getCurrentBitDepth()));
        PRINT_INFO("Input channel names: "    + device->getInputChannelNames().joinIntoString(", "));
        PRINT_INFO("Active input channels: "  + getListOfActiveBits(device->getActiveInputChannels()));
        PRINT_INFO("Output channel names: "   + device->getOutputChannelNames().joinIntoString(", "));
        PRINT_INFO("Active output channels: " + getListOfActiveBits(device->getActiveOutputChannels()));
    } else {
        PRINT_INFO("No audio device open");
    }
    PRINT_INFO("--------------------------------------");
}
