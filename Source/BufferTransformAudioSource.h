/*
  ==============================================================================

    samplePlayback.h
    Created: 1 Nov 2012 8:38:42pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __BUFFERTRANSFORMAUDIOSOURCE_H_477BC919__
#define __BUFFERTRANSFORMAUDIOSOURCE_H_477BC919__

#include "genieHeader.h"

//==============================================================================
/*
*/
class BufferTransformAudioSource :  public AudioSource
{
public:
    //==============================================================================
    BufferTransformAudioSource (AudioSource* source,
                                bool deleteSourceWhenDeleted = false);
    
    /** Destructor. */
    ~BufferTransformAudioSource();
    
    /** Returns all of the settings.
     */
    Buffer& getBuffer()     {   return buffer;    }
        
    //==============================================================================
    /** @internal. */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    
    /** @internal. */
    void releaseResources();
    
    /** @internal. */
    void getNextAudioBlock (const AudioSourceChannelInfo& info);
        
private:
    //==============================================================================
    OptionalScopedPointer<AudioSource> source;
    CriticalSection lock;
    Buffer buffer;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BufferTransformAudioSource);
};


#endif  // __BUFFERTRANSFORMAUDIOSOURCE_H_477BC919__
