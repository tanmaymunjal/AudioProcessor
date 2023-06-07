#include <iostream>
#include <portaudio/PortAudioCpp.hxx>

// Callback function to process captured audio data
int captureCallback(const void* inputBuffer, void* outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void* userData)
{
    // Cast the input buffer to the appropriate type
    const float* inputData = static_cast<const float*>(inputBuffer);

    // Process the audio data here (e.g., save to a file, analyze, etc.)

    return paContinue;
}

int main()
{
    pa::PortAudioStreamParameters inputParams;
    inputParams.setDevice(pa::PortAudio::getDefaultInputDevice());
    inputParams.setChannelCount(1);
    inputParams.setSampleFormat(pa::INT16);
    inputParams.setSuggestedLatency(pa::PortAudio::getDefaultInputDevice().getDefaultLowInputLatency());

    pa::PortAudioStream stream;
    stream.open(inputParams, nullptr, 44100, 256, captureCallback, nullptr);
    stream.start();

    std::cout << "Recording audio. Press Enter to stop." << std::endl;
    std::cin.get();

    stream.stop();
    stream.close();

    return 0;
}
