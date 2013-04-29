/*
  ==============================================================================

    SplittableWaveDisplay.cpp
    Created: 31 Dec 2012 3:42:49pm
    Author:  Jerome

  ==============================================================================
*/

#include "SplittableWaveDisplay.h"


SplittableWaveDisplay::SplittableWaveDisplay(drow::AudioThumbnailImage& sourceToBeUsed,
                                             TimeSliceThread& threadToUse_,
                                             AudioSubsectionManager& subsectionManager_)
:   waveDisplay(sourceToBeUsed, threadToUse_),
    filePlayer(&sourceToBeUsed.getAudioFilePlayer()),
    subsections(subsectionManager_)
{
   
    addAndMakeVisible(&waveDisplay); 
    
    waveDisplay.setInterceptsMouseClicks(false, false);
 
    subsections.addListener(this);
    filePlayer->addListener(this);
};

SplittableWaveDisplay::~SplittableWaveDisplay()
{
    subsections.removeListener(this);
    filePlayer->removeListener(this);
}

void SplittableWaveDisplay::resized(){
    int w = getWidth();
    int h = getHeight();

    waveDisplay.setBounds(0, 0, w, h);

    highlightImage = Image (Image::RGB, 1, jmax (1, h), true);
    Graphics g (highlightImage);
    g.fillAll(Colours::white);
    
    highlightImage.duplicateIfShared();
    
}
void SplittableWaveDisplay::paint(Graphics &g){
    paintOverChildren(g);
}

void SplittableWaveDisplay::paintOverChildren(Graphics &g){
    g.setOpacity(0.4);

   
    
    for (int i = 0; i < subsections.size();++i) {
        
         //std::cout<<i<<" Drawing subsection"<<subsections.getLength(i)<<"\n";
        
        int pixel = SampleToPixel(subsections[i].StartSample);
        int width = SampleToPixel(subsections[i].LengthInSamples);
        
        
        if(width > 0){
            
            Image SubsectionImage = highlightImage.rescaled(width, getHeight());
            
            Graphics g1(SubsectionImage);
            g1.setColour(Colours::green);
            g1.fillRect(Bw,Bw, width - twoBw, getHeight() - twoBw);
            g.drawImageAt(SubsectionImage, pixel, 0);
        }
        else g.drawImageAt(highlightImage, pixel, 0);
    }
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
/** Sample to Pixel conversion
 */
int  SplittableWaveDisplay::SampleToPixel(int64 sampleClickedOn){ // needs to include zoom ratio and offset values
    return (int) sampleClickedOn / currentXScale;
}
/** Pixel to Sample conversion
 */
int64 SplittableWaveDisplay::PixelToSample(double PixelClickedOn){
    if(PixelClickedOn)
        return (int64) (double)currentXScale * PixelClickedOn;
    else{
        std::cout<<" Invalid Pixel -> Sample convertion \n";
        return 0;
    }
}
//====================================================================================
/**@Internal
 */
void SplittableWaveDisplay::subsectionCreated(int SubsectionIndex){
    
    //std::cout<<SubsectionIndex<<"Created \n";
    repaint();
}
/**@Internal
 */
void SplittableWaveDisplay::subsectionDeleted(int SubsectionIndex){
    //std::cout<<SubsectionIndex<<"Deleted \n";
    repaint();
}
/**@Internal
 */
void SplittableWaveDisplay::subsectionChanged(int SubsectionIndex){
    //std::cout<<SubsectionIndex<<" Changed \n";
    repaint();
}
void SplittableWaveDisplay::fileChanged (drow::AudioFilePlayer* player){
    int64 audioFileLength = player->getTotalLength();
    currentXScale = audioFileLength / getWidth();
    subsections.clear();
}

void SplittableWaveDisplay::mouseDown(const MouseEvent &e){
    std::cout<<"Clicked \n";
    if (!e.mouseWasClicked()){
        mouseDrag(e);
    }
    
    if(e.mods.isShiftDown()){
        if (!e.mods.isAltDown()){
            }
        
    }
    else{}
        waveDisplay.mouseDown(e);
}
void SplittableWaveDisplay::mouseUp (const MouseEvent &e){
    int currentMouseX = e.x;
//    if (e.mods.isShiftDown()){
//        subsection.getLast()->LengthInSamples = PixelToSample(e.getDistanceFromDragStart());
//    }
//    else
        waveDisplay.mouseUp(e);
}
void SplittableWaveDisplay::mouseDrag(const MouseEvent &e){
    
    
   
    if (e.mods.isShiftDown()){
        
        if (!e.mods.isAltDown()) {
        
            //Shift-Drag Set previous subsection's duration
            
            int i = subsections.getPreviousSubsection(PixelToSample(e.getMouseDownX()));
            
            if(i >= 0){} //Empty case prevents a call to getNearest if getPreviousSubsecion call was successful
            else {i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));}
            
            
            int64 duration = PixelToSample(e.x) - subsections[i].StartSample;
            if (!duration) duration = 0;
            subsections.SetSubsectionDuration(duration, i);
        }
        else{
            int64 start = PixelToSample(e.x);
            int i = subsections.getNearestSubsection(start);
            if (i >= 0) subsections.SetSubsectionStart(start, i);
        }
    }
    
    else{ waveDisplay.mouseDrag(e); }
}

void SplittableWaveDisplay::mouseDoubleClick(const MouseEvent &e){
    //if (!e.mouseWasClicked()) mouseDrag(e);
    
    if (e.mods.isShiftDown()){
        if (e.mods.isAltDown()){
            int i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));
            if (i >= 0) subsections.removeSubsection(i);
        }
        else{
        subsections.addSubsection(PixelToSample(e.getMouseDownX()));
        
        }
    }
    else{waveDisplay.mouseDoubleClick(e);}
}
