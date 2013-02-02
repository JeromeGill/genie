/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_3FB3C59F__
#define __PLUGINPROCESSOR_H_3FB3C59F__

#include "genieHeader.h"
#include "Oscillator.h"
#include "AudioSubsectionManager.h"
#include "PolyAudioFilePlayer.h"
#include "MidiManager.h"


//==============================================================================
/**
*/
class GenieAudioProcessor  :    public AudioProcessor
{
public:
    //==============================================================================
    GenieAudioProcessor();
    ~GenieAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    
    bool silenceInProducesSilenceOut() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

private:
    //==============================================================================
    ScopedPointer<AudioFilePlayer> audioFilePlayer;
    
    ScopedPointer<PolyAudioFilePlayer> polyPlayer;
    
    MixerAudioSource mixerAudioSource;
    
    ScopedPointer<MidiManager> midiManager;
    
    ScopedPointer<AudioFormatManager> audioFormatManager;
    ScopedPointer<AudioSubsectionManager> subsectionManager;
    
    MidiKeyboardState keyboardState;
    AudioSourceChannelInfo channelInfo;
   
    Oscillator osc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenieAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_3FB3C59F__
