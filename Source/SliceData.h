/*
  ==============================================================================

    SliceData.h
    Created: 25 Nov 2012 5:12:12pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SLICEDATA_H_D15FEB32__
#define __SLICEDATA_H_D15FEB32__


/**==============================================================================
 
 Slice contains all the information needed for a slice of audio.
 
 Features
    Set start + end sample
    Highlights the samples it represents
    Set hit Type for sequencer
 To Do
    Does it really need to be a seperate class from the sliceViewer?
    Remove all component aspects, splittable audio display should handle it all
    
    Dragable start and end points
    Add a start and end point graphic start "[" and "]" end
    
 ==============================================================================*/

#define opacityDepth 0.3

#include "genieHeader.h"

class SliceData : public Component
{
public:
    
    
    enum HitType{
        Kick = 0,
        Snare,
        Hat,
        Ride,
        Crash,
        TotalHitTypes
    };
    
  
    SliceData(double startPosition,
              double endPosition,
              int index);

    ~SliceData();
    
    /**@Internal@*/
    void paint(Graphics &g);
    /**@Internal@*/
    void resized();
    
    /**Set the start position of the slice*/
    void setStartPosition(double position);
    /**Set the end position of the slice*/
    void setEndPosition(double position);
    /**Set end offset position of the slice
     
     This is the time between the end of this slice and the start of the next one
     EG Slice1.endOffset = Slice2.start - slice1.end  
     
     This allows for trimming of slices.
     */
    void setEndOffset(double position);
   
    /**Set the type of hit the slice represents
     enum HitType{
     Kick = 0,
     Snare,
     Hat,
     Ride,
     Crash,
     TotalHitTypes
     };
     
     eg setHitType(HitType::Kick)
     */
    void setHitType(HitType hitType);
    
    /**Returns the integer for the type of hit the slice represents*/
    int getHitType();
    /**Return the start position of the slice*/
    double getStartPosition();
    /**Return the end position of the slice*/
    double getEndPosition();
    /**Return the length of the slice in time
     This ignores the trim
     eg EndPosition - StartPosition */
    double getTotalLength();
    /**Return the length of the slice in time including the trim
     eg EndPosition - EndOffset - StartPosition */
    double getTrimmedLength();

    /**Set the index for the audio file player that is playing this slice*/
    void setIndex(int sliceIndex);
    /**Get the index for the slice*/
    int getIndex();
    
    /**Set an image of the slice*/
    void setImage(const Image* sliceImage);
    
    /**Returns an image of the slice*/
    const Image getSliceImage();
    
    

private:
    
  
    int hitclass;
    
    double startSample, endSample, endOffset;
    int indexValue;
    int x,y;
    int Index;
    
    const Image* sliceWaveformImage;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliceData)

};



#endif  // __SLICEDATA_H_D15FEB32__
