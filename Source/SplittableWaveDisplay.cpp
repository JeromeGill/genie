/*
  ==============================================================================

    SplittableWaveDisplay.cpp
    Created: 31 Dec 2012 3:42:49pm
    Author:  Jerome

  ==============================================================================
*/

#include "SplittableWaveDisplay.h"


SplittableWaveDisplay::SplittableWaveDisplay(AudioThumbnailImage& sourceToBeUsed,
                                             TimeSliceThread& threadToUse_)
:   waveDisplay(sourceToBeUsed, threadToUse_),
    filePlayer(sourceToBeUsed.getAudioFilePlayer()),
    subsections(*sourceToBeUsed.getAudioFilePlayer()),
    overlay(&subsections, filePlayer)
{
   
    addAndMakeVisible(&waveDisplay);
    addAndMakeVisible(&overlay);
    setInterceptsMouseClicks(true, false);
 
//    subsections.addListener(this);
//    filePlayer->addListener(this);
};

SplittableWaveDisplay::~SplittableWaveDisplay()
{
//    subsections.removeListener(this);
//    filePlayer->removeListener(this);
}

void SplittableWaveDisplay::resized(){
    int w = getWidth();
    int h = getHeight();
    overlay.setBounds(0, 0, w, h);
    waveDisplay.setBounds(0, 0, w, h);
    waveDisplay.toBack();
    

    
}

void SplittableWaveDisplay::paint(Graphics &g){

}

//====================================================================================
/** Sets whether or not the transport cursor should be displayed;
 */
void SplittableWaveDisplay::setCursorDisplayed (bool shoudldDisplayCursor){
    waveDisplay.setCursorDisplayed(shoudldDisplayCursor);
}

/** Sets the colour to use for the background.
 */
void SplittableWaveDisplay::setBackgroundColour (Colour newBackgroundColour){
    waveDisplay.setBackgroundColour(newBackgroundColour);
}

/** Sets the colour to use for the waveform.
 */
void SplittableWaveDisplay::setWaveformColour (Colour newWaveformColour){
    waveDisplay.setWaveformColour(newWaveformColour);
}

/** Sets the current horizontal zoom.
 1.0 displays the whole waveform, 0.5 will show half etc.
 */
void SplittableWaveDisplay::setZoomRatio (double newZoomRatio){
    waveDisplay.setZoomRatio(newZoomRatio);
}

/** Sets an offset used to start the waveform at a faction of the display.
 A value of 0.5 will show the waveform starting at the halfway point etc.
 */
void SplittableWaveDisplay::setStartOffsetRatio (double newStartOffsetRatio){
    waveDisplay.setStartOffsetRatio(newStartOffsetRatio);
}

/** Sets a new vertical zoom ratio.
 Values greater than 1.0 will expand the waveform vertically, less will contract it.
 */
void SplittableWaveDisplay::setVerticalZoomRatio (double newVerticalZoomRatio){
    waveDisplay.setVerticalZoomRatio(newVerticalZoomRatio);
}



//====================================================================================
void SplittableWaveDisplay::mouseDown(const MouseEvent &e){

    if(e.mods.isShiftDown())
        overlay.mouseDown(e);
    else waveDisplay.mouseDown(e);

}
void SplittableWaveDisplay::mouseUp (const MouseEvent &e){
    int currentMouseX = e.x;
    if (e.mods.isShiftDown())
        overlay.mouseUp(e);
    else waveDisplay.mouseUp(e);
}
void SplittableWaveDisplay::mouseDrag(const MouseEvent &e){
   
    if (e.mods.isShiftDown())
        overlay.mouseDrag(e);
        
        else waveDisplay.mouseDrag(e);
}

