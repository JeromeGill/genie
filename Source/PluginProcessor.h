/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_3FB3C59F__
#define __PLUGINPROCESSOR_H_3FB3C59F__

#include "genieHeader.h"
#include "AudioSubsectionManager.h"
#include "PolyAudioFilePlayer.h"
#include "MidiManager.h"


//====================================================================================
/**
 \breif GenieAudioProcessor is the Juce-Genxerated heart of the plugin.
 
                                                                                   
 It consists of;
 GenieAudioProcessorEditor- responsible for all the GUI components.
 
 AudioSubsectionManager    - A filing class resonable for managing an array of @SubSection
 PolyAudioFilePlayer       - A polyphonic playback device for @SubSections utilising the Juce audiosource system

 [drow::AudioFilePlayer]   - A master audio file player
 [juce::MixerAudioSource]  - A juce class for combining AudioSource objects
 MidiManager               - A midi parser for AudioSubsectionManager

 [drow::AudioFilePlayer]: http://drowaudio.co.uk/docs/class_audio_file_player.html
 [juce::MixerAudioSource]: http://rawmaterialsoftware.com/juce/api/classMixerAudioSource.html
*/
//====================================================================================
class GenieAudioProcessor  :    public AudioProcessor
{
    //Members
    ScopedPointer<AudioFormatManager> audioFormatManager;
    ScopedPointer<drow::AudioFilePlayer> audioFilePlayer; 
    
    AudioSourceChannelInfo channelInfo; //Juce audiosource method
    
    ScopedPointer<AudioSubsectionManager> subsectionManager;
    
    ScopedPointer<PolyAudioFilePlayer> polyPlayer;
    ScopedPointer<MidiManager> midiManager;
    
    MixerAudioSource mixerAudioSource;
    MidiKeyboardState keyboardState;
    
    
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

   
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenieAudioProcessor);
};

#endif  // __PLUGINPROCESSOR_H_3FB3C59F__
