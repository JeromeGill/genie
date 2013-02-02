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

/**==============================================================================
 
 PolyAudioFilePlayer is an object that plays subsections of an AudioFilePlayer polyphonically
 
 Features

 
 ToDo
 
 remove reliance on DRowAudio Components
 
 ==============================================================================*/


class PolyAudioFilePlayer : public AudioSource,
                            public AudioFilePlayer::Listener
{
public:
    PolyAudioFilePlayer(AudioFilePlayer &audioFilePlayer_);
    ~PolyAudioFilePlayer();
    
    //==============================================================================
    /**Plays a subsection of the audioFilePlayer and returns the voice it is playing on*/
    void playSubSection(int64 startSample, int64 length, float gain);
    /**Stops whatever voice is playing on a particular index*/
    void stopVoice(int voiceIndex);
    
    
    //==============================================================================
    /** @internal */
    void fileChanged(AudioFilePlayer *player);
    
    //==============================================================================
    /** Implementation of the AudioSource method. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    
    /** Implementation of the AudioSource method. */
    void releaseResources();
    
    /** Implementation of the AudioSource method. */
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);
    
private:
    MixerAudioSource mixer;
    
    AudioFilePlayer*                    audioFilePlayer;
    ScopedPointer<AudioFormatReader>    masterReader;
    TimeSliceThread                     thread;
    
    OwnedArray<PolyPlayerVoice> Voices;
    
    double SampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyAudioFilePlayer)
};




#endif  // __POLYAUDIOFILEPLAYER_H_624BAC67__
