//
//  audioEditor.cpp
//  Genie
//
//  Created by Jerome on 12/10/2012.
//
//

/**

 //=======================================================================================================================
 
 audioEditor is an audio file display and slicer object
 
 It comprises of;
 
    An audioFile generic file play back object, adapted from the dRowAudio class AudioFilePlayer
    
    An audioDisplay object for rendering waveforms, adapted from the dRowAudio class AudioThumbnail Image
 
    A Slice Management Class, for storing each slice's midi data, start and end sample and duration in samples.
 
 //=======================================================================================================================
 
*/
#include "audioEditor.h"


AudioEditor::AudioEditor (AudioSubsectionManager &audioSubsectionManager_,
                          AudioFilePlayer &audioFilePlayer_,
                          //AudioThumbnailImage& image,
                          SubsectionEditor& subsectionEditor)
:
    //audioThumbnailImage(&image),
    LoadBar(audioFilePlayer_),
    backgroundThread("Waveform Thread"),
    audioThumbNail (renderSampleRatio, *audioFilePlayer_.getAudioFormatManager(), audioThumbNailCache),
    audioThumbNailHighDef (renderSampleRatio / 2, *audioFilePlayer_.getAudioFormatManager(), audioThumbNailCache),
    audioThumbNailCache (2),
    editor(subsectionEditor)
    

{

   // setInterceptsMouseClicks(true, false);

    
    //The waveform bitmap rendering device
    audioThumbnailImage = new AudioThumbnailImage(audioFilePlayer_,
                                                  audioThumbNailCache.getTimeSliceThread(),
                                                  audioThumbNail,
                                                  renderSampleRatio);
    
    audioThumbnailImage->setBackgroundColour(Colours::transparentBlack);
    audioThumbnailImage->setWaveformColour  (Colours::white);
    audioThumbnailImage->setResolution(thumbResolution);
    

//    audioThumbnailImageHighDef = new AudioThumbnailImage(audioFilePlayer_,
//                                                         audioThumbNailCache.getTimeSliceThread(),
//                                                         audioThumbNailHighDef,
//                                                         renderSampleRatio/4);
//    audioThumbnailImageHighDef->setBackgroundColour(Colours::transparentBlack);
//    audioThumbnailImageHighDef->setWaveformColour  (Colours::white);
//    audioThumbnailImageHighDef->setResolution(thumbResolution * 100);
    editor.setImageSource(*audioThumbnailImage);
    
    
    //The bitmap display
    waveDisplay = new SplittableWaveDisplay (*audioThumbnailImage, backgroundThread, audioSubsectionManager_);
   
    addAndMakeVisible (waveDisplay);

    //The file loading bar
    addAndMakeVisible(&LoadBar);
    
    //Transport Buttons
    //addAndMakeVisible(&transport);
    
    //Zoom and Scroll
    SlZoom.setRange (0.01, 1);
    addAndMakeVisible(&SlZoom);
    SlZoom.addListener(this);
          
    //Text Labels
    
    label.setText("Shift Double-Click to create a slice,\nAlt-Shift Double-Click to delete one.\n Shift drag to change slice's duration,\nAlt-Shift Drag to move one", false);
    label.setJustificationType(Justification::right);
    addAndMakeVisible(&label);
    label.setColour(0x1000281, Colours::white);
    label.setInterceptsMouseClicks(false, false);
    
    backgroundThread.startThread();
    
    
}
AudioEditor::~AudioEditor()
{
    backgroundThread.stopThread(250);
    SlZoom.removeListener(this);

}

//==============================================================================
//Resizing
void AudioEditor::resized()
{
    const int w = getWidth();
    const int h = getHeight();

    LoadBar.setBounds(twoBw, twoBw, w/4* 3 - twoBw, h / 5 - Bw);
    
    SlZoom.setBounds(twoBw, h/5 + Bw, w/4,  h/ 5 - Bw);
    label.setBounds(twoBw, h - twoBw, w - fourBw, h - fourBw);
    
    waveDisplay->setBounds(twoBw, (h/5 * 2) - twoBw, w - fourBw,( h/5 * 3 ));
    
    
}

//Paint
void AudioEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour(Colours::white);
    g.drawRect(Bw, Bw, getWidth()-twoBw, getHeight()-twoBw,Bw);
}


//=================================================================
//Display

void AudioEditor::setZoomRatio(double newZoomRatio){
    
    zoomRatio = newZoomRatio;
    waveDisplay->setZoomRatio (zoomRatio);
}

//=================================================================
//Callbacks
void AudioEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &SlZoom){
        setZoomRatio (slider->getValue());
    }
}



