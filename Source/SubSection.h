/*
  ==============================================================================

    SubSection.h
    Created: 30 Mar 2013 1:53:18pm
    Author:  Jerome

  ==============================================================================
*/

#ifndef __SUBSECTION_H_797D2845__
#define __SUBSECTION_H_797D2845__

//Some common Strings for this project

namespace HitTypeStrings
{
    //Juce Strings
    static const String Kick    = "Kick";
    static const String Snare   = "Snare";
    static const String Ride    = "Ride";
    static const String Crash   = "Crash";
    static const String Highhat = "High-hat";
};

//Hittype as an emum
enum HitTypeValue {
    Unnamed = 0,
    Kick,
    Snare,
    Ride,
    Crash,
    Highhat,
    TotalHitTypes
};


struct SubSection{
    
    int64 StartSample = 0;
    int64 LengthInSamples = 0;
    
    String name = "Slice";
    HitTypeValue TypeValue = Unnamed;
};


#endif  // __SUBSECTION_H_797D2845__
