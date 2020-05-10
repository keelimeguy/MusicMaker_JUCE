#include "AudioPlayer.h"
#include "Logger.h"

AudioPlayer::AudioPlayer() {
    auto xml = juce::parseXML("<DEVICESETUP deviceType=\"DirectSound\" audioOutputDeviceName=\"Primary Sound Driver\"/>");
    setAudioChannels(0, 2, xml.get());
}

AudioPlayer::~AudioPlayer() {
    shutdownAudio();
}

void AudioPlayer::play_pitch(Pitch *p) {
    PRINT_TRACE("Playing {} Hz", (int)p->get_frequency());
    phaseDelta = (float) (juce::MathConstants<double>::twoPi * p->get_frequency() / sampleRate);

    dumpDeviceInfo();
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double newSampleRate) {
    sampleRate = newSampleRate;
    expectedSamplesPerBlock = samplesPerBlockExpected;
    PRINT_TRACE("Preparing to play audio...");
}

void AudioPlayer::releaseResources() {
    PRINT_TRACE("Releasing audio resources");
}

void AudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    bufferToFill.clearActiveBufferRegion();
    auto originalPhase = phase;

    for (auto chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan) {
        phase = originalPhase;

        auto *channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples ; ++i) {
            channelData[i] = amplitude * std::sin(phase);

            // increment the phase step for the next sample
            phase = std::fmod(phase + phaseDelta, juce::MathConstants<float>::twoPi);
        }
    }
}

static juce::String getListOfActiveBits(const juce::BigInteger &b) {
    juce::StringArray bits;

    for (int i = 0; i <= b.getHighestBit(); ++i)
        if (b[i])
            bits.add(juce::String(i));

    return bits.joinIntoString(", ");
}

void AudioPlayer::dumpDeviceInfo() {

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
}
