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
#include "audioFileLoader.h"
#include "SplittableWaveDisplay.h"
#include "SubsectionEditor.h"

#define renderSampleRatio   128 //a lower number gives higher definition rendering of audio files
#define thumbResolution     10 //a higher number gives a higher resolution of the rendered file.

//==============================================================================
/**AudioEditor
 \brief AudioEditor is an Audio File Loader, display and slicer object
 
 An AudioFileLoader loads an audio file into [drow::AudioFilePlayer]
 An image is rendered with a [drow::AudioThumbnailImage] on a [TimeSliceThread]
 This image is passed to a SplittableWaveDisplay and a SubsectionEditor (poor quality messy method that needs replacing - perhaps a listener system would be cleaner)
 
 [drow::AudioFilePlayer]: http://drowaudio.co.uk/docs/class_audio_file_player.html (drow:AudioFilePlayer)
 [drow::AudioThumbnailImage]: http://drowaudio.co.uk/docs/class_audio_thumbnail_image.html (drow:AudioThumbnailImage)
 [TimeSliceThread]: http://rawmaterialsoftware.com/juce/api/classTimeSliceThread.html (Juce::TimeSliceThread)
*///==============================================================================
class AudioEditor : public Component,
                    public Slider::Listener
{
public:
    AudioEditor(AudioSubsectionManager &audioSubsectionManager_,
                drow::AudioFilePlayer &audioFilePlayer_,
                SubsectionEditor& subsectionEditor);
    ~AudioEditor();
    

    
    /**Set the Zoom Ratio for the Splitable Wave Display*/
    void setZoomRatio(double newZoomRatio);
    
    /** @Internal */
    void sliderValueChanged (Slider* slider);

    /**Component*/
    /** @Internal */
    void resized();
    /** @Internal */
    void paint(Graphics& g);

private:
    //==============================================================================
    // Member Objects
    
    //File Loading bar
    AudioFileLoader LoadBar;
   
    
    //Rendering Thread
    TimeSliceThread backgroundThread;
    
    //Display
    AudioThumbnail          audioThumbNail;
    //AudioThumbnail          audioThumbNailHighDef;
    AudioThumbnailCache     audioThumbNailCache;
    ScopedPointer<drow::AudioThumbnailImage>    audioThumbnailImage;
    //ScopedPointer<drow::AudioThumbnailImage>    audioThumbnailImageHighDef;
    ScopedPointer<SplittableWaveDisplay>  waveDisplay;
    
    
    SubsectionEditor& editor;
    
    double zoomRatio;
    
    //Display Controls
    Slider SlZoom;
    Slider SlOffset;
    
    //Label
    Label label;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioEditor)
    
};
#endif /* defined(__Genie__audioEditor__) */
