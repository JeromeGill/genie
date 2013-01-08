/*
  ==============================================================================

    MarkerOverlay.cpp
    Created: 7 Jan 2013 7:01:22pm
    Author:  Jerome

  ==============================================================================
*/

#include "MarkerOverlay.h"

MarkerOverlay::MarkerOverlay(AudioFilePlayer &filePlayer_)
: filePlayer(&filePlayer_)
{
    filePlayer->addListener(this);
}
MarkerOverlay::~MarkerOverlay(){
    filePlayer->removeListener(this);
}



//====================================================================================
/** Creates a marker on a specific sample of the waveDisplay
 */
void MarkerOverlay::addMarker (int64 startSample){
    
    subsection.add(new SubSection);
    subsection.getLast()->StartSample = startSample;
    repaint();
    
    std::cout<<"Marker Created at"<< startSample<<"\n";
}
/** Deletes the nearest marker to the sample passed on
 */
void MarkerOverlay::removeMarker (int MarkerIndex){
    subsection.remove(MarkerIndex);
}
/** Sets Start point of a particular marker
 */
void MarkerOverlay::SetSubsectionStart (int64 startSample, int MarkerIndex){
    subsection[MarkerIndex]->StartSample = startSample;
}
/** Sets a markers duration
 */
void MarkerOverlay::SetSubsectionDuration (int64 lengthInSamples, int MarkerIndex){
    subsection[MarkerIndex]->LengthInSamples = lengthInSamples;
    repaint();
}
/** Clears all markers
 */
void MarkerOverlay::clear(){
    subsection.clear();
    repaint();
}
void MarkerOverlay::sortSubsections(){
    if(subsection.size() > 2)
       subsection.sort(subsectionComparator);
}
//====================================================================================
/** Sample to Pixel conversion
 */
int  MarkerOverlay::SampleToPixel(int64 sampleClickedOn){ // needs to include zoom ratio and offset values
    return (int) sampleClickedOn / currentXScale;
}
/** Pixel to Sample conversion
 */
int64 MarkerOverlay::PixelToSample(double PixelClickedOn){
    return (int64) roundToInt((float)currentXScale * PixelClickedOn);
}
/** Sample to time conversion
 */
double MarkerOverlay::SampleToTime(int64 sample){
    return (double) sample * (filePlayer->getTotalLength() / filePlayer->getLengthInSeconds());
}

//====================================================================================
/**@Internal@*/
void MarkerOverlay::fileChanged (AudioFilePlayer* player){
    int64 audioFileLength = filePlayer->getTotalLength();
    currentXScale   = (audioFileLength / getWidth());
    clear();
}
/**@Internal@*/
void MarkerOverlay::paint(Graphics &g){

    for (int i = 0; i < subsection.size();) {
        
        int pixel = SampleToPixel(subsection[i]->StartSample);
        int width = SampleToPixel(subsection[i]->LengthInSamples);
        g.drawImageAt (markerImage, pixel, 0);
        
        if(subsection[i]->LengthInSamples){
            g.setOpacity(0.4);
            g.drawImageAt(highlightImage.rescaled(width, getHeight()), pixel + 3, 0);
            //std::cout<<"Highlight Size"<<width<<"\n";
        }
        i++;
    }
    
}
/**@Internal@*/
void MarkerOverlay::resized(){
    int w = getWidth();
    int h = getHeight();
    
    markerImage = Image (Image::RGB, 3, jmax (1, h), true);
    Graphics g (markerImage);
    g.fillAll (Colours::green);
    g.setColour (Colours::white);
    g.drawVerticalLine (1, 0.0f, (float) markerImage.getHeight());
    
    highlightImage = Image (Image::RGB, 3, jmax (1, h), true);
    Graphics g1 (highlightImage);
    g1.fillAll(Colours::green);
}

void MarkerOverlay::mouseDown(const MouseEvent &e){
    
    if (e.mods.isShiftDown()){
        if (e.mouseWasClicked()) addMarker(PixelToSample(e.getMouseDownX()));
        else{
            subsection.getLast()->LengthInSamples = PixelToSample(e.getDistanceFromDragStart());
            std::cout<<"setting length "<<subsection.getLast()->LengthInSamples<<"\n";
            repaint();
        }
      }
    
}
void MarkerOverlay::mouseUp (const MouseEvent &e){
    int currentMouseX = e.x;
    sortSubsections();
}
void MarkerOverlay::mouseDrag(const MouseEvent &e){
    //if (!e.mods.isShiftDown() && !e.mods.isAltDown())
    if (e.mods.isShiftDown()){
        subsection.getLast()->LengthInSamples = PixelToSample(e.getDistanceFromDragStart());
    }
}
