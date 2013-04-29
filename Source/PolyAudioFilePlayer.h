/*
  ==============================================================================

    PolyAudioFilePlayer.h
    Created: 11 Dec 2012 10:25:31am
    Author:  Jerome

  ==============================================================================
*/

#ifndef __POLYAUDIOFILEPLAYER_H_624BAC67__
#define __POLYAUDIOFILEPLAYER_H_624BAC67__

#include "genieHeader.h"
#include "PolyPlayerVoice.H"

//==============================================================================
/**PolyAudioFilePlayer
 
 \brief PolyAudioFilePlayer enables polyphonic playback of cropped sections of [AudioFormatReader]
 
 It manages an array of PolyPlayerVoice via the Juce [AudioSource] method with a [MixerAudioSource]
 
 [AudioSource]: http://rawmaterialsoftware.com/juce/api/classAudioSource.html (juce::AudioSource)
 [MixerAudioSource]: http://rawmaterialsoftware.com/juce/api/classMixerAudioSource.html (juce::MixerAudioSource)
 [AudioFormatReader]: http://www.rawmaterialsoftware.com/api/classAudioFormatReader.html (juce::AudioFormatReade)
 
 ToDo;
 It currently takes POLYPHONY from genieheader - it should probably be internal

*/
//==============================================================================


class PolyAudioFilePlayer : public AudioSource
{
public:
    PolyAudioFilePlayer();
    ~PolyAudioFilePlayer();
    
    /**Set the AudioFormatReader to crop from*/
    void setAudioFormatReader(AudioFormatReader *reader);
    
    //==============================================================================
    /**Plays a subsection of the audioFilePlayer and returns the voice it is playing on*/
    void playSubSection(int64 startSample, int64 length, float gain);
    /**Stops whatever voice is playing on a particular index*/
    void stopVoice(int voiceIndex);
 
    
    //==============================================================================
    /** Implementation of the AudioSource method. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    
    /** Implementation of the AudioSource method. */
    void releaseResources();
    
    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    
private:
    MixerAudioSource    mixer;         
    AudioFormatReader*  masterReader;
    TimeSliceThread     thread;
    
    OwnedArray<PolyPlayerVoice> Voices;     
    
    double SampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyAudioFilePlayer)
};




#endif  // __POLYAUDIOFILEPLAYER_H_624BAC67__
