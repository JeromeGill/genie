/*
  ==============================================================================

    SliceData.cpp
    Created: 6 Jan 2013 9:13:12pm
    Author:  Jerome

  ==============================================================================
*/

#include "SliceData.h"


SliceData::SliceData(double startPosition,
          double endPosition,
          int index)
{
    
    indexValue = index;
    setStartPosition(startPosition);
    setEndPosition(endPosition);
    
    std::cout<<"Slice Created "<<startSample<<" : "<<endSample<<" at position "<<indexValue<<"\n";
    
}

//Destructor
SliceData::~SliceData(){
    
}

//Component
void SliceData::paint(Graphics &g){
//    g.setColour(Colours::green);
//    g.setOpacity(indexValue%2 * opacityDepth + opacityDepth);
//    g.drawLine(0, 0, 0, y);
//    g.fillAll();
}

void SliceData::resized(){
    
};

// Start and end locations
void SliceData::setStartPosition(double position){
    startSample = position;
    repaint();
}
void SliceData::setEndPosition(double position){
    endSample = position - 1;
    repaint();
}
void SliceData::setEndOffset(double position){
    endOffset = position;
    repaint();
}

void SliceData::setHitType(HitType hitType){
    hitclass = hitType;
    std::cout<<"HitType "<<hitclass<<"\n";
}

int SliceData::getHitType(){ return hitclass;
}
double SliceData::getStartPosition(){return startSample; }
double SliceData::getEndPosition()  {return endSample;   }
double SliceData::getTotalLength()  {return endSample - startSample;}
double SliceData::getTrimmedLength(){return endSample - endOffset - startSample;}

/*set and retreive the index for the audio file player that is playing this slice*/
void SliceData::setIndex(int sliceIndex) {Index = sliceIndex;}
int SliceData::getIndex() {return indexValue;}

/**Set an image of the slice*/
void SliceData::setImage(const Image* sliceImage){
    sliceWaveformImage = sliceImage;
}

const Image SliceData::getSliceImage(){
    std::cout<<"get Image \n";
    return *sliceWaveformImage;
    
}
