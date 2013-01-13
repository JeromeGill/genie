/*
  ==============================================================================

    PolyPlayerVoice.H
    Created: 26 Dec 2012 1:55:14pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __POLYPLAYERVOICE_H_F7480A5__
#define __POLYPLAYERVOICE_H_F7480A5__

#include "genieHeader.h"

/**============================================================================== 
 
 PolyPlayerVoice is a class designed to crop a section of an AudioFormatReader.
 
 It returns an AudioTransportSource that may be used to playback the cropped section.
 
 ==============================================================================*/

class PolyPlayerVoice
{
public:
    PolyPlayerVoice(TimeSliceThread &Thread)
    :   thread(&Thread)
    {
        
    }
    
    ~PolyPlayerVoice(){
        
    }

    //==============================================================================
    /**Initialise a voice
    
     Set an AudioFormatReader as the master source to crop
     Set the startsample and length of the crop
     */
    void initialise(AudioFormatReader* masterReader,
                    int64 StartSample,
                    int64 Length)
    {
        std::cout<<"Creating Voice. "<<StartSample<<" : "<<Length;
        reader = new AudioSubsectionReader(masterReader,StartSample, Length, false);
        std::cout<<" Created reader. ";
        audioFileSource = new AudioFormatReaderSource (reader, false);
        std::cout<<" Created Source. ";
        audioTransportSource.setSource(audioFileSource,0, thread);
        std::cout<<" Set Source \n";
    }
    
    /**Returns the AudioTransportSource
     */
    inline AudioTransportSource* getAudioSource(){return &audioTransportSource;}
    
private:
    TimeSliceThread         *thread;
    ScopedPointer<AudioSubsectionReader>  reader;
    AudioTransportSource    audioTransportSource;
    ScopedPointer<AudioFormatReaderSource> audioFileSource;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPlayerVoice)
};

#endif  // __POLYPLAYERVOICE_H_F7480A5__
