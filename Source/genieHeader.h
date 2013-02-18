/*
  ==============================================================================

    genieHeader.h
    Created: 28 Oct 2012 4:59:07pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __GENIEHEADER_H_636F1999__
#define __GENIEHEADER_H_636F1999__


/**==============================================================================

 ==============================================================================*/

#include "../JuceLibraryCode/JuceHeader.h"
using namespace drow;

//Global size definitions in pixels
#define Width 800
#define Height 600

//Component Border sizes
#define Bw 2
#define twoBw 4
#define fourBw 8

//Sample offset used for playback buffer
#define SAMPLEOFFSET_ 512

//Number of Voices
#define POLYPHONY 16

//Stride for output buffer (incase of potential interlacing decision later?)
#define STRIDE 1

//some common Strings for this project
namespace HitType
{
    //Juce Strings
    static const String Kick    = "Kick";
    static const String Snare   = "Snare";
    static const String Ride    = "Ride";
    static const String Crash   = "Crash";
    static const String Highhat = "High hat";
}

#endif  // __GENIEHEADER_H_636F1999__
