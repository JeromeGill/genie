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

//==============================================================================
/**PolyPlayerVoice

 \brief PolyPlayerVoice crops a section of an [AudioFormatReader].
 
 It returns an [AudioTransportSource] that may be used to playback the cropped section.
 To help keep threads to a minimum a [TimeSliceThread] must be passed from higher up.
 
 [AudioFormatReader]: http://rawmaterialsoftware.com/juce/api/classAudioFormatReader.html (juce::AudioFormatReader)
 [TimeSliceThread]: http://rawmaterialsoftware.com/juce/api/classTimeSliceThread.html (juce::TimeSliceThread)
 */
 //==============================================================================


class PolyPlayerVoice
{
    
public:
    PolyPlayerVoice(TimeSliceThread &Thread)
    :   thread(&Thread)
    {
        
    }
    
    ~PolyPlayerVoice()
    {
        audioTransportSource.setSource(0);

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

        reader = new AudioSubsectionReader(masterReader,StartSample, Length, false);
        audioFileSource = new AudioFormatReaderSource (reader, false);
        audioTransportSource.setSource(audioFileSource,0, thread);
    }
    
     AudioTransportSource    audioTransportSource; //!< The AudioSource play back device for the cropped audio.
    
private:
    TimeSliceThread         *thread;
    
    ScopedPointer<AudioSubsectionReader>  reader;
    ScopedPointer<AudioFormatReaderSource> audioFileSource;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPlayerVoice)
};

#endif  // __POLYPLAYERVOICE_H_F7480A5__
