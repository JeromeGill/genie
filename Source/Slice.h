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
 
 set start + end sample
 
    To Do
 
 ==============================================================================*/

#include "genieHeader.h"

class SliceData
{
public:
//    SliceData(double endPosition)
//    {
//        startSample = 0
//        endSample = endPosition;
//    }
    
    SliceData(double startPosition, double endPosition)
    {
        setStartPosition(startPosition);
        setEndPosition(endPosition);
    }
    
    ~SliceData()
    {
        
    }
    
    void setStartPosition(double position){
        startSample = position;
    }
    
    void setEndPosition(double position){
        endSample = position - 1;
    }

private:
    double startSample, endSample;
};

#endif  // __SLICEDATA_H_D15FEB32__
