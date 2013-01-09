/*
  ==============================================================================

    SubsectionOverlay.cpp
    Created: 9 Jan 2013 7:02:59pm
    Author:  Jerome

  ==============================================================================
*/

#include "SubsectionOverlay.h"

SubsectionOverlay::SubsectionOverlay(AudioSubsectionManager *AudioSubsectionManager_, AudioFilePlayer* filePlayer_)
: subsections(*AudioSubsectionManager_),
filePlayer(filePlayer_)

{
    subsections.addListener(this);
    filePlayer->addListener(this);
};

SubsectionOverlay::~SubsectionOverlay(){};

void SubsectionOverlay::paint(Graphics &g){
    
     g.setOpacity(0.4);
    
    std::cout<<"Overlay Paint \n";
    for (int i = 0; i < subsections.size();) {
        
        int pixel = SampleToPixel(subsections.getStart(i));
        int width = SampleToPixel(subsections.getLength(i));
        //g.drawImageAt (SubsectionImage, pixel, 0);
        
        if(subsections.getLength(i)){
           
            SubsectionImage = new Image(highlightImage.rescaled(width, getHeight()));
            Graphics g1(*SubsectionImage);
            g1.setColour(Colours::white);
            g1.drawRect(0, 0, width, getHeight());
            
            std::cout<<"Drawing subsection"<<subsections.getLength(i)<<"\n";
            g.drawImageAt(*SubsectionImage, pixel, 0);
        
        }
        i++;
    }
}

void SubsectionOverlay::resized(){
    int h = getHeight();
    highlightImage = Image (Image::RGB, 3, jmax (1, h), true);
    Graphics g (highlightImage);
    g.fillAll(Colours::green);

}

//====================================================================================
/** Sample to Pixel conversion
 */
int  SubsectionOverlay::SampleToPixel(int64 sampleClickedOn){ // needs to include zoom ratio and offset values
    return (int) sampleClickedOn / currentXScale;
}
/** Pixel to Sample conversion
 */
int64 SubsectionOverlay::PixelToSample(double PixelClickedOn){
    return (int64) roundToInt((float)currentXScale * PixelClickedOn);
}
//====================================================================================
/**@Internal
 */
void SubsectionOverlay::subsectionCreated(){
    
    std::cout<<"Created \n";
    repaint();
}
/**@Internal
 */
void SubsectionOverlay::subsectionDeleted(){
    repaint();
}
/**@Internal
 */
void SubsectionOverlay::subsectionChanged(int SubsectionIndex){
     std::cout<<"Changed \n";
    repaint();
}
void SubsectionOverlay::fileChanged (AudioFilePlayer* player){
    int64 audioFileLength = player->getTotalLength();
    currentXScale = audioFileLength / getWidth();
    subsections.clear();
}

void SubsectionOverlay::mouseDown(const MouseEvent &e){
    
    if(e.mods.isShiftDown()){
        
        if (!e.mods.isAltDown()){
            if (e.mouseWasClicked())
                subsections.addSubsection(PixelToSample(e.getMouseDownX()));
            else{ 
            }
        }
        if (e.mods.isAltDown()){
            int i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));
            subsections.removeSubsection(i);
        }
    }
}
void SubsectionOverlay::mouseUp (const MouseEvent &e){
    int currentMouseX = e.x;
    if (e.mods.isShiftDown()){
        // subsection.getLast()->LengthInSamples = PixelToSample(e.getDistanceFromDragStart());
    }
    
}
void SubsectionOverlay::mouseDrag(const MouseEvent &e){
    //if (!e.mods.isShiftDown() && !e.mods.isAltDown())
    if (e.mods.isShiftDown()){
        int i = subsections.getNearestSubsection(PixelToSample(e.getMouseDownX()));
        subsections.SetSubsectionDuration(PixelToSample(e.getDistanceFromDragStart()), i);
        std::cout<<i<<"setting length "<<subsections.getLength(i)<<"\n";
    }
}