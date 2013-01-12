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
    audioThumbNailCache (1),
    editor(subsectionEditor)
    

{

   // setInterceptsMouseClicks(true, false);

    
    //The waveform bitmap rendering device
    audioThumbnailImage = new AudioThumbnailImage(&audioFilePlayer_,
                                                  backgroundThread,
                                                  &audioThumbNailCache,
                                                  &audioThumbNail,
                                                  renderSampleRatio);
    
    audioThumbnailImage->setBackgroundColour(Colours::black);
    audioThumbnailImage->setWaveformColour  (Colours::white);
    audioThumbnailImage->setResolution(thumbResolution);
    
    editor.setImageSource(*audioThumbnailImage);
    //The bitmap display
    waveDisplay = new SplittableWaveDisplay (*audioThumbnailImage, backgroundThread, audioSubsectionManager_);
   
    addAndMakeVisible (waveDisplay);
    
    //Component
    addAndMakeVisible(&midiControl);

    //The file loading bar
    addAndMakeVisible(&LoadBar);
    
    //Transport Buttons
    //addAndMakeVisible(&transport);
    
    //Zoom and Scroll
    SlZoom.setRange (0.01, 1);
    addAndMakeVisible(&SlZoom);
    SlZoom.addListener(this);
          
    //Text Labels
    
    label.setText("Shift Double-Click to create a slice, Alt-Shift Double-Click to delete one", false);
    label.setJustificationType(Justification::centred);
    addAndMakeVisible(&label);
    label.setColour(0x1000281, Colours::white);
    label.setInterceptsMouseClicks(false, false);
    
    
}
AudioEditor::~AudioEditor()
{

    SlZoom.removeListener(this);

}

//==============================================================================
//Resizing
void AudioEditor::resized()
{
    const int w = getWidth();
    const int h = getHeight();

    LoadBar.setBounds(twoBw, twoBw, w/4* 3 - twoBw, h / 5 - fourBw);
    
    SlZoom.setBounds(twoBw, h/5 - twoBw, w/4 - fourBw,  h/ 5 - fourBw);
    label.setBounds(twoBw, h / 5 * 4 - twoBw, w - fourBw, h/5 - fourBw);
    
    waveDisplay->setBounds(twoBw, (h/5 * 2) - twoBw, w - fourBw,( h/5 * 3 )- fourBw);
    
    midiControl.setBounds (w/4 *3, twoBw, w/4  - twoBw, h/5 - fourBw);
    
    
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



