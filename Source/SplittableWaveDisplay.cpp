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
    subsections(*sourceToBeUsed.getAudioFilePlayer())
   // overlay(&subsections, filePlayer)
{
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(&waveDisplay);
    //addAndMakeVisible(&overlay);
   
    
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
   // overlay.setBounds(0, 0, w, h);
    waveDisplay.setBounds(0, 0, w, h);

    highlightImage = Image (Image::RGB, 3, jmax (1, h), true);
    Graphics g (highlightImage);
    g.fillAll(Colours::green);

    
}
void SplittableWaveDisplay::paint(Graphics &g){
    paintOverChildren(g);
}

void SplittableWaveDisplay::paintOverChildren(Graphics &g){
    g.setOpacity(0.4);
    
    std::cout<<"Overlay Paint \n";
    for (int i = 0; i < subsections.size();) {
        
        int pixel = SampleToPixel(subsections.getStart(i));
        int width = SampleToPixel(subsections.getLength(i));
        //g.drawImageAt (SubsectionImage, pixel, 0);
        
        if(subsections.getLength(i)){
            
            Image SubsectionImage(highlightImage.rescaled(width, getHeight()));
            Graphics g1(SubsectionImage);
            g1.setColour(Colours::green);
            g1.drawRect(0, 0, width, getHeight());
            
            std::cout<<"Drawing subsection"<<subsections.getLength(i)<<"\n";
            g.drawImageAt(SubsectionImage, pixel, 0);
            
        }
        i++;
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
    return (int64) roundToInt((float)currentXScale * PixelClickedOn);
}
//====================================================================================
/**@Internal
 */
void SplittableWaveDisplay::subsectionCreated(){
    
    std::cout<<"Created \n";
    repaint();
}
/**@Internal
 */
void SplittableWaveDisplay::subsectionDeleted(){
    repaint();
}
/**@Internal
 */
void SplittableWaveDisplay::subsectionChanged(int SubsectionIndex){
    std::cout<<"Changed \n";
    repaint();
}
void SplittableWaveDisplay::fileChanged (AudioFilePlayer* player){
    int64 audioFileLength = player->getTotalLength();
    currentXScale = audioFileLength / getWidth();
    subsections.clear();
}

void SplittableWaveDisplay::mouseDown(const MouseEvent &e){
    std::cout<<"Clicked \n";
    if(e.mods.isShiftDown()){
        
        if (!e.mods.isAltDown()){
            if (e.mouseWasClicked())
                subsections.addSubsection(PixelToSample(e.getMouseDownX()));
            else{
               
            }
            
            if (e.mods.isAltDown()){
                int i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));
                subsections.removeSubsection(i);
            }
        }
    }
    else waveDisplay.mouseDown(e);
}
void SplittableWaveDisplay::mouseUp (const MouseEvent &e){
    int currentMouseX = e.x;
    if (e.mods.isShiftDown()){
        // subsection.getLast()->LengthInSamples = PixelToSample(e.getDistanceFromDragStart());
    }
    else waveDisplay.mouseUp(e);
}
void SplittableWaveDisplay::mouseDrag(const MouseEvent &e){
    //if (!e.mods.isShiftDown() && !e.mods.isAltDown())
    if (e.mods.isShiftDown()){
        int i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));
        subsections.SetSubsectionDuration(PixelToSample(e.getDistanceFromDragStart()), i);
        std::cout<<i<<"setting length "<<subsections.getLength(i)<<"\n";
    }
    else waveDisplay.mouseDrag(e);
}

//====================================================================================
//void SplittableWaveDisplay::mouseDown(const MouseEvent &e){
//
//    if(e.mods.isShiftDown())
//        overlay.mouseDown(e);
//    else waveDisplay.mouseDown(e);
//
//}
//void SplittableWaveDisplay::mouseUp (const MouseEvent &e){
//    int currentMouseX = e.x;
//    if (e.mods.isShiftDown())
//        overlay.mouseUp(e);
//    else waveDisplay.mouseUp(e);
//}
//void SplittableWaveDisplay::mouseDrag(const MouseEvent &e){
//   
//    if (e.mods.isShiftDown())
//        overlay.mouseDrag(e);
//        
//        else waveDisplay.mouseDrag(e);
//}

