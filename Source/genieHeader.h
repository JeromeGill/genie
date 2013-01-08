/*
  ==============================================================================

    genieHeader.h
    Created: 28 Oct 2012 4:59:07pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __GENIEHEADER_H_636F1999__
#define __GENIEHEADER_H_636F1999__

/**
 ==============================================================================
 
 Functions
 
 Open Files
 Render Wave Form
 Store start and end point of each slice
 Highlight Slices
 
 To Do
 
 Save and load slice settings
 
 ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
using namespace drow;

//Global size definitions in pixels
#define Width 800
#define Height 600

//Sample offset used for playback buffer
#define SAMPLEOFFSET_ 512

//Number of Voices
#define POLYPHONY 16

//Stride for output buffer (incase of potential interlacing decision later?)
#define STRIDE 1

#endif  // __GENIEHEADER_H_636F1999__
