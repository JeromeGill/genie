//
//  audioEditor.h
//  Genie
//
//  Created by Jerome on 12/10/2012.
//
//

#ifndef __Genie__audioEditor__
#define __Genie__audioEditor__

#include "genieHeader.h"
#include "audioFile.h"
#include "SliceManager.h"
#include "MidiControl.h"
#include "SplittableWaveDisplay.h"

/**==============================================================================
 
 audioEditor is an audio file display and slicer object
 
 It comprises of;
    An audioFile generic file play back object, adapted from the dRowAudio class AudioFilePlayer
    An audioDisplay object for rendering waveforms, adapted from the dRowAudio class AudioThumbnail Image
    A Slice Management Class, for storing each slice's midi data, start and end sample and duration in samples.

 
 This will load an audio file and display its waveform. Clicking on the waveform will reposition the transport source.
 
 It contains positional data for slices in a positionalWaveDisplay object
 It allows the user to see and modify the position of the start and end point of a slice.
 They may also create new slices by splitting an existing slice by adding a marker or adjoin two slices into one by removing one.
 
 It needs to be created when an audiofile is loaded up and cleared when an audiofile is closed.
 This is because it needs the length of an audio file in samples to initialise.
 
 
 Features;
    Adjustable zoom
    Shift Click to dynamically create Slices
    Shift + Alt click to Delete Slices
    Automatic endpoint reallocation when adjacent markers are created
    Entire way that slices are highlighted needs addressing 
 
 Todo;
    Make overlay so you can click anywhere
    Set marker start and end sample by dragging markers - probably needs making threadsafe
 
 
 ==============================================================================*/


#define renderSampleRatio   128 //a lower number gives higher definition rendering of audio files
#define thumbResolution     10 //a higher number gives a higher resolution of the rendered file. 

class AudioEditor : public Component,
                    public Slider::Listener
{
public:
    AudioEditor(AudioSubsectionManager &audioSubsectionManager_, AudioFilePlayer &audioFilePlayer_);
    ~AudioEditor();
    

    
    /**Set the Zoom Ratio for the Splitable Wave Display*/
    void setZoomRatio(double newZoomRatio);
    
    /** @Internal@ */
    void sliderValueChanged (Slider* slider);

    /**Component*/
    /** @Internal@ */
    void resized();
    /** @Internal@ */
    void paint(Graphics& g);

private:
    //==============================================================================
    // Member Objects
    
    //File Loading bar
    AudioFile LoadBar;
   
    
    //Rendering Thread
    TimeSliceThread backgroundThread;
    
    //Display
    AudioThumbnail                      audioThumbNail;
    AudioThumbnailCache                 audioThumbNailCache;
    ScopedPointer<AudioThumbnailImage>  audioThumbnailImage;
    SplittableWaveDisplay*              waveDisplay;
    
    MidiControl midiControl;
    
    double zoomRatio;
    
    //Display Controls
    Slider SlZoom;
    
    //Label
    Label label;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioEditor)
    
};
#endif /* defined(__Genie__audioEditor__) */
